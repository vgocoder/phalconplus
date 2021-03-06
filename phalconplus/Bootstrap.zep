//<?php
namespace PhalconPlus;
use PhalconPlus\Enum\Sys as Sys;

final class Bootstrap
{
    // 全局配置 <\Phalcon\Config>
    protected config = null;
    // 全局DI容器 <\Phalcon\Di>
    protected di = null;
    // 应用实例 <\Phalcon\Mvc\Application>
    protected application = null;
    // 模块实例 <\PhalconPlus\Base\ModuleDef>
    protected primaryModuleDef = null;
    // 加载的模块实例列表 <\PhalconPlus\Base\ModuleDef>[]
    protected activeModules = [];
    // <\Phalcon\Debug>
    protected debug = null;
    // 默认运行环境
    // 其实框架定义了<\PhalconPlus\Enum\RunEnv>，但考虑再三，此处不能做枚举限制
    // Enum: ['dev', 'test', 'pre-production', 'production']
    protected env = \PhalconPlus\Enum\RunEnv::DEV;

    public function __construct(string! moduleDir)
    {
        // 模块目录, PrimaryModule Dir
        Sys::init(moduleDir);

        // 获取并初始化运行环境
        var env = trim(get_cfg_var(Sys::ENV_NAME));
        // 这里不能强约束env的值为枚举中的一个
        // 你可能会有非常多的环境，只要env值和配置文件名能对应上就行
        if !empty(env) {
            let this->env = env;
        }
        // 如果不是生产环境，打开Debug
        // 这里我们假设生产环境的env值会以"product"开头
        if substr(PHP_SAPI, 0, 3) != "cli" && !\PhalconPlus\Enum\RunEnv::isInProd(this->env) {
            let this->debug = new \Phalcon\Debug();
            this->debug->listen();
        }

        // 定义全局常量
        define("APP_ENV", this->env, true); // 为了兼容, 同下
        define("APP_RUN_ENV", this->env, true);
        define("APP_ROOT_DIR", Sys::getRootDir(), true);
        define("APP_MODULE_DIR", Sys::getPrimaryModuleDir(), true); // 为了兼容, 同下
        define("APP_PRI_MODULE_DIR", Sys::getPrimaryModuleDir(), true);
        define("APP_ROOT_COMMON_DIR", Sys::getCommonDir(), true);
        define("APP_ROOT_COMMON_LOAD_DIR", Sys::getGlobalLoadDir(), true);
        define("APP_ROOT_COMMON_CONF_DIR", Sys::getGlobalConfigDir(), true);
    }

    private function registerModule(<\PhalconPlus\Base\ModuleDef> moduleDef) -> <\PhalconPlus\Base\AbstractModule>
    {
        if isset(this->activeModules[moduleDef->getName()]) {
            throw new \Exception("Module already loaded: " . moduleDef->getName());
        }
        if is_null(this->di) {
            throw new \Exception("DI doesn't load yet, failed to register module " . moduleDef->getName());
        }
        // Implement a module from it's defintion
        var module = moduleDef->impl(this->di);

        // Register autoloaders and di-services
        module->registerAutoloaders();
        module->registerServices();

        // Maintain a list of loaded modules
        let this->activeModules[moduleDef->getName()] = module;

        return module;
    }

    public function initConf() -> <\PhalconPlus\Bootstrap>
    {
        var globalConfPath = "", moduleConf = null;
        // 全局配置
        let globalConfPath = Sys::getGlobalConfigPath();
        if !is_file(globalConfPath) {
            // throw new \Phalcon\Config\Exception("Global config file not exist, file position: " . globalConfPath);
            // Make a warning here
            error_log("PHP Notice:  PhalconPlus\\Bootstrap Global config file not exists: " . globalConfPath);
            let this->config = new \Phalcon\Config([]); 
        } else {
            let this->config = new \Phalcon\Config(this->load(globalConfPath));
        }

        // 初始化主模块
        let this->primaryModuleDef = new \PhalconPlus\Base\ModuleDef(this, APP_MODULE_DIR, true);
        // 定义工作模式
        define("APP_RUN_MODE", this->primaryModuleDef->getMode(), true);
        // 获取模块配置
        let moduleConf = this->primaryModuleDef->getConfig();
        // 合并配置，Module配置优先级更高
        this->config->merge(moduleConf);
        // 返回对象本身
        return this;
    }

