
extern zend_class_entry *phalconplus_base_moduledef_ce;

ZEPHIR_INIT_CLASS(PhalconPlus_Base_ModuleDef);

PHP_METHOD(PhalconPlus_Base_ModuleDef, __construct);
PHP_METHOD(PhalconPlus_Base_ModuleDef, impl);
PHP_METHOD(PhalconPlus_Base_ModuleDef, getIsPrimary);
PHP_METHOD(PhalconPlus_Base_ModuleDef, getClassPath);
PHP_METHOD(PhalconPlus_Base_ModuleDef, getClassName);
PHP_METHOD(PhalconPlus_Base_ModuleDef, getRunMode);
PHP_METHOD(PhalconPlus_Base_ModuleDef, getMapClassName);
PHP_METHOD(PhalconPlus_Base_ModuleDef, getMode);
PHP_METHOD(PhalconPlus_Base_ModuleDef, getName);
PHP_METHOD(PhalconPlus_Base_ModuleDef, getConfigPath);
PHP_METHOD(PhalconPlus_Base_ModuleDef, getConfig);
PHP_METHOD(PhalconPlus_Base_ModuleDef, getDir);

ZEND_BEGIN_ARG_INFO_EX(arginfo_phalconplus_base_moduledef___construct, 0, 0, 2)
	ZEND_ARG_OBJ_INFO(0, boot, PhalconPlus\\Bootstrap, 0)
#if PHP_VERSION_ID >= 70200
	ZEND_ARG_TYPE_INFO(0, moduleDir, IS_STRING, 0)
#else
	ZEND_ARG_INFO(0, moduleDir)
#endif
#if PHP_VERSION_ID >= 70200
	ZEND_ARG_TYPE_INFO(0, isPrimary, _IS_BOOL, 0)
#else
	ZEND_ARG_INFO(0, isPrimary)
#endif
ZEND_END_ARG_INFO()

#if PHP_VERSION_ID >= 70200
ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_phalconplus_base_moduledef_impl, 0, 1, PhalconPlus\\Base\\AbstractModule, 0)
#else
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_phalconplus_base_moduledef_impl, 0, 1, IS_OBJECT, "PhalconPlus\\Base\\AbstractModule", 0)
#endif
	ZEND_ARG_OBJ_INFO(0, di, Phalcon\\Di, 0)
ZEND_END_ARG_INFO()

#if PHP_VERSION_ID >= 70200
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_phalconplus_base_moduledef_getclasspath, 0, 0, IS_STRING, 0)
#else
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_phalconplus_base_moduledef_getclasspath, 0, 0, IS_STRING, NULL, 0)
#endif
ZEND_END_ARG_INFO()

#if PHP_VERSION_ID >= 70200
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_phalconplus_base_moduledef_getclassname, 0, 0, IS_STRING, 0)
#else
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_phalconplus_base_moduledef_getclassname, 0, 0, IS_STRING, NULL, 0)
#endif
ZEND_END_ARG_INFO()

#if PHP_VERSION_ID >= 70200
ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_phalconplus_base_moduledef_getrunmode, 0, 0, PhalconPlus\\Enum\\RunMode, 0)
#else
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_phalconplus_base_moduledef_getrunmode, 0, 0, IS_OBJECT, "PhalconPlus\\Enum\\RunMode", 0)
#endif
ZEND_END_ARG_INFO()

#if PHP_VERSION_ID >= 70200
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_phalconplus_base_moduledef_getmapclassname, 0, 0, IS_STRING, 0)
#else
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_phalconplus_base_moduledef_getmapclassname, 0, 0, IS_STRING, NULL, 0)
#endif
ZEND_END_ARG_INFO()

#if PHP_VERSION_ID >= 70200
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_phalconplus_base_moduledef_getmode, 0, 0, IS_STRING, 0)
#else
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_phalconplus_base_moduledef_getmode, 0, 0, IS_STRING, NULL, 0)
#endif
ZEND_END_ARG_INFO()

#if PHP_VERSION_ID >= 70200
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_phalconplus_base_moduledef_getname, 0, 0, IS_STRING, 0)
#else
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_phalconplus_base_moduledef_getname, 0, 0, IS_STRING, NULL, 0)
#endif
ZEND_END_ARG_INFO()

#if PHP_VERSION_ID >= 70200
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_phalconplus_base_moduledef_getconfigpath, 0, 0, IS_STRING, 0)
#else
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_phalconplus_base_moduledef_getconfigpath, 0, 0, IS_STRING, NULL, 0)
#endif
ZEND_END_ARG_INFO()

#if PHP_VERSION_ID >= 70200
ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_phalconplus_base_moduledef_getconfig, 0, 0, Phalcon\\Config, 0)
#else
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_phalconplus_base_moduledef_getconfig, 0, 0, IS_OBJECT, "Phalcon\\Config", 0)
#endif
ZEND_END_ARG_INFO()

#if PHP_VERSION_ID >= 70200
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_phalconplus_base_moduledef_getdir, 0, 0, IS_STRING, 0)
#else
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_phalconplus_base_moduledef_getdir, 0, 0, IS_STRING, NULL, 0)
#endif
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(phalconplus_base_moduledef_method_entry) {
	PHP_ME(PhalconPlus_Base_ModuleDef, __construct, arginfo_phalconplus_base_moduledef___construct, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	PHP_ME(PhalconPlus_Base_ModuleDef, impl, arginfo_phalconplus_base_moduledef_impl, ZEND_ACC_PUBLIC)
	PHP_ME(PhalconPlus_Base_ModuleDef, getIsPrimary, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(PhalconPlus_Base_ModuleDef, getClassPath, arginfo_phalconplus_base_moduledef_getclasspath, ZEND_ACC_PUBLIC)
	PHP_ME(PhalconPlus_Base_ModuleDef, getClassName, arginfo_phalconplus_base_moduledef_getclassname, ZEND_ACC_PUBLIC)
	PHP_ME(PhalconPlus_Base_ModuleDef, getRunMode, arginfo_phalconplus_base_moduledef_getrunmode, ZEND_ACC_PUBLIC)
	PHP_ME(PhalconPlus_Base_ModuleDef, getMapClassName, arginfo_phalconplus_base_moduledef_getmapclassname, ZEND_ACC_PUBLIC)
	PHP_ME(PhalconPlus_Base_ModuleDef, getMode, arginfo_phalconplus_base_moduledef_getmode, ZEND_ACC_PUBLIC)
	PHP_ME(PhalconPlus_Base_ModuleDef, getName, arginfo_phalconplus_base_moduledef_getname, ZEND_ACC_PUBLIC)
	PHP_ME(PhalconPlus_Base_ModuleDef, getConfigPath, arginfo_phalconplus_base_moduledef_getconfigpath, ZEND_ACC_PUBLIC)
	PHP_ME(PhalconPlus_Base_ModuleDef, getConfig, arginfo_phalconplus_base_moduledef_getconfig, ZEND_ACC_PUBLIC)
	PHP_ME(PhalconPlus_Base_ModuleDef, getDir, arginfo_phalconplus_base_moduledef_getdir, ZEND_ACC_PUBLIC)
	PHP_FE_END
};