    public function exec()
    {
        var handleMethod = "exec";
        // 初始化配置
        this->initConf();
        let handleMethod .= this->primaryModuleDef->getMapClassName();
        return call_user_func_array([this, handleMethod], func_get_args());
    }

    public function execModule(var uri = null, bool needHandle = true)
    {
        // 如果被直接调用需要自己加载配置
        if empty(this->config) {
            this->initConf();
        }
        // 应用初始化
        let this->di = new \Phalcon\DI\FactoryDefault();
        let this->application = new \Phalcon\Mvc\Application();
        this->application->setDI(this->di);

        // 加载Web模式依赖
        var globalScript;
        let globalScript = APP_ROOT_COMMON_LOAD_DIR . "default-web.php";
        if is_file(globalScript) {
            this->load(globalScript);
        } else {
            error_log("PHP Notice:  PhalconPlus\\Bootstrap Global load file not exists: " . globalScript);
        }

        // 把自己注入di
        this->di->setShared("bootstrap", this);
        // 注册模块
        this->registerModule(this->primaryModuleDef);

        // 如果不需要handle，则直接返回
        if !needHandle { return true; }

        // 运行
        try {
            echo this->application->handle(uri)->getContent();
        } catch \Phalcon\Mvc\Application\Exception {
            var router, newUri;
            let router = this->di->get("router");
            let newUri = "/" . router->getDefaultModule() . router->getRewriteUri();
            echo this->application->handle(newUri)->getContent();
        }
    }

    public function execSrv(bool needHandle = true)
    {
        var backendSrv = null;

        if empty(this->config) {
            this->initConf();
        }

        let this->di = new \Phalcon\DI\FactoryDefault();
        this->di->setShared("bootstrap", this);

        var globalScript;
        let globalScript = APP_ROOT_COMMON_LOAD_DIR . "default-web.php";
        if is_file(globalScript) {
            this->load(globalScript);
        } else {
            error_log("PHP Notice:  PhalconPlus\\Bootstrap Global load file not exists: " . globalScript);
        }

        // 注册模块
        this->registerModule(this->primaryModuleDef);

        if !needHandle { return true; }

        // Backend Server, Default is SimpleServer 
        if this->di->has("backendSrv") {
            let backendSrv = this->di->get("backendSrv");
            if ! (backendSrv instanceof \PhalconPlus\RPC\Server\AbstractServer) {
                throw new \Exception("Service object(DI[\"backendSrv\"]) must be type of \\PhalconPlus\\RPC\\Server\\AbstractServer");
            }
        } else {
            let backendSrv = new \PhalconPlus\Base\SimpleServer(this->di);
        }

        // Yar Server
        let this->application = new \Yar_Server(backendSrv);

        // 运行
        this->application->handle();
    }

    public function execTask(array argv, <\Phalcon\DI\FactoryDefault> di = null, var needHandle = true)
    {
        if empty(this->config) {
            this->initConf();
        }

        if is_null(di) || ! (di instanceof \Phalcon\DI\FactoryDefault\CLI) {
            let this->di = new \Phalcon\DI\FactoryDefault\CLI();
        } else {
            let this->di = di;
        }

        let this->application = new \Phalcon\CLI\Console();
        this->application->setDI(this->di);

        var globalScript;
        let globalScript = APP_ROOT_COMMON_LOAD_DIR . "default-cli.php";
        if is_file(globalScript) {
            this->load(globalScript);
        } else {
            error_log("PHP Notice:  PhalconPlus\\Bootstrap Global load file not exists: " . globalScript);
        }
        
        this->di->setShared("bootstrap", this);

        // 注册模块
        this->registerModule(this->primaryModuleDef);

        if !needHandle { return true; }

        // 运行
        return this->application->handle(argv);
    }

    public function getPrimaryModuleDef() -> <\PhalconPlus\Base\ModuleDef>
    {
        return this->primaryModuleDef;
    }

    public function getPrimaryModule() -> <\PhalconPlus\Base\AbstractModule>
    {
        var name = this->primaryModuleDef->getName();
        if !isset(this->activeModules[name]) {
            throw new \Exception("Module not exists: " . name);
        }
        return this->activeModules[name];
    }

    public function getModule(string! name) -> <\PhalconPlus\Base\AbstractModule>
    {
        if !isset(this->activeModules[name]) {
            throw new \Exception("Module not exists: " . name);
        }
        return this->activeModules[name];
    }

    public function getModuleDef(string! name) -> <\PhalconPlus\Base\ModuleDef>
    {
        if !isset(this->activeModules[name]) {
            throw new \Exception("Module not exists: " . name);
        }
        return this->activeModules[name]->getDef();
    }

    public function dependModule(string! moduleName) -> <\PhalconPlus\Base\AbstractModule>
    {
        var module, moduleDef, moduleDir, moduleConf;
        let moduleDir = Sys::getModuleDirByName(moduleName);
        let moduleDef = new \PhalconPlus\Base\ModuleDef(this, moduleDir);
        // 注册模块
        let module = this->registerModule(moduleDef);

        // 保留被依赖的模块的配置, 已经移除
        // this->di->set("moduleConfig", moduleDef->getConfig());
        // Use `$bootstrap->getModuleDef($moduleName)->getConfig()` instead

        // 参与合并的模块配置
        let moduleConf = new \Phalcon\Config(this->load(moduleDef->getConfigPath()));
        // 全局配置文件优先级高于被依赖的模块
        moduleConf->merge(this->config);
        this->setConfig(moduleConf);
        return module;
    }

    public function isDebug() -> boolean
    {
        return null != this->debug;
    }

    public function getDebug() -> <\Phalcon\Debug>
    {
        return this->debug;
    }

    public function getEnv() -> string
    {
        return this->env;
    }

    public function getConfig() -> <\Phalcon\Config>
    {
        return this->config;
    }

    // 传入的 Config 优先级更高
    public function setConfig(<\Phalcon\Config> config)
    {
        var globalConf;
        if ! this->di->has("config") {
            let globalConf = new \Phalcon\Config();
        } else {
            let globalConf = this->di->getConfig();
        }
        globalConf->merge(config);
        let this->config = globalConf;
        this->di->set("config", this->config);
        return this;
    }

    public function getDI() -> <\Phalcon\DI>
    {
        return this->di;
    }

    public function load(var filePath)
    {
        if !is_file(filePath) {
            throw new \Exception("The file you try to load is not exists. file position: " . filePath);
        }

        var rootPath, loader, config, application, bootstrap, di;

        let
          rootPath = "rootPath",
          loader = "loader",
          config = "config",
          application = "application",
          bootstrap = "bootstrap",
          di = "di";

        let {rootPath} = APP_ROOT_DIR;
        let {loader} = new \Phalcon\Loader();
        let {config} = this->config;
        let {application} = this->application;
        let {bootstrap} = this;
        let {di} = this->di;

        /* PHP 7.1 and later version, forbid dynamic calls to scope introspection functions
        extract(["rootPath": APP_ROOT_DIR,
                 "loader": new \Phalcon\Loader(),
                 "config": this->config,
                 "application": this->application,
                 "bootstrap": this,
                 "di": this->di
        ]);
        */
        return require filePath;
    }
}
