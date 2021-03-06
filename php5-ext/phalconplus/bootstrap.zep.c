
#ifdef HAVE_CONFIG_H
#include "../ext_config.h"
#endif

#include <php.h>
#include "../php_ext.h"
#include "../ext.h"

#include <Zend/zend_operators.h>
#include <Zend/zend_exceptions.h>
#include <Zend/zend_interfaces.h>

#include "kernel/main.h"
#include "kernel/fcall.h"
#include "kernel/string.h"
#include "kernel/memory.h"
#include "kernel/operators.h"
#include "kernel/object.h"
#include "ext/spl/spl_exceptions.h"
#include "kernel/exception.h"
#include "kernel/array.h"
#include "kernel/concat.h"
#include "kernel/main.h"
#include "kernel/require.h"


ZEPHIR_INIT_CLASS(PhalconPlus_Bootstrap) {

	ZEPHIR_REGISTER_CLASS(PhalconPlus, Bootstrap, phalconplus, bootstrap, phalconplus_bootstrap_method_entry, ZEND_ACC_FINAL_CLASS);

	zend_declare_property_null(phalconplus_bootstrap_ce, SL("config"), ZEND_ACC_PROTECTED TSRMLS_CC);

	zend_declare_property_null(phalconplus_bootstrap_ce, SL("di"), ZEND_ACC_PROTECTED TSRMLS_CC);

	zend_declare_property_null(phalconplus_bootstrap_ce, SL("application"), ZEND_ACC_PROTECTED TSRMLS_CC);

	zend_declare_property_null(phalconplus_bootstrap_ce, SL("primaryModuleDef"), ZEND_ACC_PROTECTED TSRMLS_CC);

	zend_declare_property_null(phalconplus_bootstrap_ce, SL("activeModules"), ZEND_ACC_PROTECTED TSRMLS_CC);

	zend_declare_property_null(phalconplus_bootstrap_ce, SL("debug"), ZEND_ACC_PROTECTED TSRMLS_CC);

	zend_declare_property_string(phalconplus_bootstrap_ce, SL("env"), "dev", ZEND_ACC_PROTECTED TSRMLS_CC);

	phalconplus_bootstrap_ce->create_object = zephir_init_properties_PhalconPlus_Bootstrap;
	return SUCCESS;

}

PHP_METHOD(PhalconPlus_Bootstrap, __construct) {

	zend_bool _6;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zephir_fcall_cache_entry *_0 = NULL, *_8 = NULL, *_14 = NULL, *_17 = NULL, *_19 = NULL, *_22 = NULL, *_24 = NULL, *_26 = NULL;
	zval *moduleDir_param = NULL, *env = NULL, _1 = zval_used_for_init, *_2 = NULL, *_3, _4, *_5, *_7 = NULL, *_9, *_12, _13 = zval_used_for_init, *_15, *_16 = NULL, *_18 = NULL, *_20 = NULL, *_21 = NULL, *_23 = NULL, *_25 = NULL, *_10$$4, *_11$$4;
	zval *moduleDir = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &moduleDir_param);

	if (UNEXPECTED(Z_TYPE_P(moduleDir_param) != IS_STRING && Z_TYPE_P(moduleDir_param) != IS_NULL)) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'moduleDir' must be a string") TSRMLS_CC);
		RETURN_MM_NULL();
	}
	if (EXPECTED(Z_TYPE_P(moduleDir_param) == IS_STRING)) {
		zephir_get_strval(moduleDir, moduleDir_param);
	} else {
		ZEPHIR_INIT_VAR(moduleDir);
		ZVAL_EMPTY_STRING(moduleDir);
	}


	ZEPHIR_CALL_CE_STATIC(NULL, phalconplus_enum_sys_ce, "init", &_0, 52, moduleDir);
	zephir_check_call_status();
	ZEPHIR_SINIT_VAR(_1);
	ZVAL_STRING(&_1, "phalconplus.env", 0);
	ZEPHIR_CALL_FUNCTION(&_2, "get_cfg_var", NULL, 53, &_1);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(env);
	zephir_fast_trim(env, _2, NULL , ZEPHIR_TRIM_BOTH TSRMLS_CC);
	if (!(ZEPHIR_IS_EMPTY(env))) {
		zephir_update_property_this(getThis(), SL("env"), env TSRMLS_CC);
	}
	ZEPHIR_INIT_VAR(_3);
	ZEPHIR_GET_CONSTANT(_3, "PHP_SAPI");
	ZEPHIR_SINIT_NVAR(_1);
	ZVAL_LONG(&_1, 0);
	ZEPHIR_SINIT_VAR(_4);
	ZVAL_LONG(&_4, 3);
	ZEPHIR_INIT_VAR(_5);
	zephir_substr(_5, _3, 0 , 3 , 0);
	_6 = !ZEPHIR_IS_STRING(_5, "cli");
	if (_6) {
		_9 = zephir_fetch_nproperty_this(this_ptr, SL("env"), PH_NOISY_CC);
		ZEPHIR_CALL_CE_STATIC(&_7, phalconplus_enum_runenv_ce, "isinprod", &_8, 54, _9);
		zephir_check_call_status();
		_6 = !zephir_is_true(_7);
	}
	if (_6) {
		ZEPHIR_INIT_VAR(_10$$4);
		object_init_ex(_10$$4, zephir_get_internal_ce(SS("phalcon\\debug") TSRMLS_CC));
		if (zephir_has_constructor(_10$$4 TSRMLS_CC)) {
			ZEPHIR_CALL_METHOD(NULL, _10$$4, "__construct", NULL, 0);
			zephir_check_call_status();
		}
		zephir_update_property_this(getThis(), SL("debug"), _10$$4 TSRMLS_CC);
		_11$$4 = zephir_fetch_nproperty_this(this_ptr, SL("debug"), PH_NOISY_CC);
		ZEPHIR_CALL_METHOD(NULL, _11$$4, "listen", NULL, 0);
		zephir_check_call_status();
	}
	_12 = zephir_fetch_nproperty_this(this_ptr, SL("env"), PH_NOISY_CC);
	ZEPHIR_SINIT_VAR(_13);
	ZVAL_STRING(&_13, "APP_ENV", 0);
	ZEPHIR_CALL_FUNCTION(NULL, "define", &_14, 55, &_13, _12, ZEPHIR_GLOBAL(global_true));
	zephir_check_call_status();
	_15 = zephir_fetch_nproperty_this(this_ptr, SL("env"), PH_NOISY_CC);
	ZEPHIR_SINIT_NVAR(_13);
	ZVAL_STRING(&_13, "APP_RUN_ENV", 0);
	ZEPHIR_CALL_FUNCTION(NULL, "define", &_14, 55, &_13, _15, ZEPHIR_GLOBAL(global_true));
	zephir_check_call_status();
	ZEPHIR_CALL_CE_STATIC(&_16, phalconplus_enum_sys_ce, "getrootdir", &_17, 56);
	zephir_check_call_status();
	ZEPHIR_SINIT_NVAR(_13);
	ZVAL_STRING(&_13, "APP_ROOT_DIR", 0);
	ZEPHIR_CALL_FUNCTION(NULL, "define", &_14, 55, &_13, _16, ZEPHIR_GLOBAL(global_true));
	zephir_check_call_status();
	ZEPHIR_CALL_CE_STATIC(&_18, phalconplus_enum_sys_ce, "getprimarymoduledir", &_19, 57);
	zephir_check_call_status();
	ZEPHIR_SINIT_NVAR(_13);
	ZVAL_STRING(&_13, "APP_MODULE_DIR", 0);
	ZEPHIR_CALL_FUNCTION(NULL, "define", &_14, 55, &_13, _18, ZEPHIR_GLOBAL(global_true));
	zephir_check_call_status();
	ZEPHIR_CALL_CE_STATIC(&_20, phalconplus_enum_sys_ce, "getprimarymoduledir", &_19, 57);
	zephir_check_call_status();
	ZEPHIR_SINIT_NVAR(_13);
	ZVAL_STRING(&_13, "APP_PRI_MODULE_DIR", 0);
	ZEPHIR_CALL_FUNCTION(NULL, "define", &_14, 55, &_13, _20, ZEPHIR_GLOBAL(global_true));
	zephir_check_call_status();
	ZEPHIR_CALL_CE_STATIC(&_21, phalconplus_enum_sys_ce, "getcommondir", &_22, 58);
	zephir_check_call_status();
	ZEPHIR_SINIT_NVAR(_13);
	ZVAL_STRING(&_13, "APP_ROOT_COMMON_DIR", 0);
	ZEPHIR_CALL_FUNCTION(NULL, "define", &_14, 55, &_13, _21, ZEPHIR_GLOBAL(global_true));
	zephir_check_call_status();
	ZEPHIR_CALL_CE_STATIC(&_23, phalconplus_enum_sys_ce, "getgloballoaddir", &_24, 59);
	zephir_check_call_status();
	ZEPHIR_SINIT_NVAR(_13);
	ZVAL_STRING(&_13, "APP_ROOT_COMMON_LOAD_DIR", 0);
	ZEPHIR_CALL_FUNCTION(NULL, "define", &_14, 55, &_13, _23, ZEPHIR_GLOBAL(global_true));
	zephir_check_call_status();
	ZEPHIR_CALL_CE_STATIC(&_25, phalconplus_enum_sys_ce, "getglobalconfigdir", &_26, 60);
	zephir_check_call_status();
	ZEPHIR_SINIT_NVAR(_13);
	ZVAL_STRING(&_13, "APP_ROOT_COMMON_CONF_DIR", 0);
	ZEPHIR_CALL_FUNCTION(NULL, "define", &_14, 55, &_13, _25, ZEPHIR_GLOBAL(global_true));
	zephir_check_call_status();
	ZEPHIR_MM_RESTORE();

}

PHP_METHOD(PhalconPlus_Bootstrap, registerModule) {

	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *moduleDef, *_0, *_1 = NULL, *_5, *module = NULL, *_9, *_10 = NULL, *_2$$3, *_3$$3 = NULL, *_4$$3, *_6$$4, *_7$$4 = NULL, *_8$$4;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &moduleDef);



	_0 = zephir_fetch_nproperty_this(this_ptr, SL("activeModules"), PH_NOISY_CC);
	ZEPHIR_CALL_METHOD(&_1, moduleDef, "getname", NULL, 0);
	zephir_check_call_status();
	if (zephir_array_isset(_0, _1)) {
		ZEPHIR_INIT_VAR(_2$$3);
		object_init_ex(_2$$3, zend_exception_get_default(TSRMLS_C));
		ZEPHIR_CALL_METHOD(&_3$$3, moduleDef, "getname", NULL, 0);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(_4$$3);
		ZEPHIR_CONCAT_SV(_4$$3, "Module already loaded: ", _3$$3);
		ZEPHIR_CALL_METHOD(NULL, _2$$3, "__construct", NULL, 7, _4$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(_2$$3, "phalconplus/Bootstrap.zep", 57 TSRMLS_CC);
		ZEPHIR_MM_RESTORE();
		return;
	}
	_5 = zephir_fetch_nproperty_this(this_ptr, SL("di"), PH_NOISY_CC);
	if (Z_TYPE_P(_5) == IS_NULL) {
		ZEPHIR_INIT_VAR(_6$$4);
		object_init_ex(_6$$4, zend_exception_get_default(TSRMLS_C));
		ZEPHIR_CALL_METHOD(&_7$$4, moduleDef, "getname", NULL, 0);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(_8$$4);
		ZEPHIR_CONCAT_SV(_8$$4, "DI doesn't load yet, failed to register module ", _7$$4);
		ZEPHIR_CALL_METHOD(NULL, _6$$4, "__construct", NULL, 7, _8$$4);
		zephir_check_call_status();
		zephir_throw_exception_debug(_6$$4, "phalconplus/Bootstrap.zep", 60 TSRMLS_CC);
		ZEPHIR_MM_RESTORE();
		return;
	}
	_9 = zephir_fetch_nproperty_this(this_ptr, SL("di"), PH_NOISY_CC);
	ZEPHIR_CALL_METHOD(&module, moduleDef, "impl", NULL, 0, _9);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(NULL, module, "registerautoloaders", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(NULL, module, "registerservices", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&_10, moduleDef, "getname", NULL, 0);
	zephir_check_call_status();
	zephir_update_property_array(this_ptr, SL("activeModules"), _10, module TSRMLS_CC);
	RETURN_CCTOR(module);

}

PHP_METHOD(PhalconPlus_Bootstrap, initConf) {

	zval *globalConfPath = NULL, *moduleConf = NULL, *_1 = NULL, *_8, *_9, *_10, *_11, *_12 = NULL, _13, *_14, *_15, *_2$$3, *_3$$3, *_4$$3, *_6$$4, *_7$$4 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zephir_fcall_cache_entry *_0 = NULL, *_5 = NULL;

	ZEPHIR_MM_GROW();

	ZEPHIR_INIT_VAR(globalConfPath);
	ZVAL_STRING(globalConfPath, "", 1);
	ZEPHIR_INIT_VAR(moduleConf);
	ZVAL_NULL(moduleConf);
	ZEPHIR_CALL_CE_STATIC(&globalConfPath, phalconplus_enum_sys_ce, "getglobalconfigpath", &_0, 61);
	zephir_check_call_status();
	ZEPHIR_CALL_FUNCTION(&_1, "is_file", NULL, 44, globalConfPath);
	zephir_check_call_status();
	if (!(zephir_is_true(_1))) {
		ZEPHIR_INIT_VAR(_2$$3);
		ZEPHIR_CONCAT_SV(_2$$3, "PHP Notice:  PhalconPlus\\Bootstrap Global config file not exists: ", globalConfPath);
		ZEPHIR_CALL_FUNCTION(NULL, "error_log", NULL, 62, _2$$3);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(_3$$3);
		object_init_ex(_3$$3, zephir_get_internal_ce(SS("phalcon\\config") TSRMLS_CC));
		ZEPHIR_INIT_VAR(_4$$3);
		array_init(_4$$3);
		ZEPHIR_CALL_METHOD(NULL, _3$$3, "__construct", &_5, 0, _4$$3);
		zephir_check_call_status();
		zephir_update_property_this(getThis(), SL("config"), _3$$3 TSRMLS_CC);
	} else {
		ZEPHIR_INIT_VAR(_6$$4);
		object_init_ex(_6$$4, zephir_get_internal_ce(SS("phalcon\\config") TSRMLS_CC));
		ZEPHIR_CALL_METHOD(&_7$$4, this_ptr, "load", NULL, 41, globalConfPath);
		zephir_check_call_status();
		ZEPHIR_CALL_METHOD(NULL, _6$$4, "__construct", &_5, 0, _7$$4);
		zephir_check_call_status();
		zephir_update_property_this(getThis(), SL("config"), _6$$4 TSRMLS_CC);
	}
	ZEPHIR_INIT_VAR(_8);
	object_init_ex(_8, phalconplus_base_moduledef_ce);
	ZEPHIR_INIT_VAR(_9);
	ZEPHIR_GET_CONSTANT(_9, "APP_MODULE_DIR");
	ZEPHIR_INIT_VAR(_10);
	ZVAL_BOOL(_10, 1);
	ZEPHIR_CALL_METHOD(NULL, _8, "__construct", NULL, 63, this_ptr, _9, _10);
	zephir_check_call_status();
	zephir_update_property_this(getThis(), SL("primaryModuleDef"), _8 TSRMLS_CC);
	_11 = zephir_fetch_nproperty_this(this_ptr, SL("primaryModuleDef"), PH_NOISY_CC);
	ZEPHIR_CALL_METHOD(&_12, _11, "getmode", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_SINIT_VAR(_13);
	ZVAL_STRING(&_13, "APP_RUN_MODE", 0);
	ZEPHIR_CALL_FUNCTION(NULL, "define", NULL, 55, &_13, _12, ZEPHIR_GLOBAL(global_true));
	zephir_check_call_status();
	_14 = zephir_fetch_nproperty_this(this_ptr, SL("primaryModuleDef"), PH_NOISY_CC);
	ZEPHIR_CALL_METHOD(&moduleConf, _14, "getconfig", NULL, 0);
	zephir_check_call_status();
	_15 = zephir_fetch_nproperty_this(this_ptr, SL("config"), PH_NOISY_CC);
	ZEPHIR_CALL_METHOD(NULL, _15, "merge", NULL, 0, moduleConf);
	zephir_check_call_status();
	RETURN_THIS();

}

PHP_METHOD(PhalconPlus_Bootstrap, exec) {

	zval *_2;
	zval *handleMethod = NULL, *_0, *_1 = NULL, *_3;
	zend_long ZEPHIR_LAST_CALL_STATUS;

	ZEPHIR_MM_GROW();

	ZEPHIR_INIT_VAR(handleMethod);
	ZVAL_STRING(handleMethod, "exec", 1);
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "initconf", NULL, 64);
	zephir_check_call_status();
	_0 = zephir_fetch_nproperty_this(this_ptr, SL("primaryModuleDef"), PH_NOISY_CC);
	ZEPHIR_CALL_METHOD(&_1, _0, "getmapclassname", NULL, 0);
	zephir_check_call_status();
	zephir_concat_self(&handleMethod, _1 TSRMLS_CC);
	ZEPHIR_INIT_VAR(_2);
	zephir_create_array(_2, 2, 0 TSRMLS_CC);
	zephir_array_fast_append(_2, this_ptr);
	zephir_array_fast_append(_2, handleMethod);
	ZEPHIR_INIT_VAR(_3);
	zephir_get_args(_3 TSRMLS_CC);
	ZEPHIR_CALL_USER_FUNC_ARRAY(return_value, _2, _3);
	zephir_check_call_status();
	RETURN_MM();

}

PHP_METHOD(PhalconPlus_Bootstrap, execModule) {

	zend_long ZEPHIR_LAST_CALL_STATUS;
	zend_bool needHandle;
	zval *uri = NULL, *needHandle_param = NULL, *_0, *_1, *_2, *_3, *_4, *globalScript = NULL, *_5, *_6 = NULL, *_8, *_9 = NULL, *_10, *_14 = NULL, *_7$$5, *_11$$7, *_12$$7 = NULL, *_13$$7 = NULL, *router$$8 = NULL, *newUri$$8 = NULL, *_15$$8, *_16$$8, *_17$$8 = NULL, *_18$$8 = NULL, *_19$$8, *_20$$8 = NULL, *_21$$8 = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 2, &uri, &needHandle_param);

	if (!uri) {
		uri = ZEPHIR_GLOBAL(global_null);
	}
	if (!needHandle_param) {
		needHandle = 1;
	} else {
		needHandle = zephir_get_boolval(needHandle_param);
	}


	ZEPHIR_OBS_VAR(_0);
	zephir_read_property_this(&_0, this_ptr, SL("config"), PH_NOISY_CC);
	if (ZEPHIR_IS_EMPTY(_0)) {
		ZEPHIR_CALL_METHOD(NULL, this_ptr, "initconf", NULL, 64);
		zephir_check_call_status();
	}
	ZEPHIR_INIT_VAR(_1);
	object_init_ex(_1, zephir_get_internal_ce(SS("phalcon\\di\\factorydefault") TSRMLS_CC));
	ZEPHIR_CALL_METHOD(NULL, _1, "__construct", NULL, 0);
	zephir_check_call_status();
	zephir_update_property_this(getThis(), SL("di"), _1 TSRMLS_CC);
	ZEPHIR_INIT_VAR(_2);
	object_init_ex(_2, zephir_get_internal_ce(SS("phalcon\\mvc\\application") TSRMLS_CC));
	ZEPHIR_CALL_METHOD(NULL, _2, "__construct", NULL, 0);
	zephir_check_call_status();
	zephir_update_property_this(getThis(), SL("application"), _2 TSRMLS_CC);
	_3 = zephir_fetch_nproperty_this(this_ptr, SL("application"), PH_NOISY_CC);
	_4 = zephir_fetch_nproperty_this(this_ptr, SL("di"), PH_NOISY_CC);
	ZEPHIR_CALL_METHOD(NULL, _3, "setdi", NULL, 0, _4);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(_5);
	ZEPHIR_GET_CONSTANT(_5, "APP_ROOT_COMMON_LOAD_DIR");
	ZEPHIR_INIT_VAR(globalScript);
	ZEPHIR_CONCAT_VS(globalScript, _5, "default-web.php");
	ZEPHIR_CALL_FUNCTION(&_6, "is_file", NULL, 44, globalScript);
	zephir_check_call_status();
	if (zephir_is_true(_6)) {
		ZEPHIR_CALL_METHOD(NULL, this_ptr, "load", NULL, 41, globalScript);
		zephir_check_call_status();
	} else {
		ZEPHIR_INIT_VAR(_7$$5);
		ZEPHIR_CONCAT_SV(_7$$5, "PHP Notice:  PhalconPlus\\Bootstrap Global load file not exists: ", globalScript);
		ZEPHIR_CALL_FUNCTION(NULL, "error_log", NULL, 62, _7$$5);
		zephir_check_call_status();
	}
	_8 = zephir_fetch_nproperty_this(this_ptr, SL("di"), PH_NOISY_CC);
	ZEPHIR_INIT_VAR(_9);
	ZVAL_STRING(_9, "bootstrap", ZEPHIR_TEMP_PARAM_COPY);
	ZEPHIR_CALL_METHOD(NULL, _8, "setshared", NULL, 0, _9, this_ptr);
	zephir_check_temp_parameter(_9);
	zephir_check_call_status();
	_10 = zephir_fetch_nproperty_this(this_ptr, SL("primaryModuleDef"), PH_NOISY_CC);
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "registermodule", NULL, 65, _10);
	zephir_check_call_status();
	if (!(needHandle)) {
		RETURN_MM_BOOL(1);
	}

	/* try_start_1: */

		_11$$7 = zephir_fetch_nproperty_this(this_ptr, SL("application"), PH_NOISY_CC);
		ZEPHIR_CALL_METHOD(&_12$$7, _11$$7, "handle", NULL, 0, uri);
		zephir_check_call_status_or_jump(try_end_1);
		ZEPHIR_CALL_METHOD(&_13$$7, _12$$7, "getcontent", NULL, 0);
		zephir_check_call_status_or_jump(try_end_1);
		zend_print_zval(_13$$7, 0);

	try_end_1:

	if (EG(exception)) {
		ZEPHIR_INIT_NVAR(_9);
		ZEPHIR_CPY_WRT(_9, EG(exception));
		ZEPHIR_INIT_VAR(_14);
		if (zephir_instance_of_ev(_9, zephir_get_internal_ce(SS("phalcon\\mvc\\application\\exception") TSRMLS_CC) TSRMLS_CC)) {
			zend_clear_exception(TSRMLS_C);
			ZEPHIR_CPY_WRT(_14, _9);
			_15$$8 = zephir_fetch_nproperty_this(this_ptr, SL("di"), PH_NOISY_CC);
			ZEPHIR_INIT_VAR(_16$$8);
			ZVAL_STRING(_16$$8, "router", ZEPHIR_TEMP_PARAM_COPY);
			ZEPHIR_CALL_METHOD(&router$$8, _15$$8, "get", NULL, 0, _16$$8);
			zephir_check_temp_parameter(_16$$8);
			zephir_check_call_status();
			ZEPHIR_CALL_METHOD(&_17$$8, router$$8, "getdefaultmodule", NULL, 0);
			zephir_check_call_status();
			ZEPHIR_CALL_METHOD(&_18$$8, router$$8, "getrewriteuri", NULL, 0);
			zephir_check_call_status();
			ZEPHIR_INIT_VAR(newUri$$8);
			ZEPHIR_CONCAT_SVV(newUri$$8, "/", _17$$8, _18$$8);
			_19$$8 = zephir_fetch_nproperty_this(this_ptr, SL("application"), PH_NOISY_CC);
			ZEPHIR_CALL_METHOD(&_20$$8, _19$$8, "handle", NULL, 0, newUri$$8);
			zephir_check_call_status();
			ZEPHIR_CALL_METHOD(&_21$$8, _20$$8, "getcontent", NULL, 0);
			zephir_check_call_status();
			zend_print_zval(_21$$8, 0);
		}
	}
	ZEPHIR_MM_RESTORE();

}

PHP_METHOD(PhalconPlus_Bootstrap, execSrv) {

	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *needHandle_param = NULL, *backendSrv = NULL, *_0, *_1, *_2, *_3 = NULL, *globalScript = NULL, *_4 = NULL, *_6, *_7, *_8 = NULL, *_9 = NULL, *_13, *_5$$5, *_10$$7, *_11$$7, *_12$$9;
	zend_bool needHandle;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 1, &needHandle_param);

	if (!needHandle_param) {
		needHandle = 1;
	} else {
		needHandle = zephir_get_boolval(needHandle_param);
	}


	ZEPHIR_INIT_VAR(backendSrv);
	ZVAL_NULL(backendSrv);
	ZEPHIR_OBS_VAR(_0);
	zephir_read_property_this(&_0, this_ptr, SL("config"), PH_NOISY_CC);
	if (ZEPHIR_IS_EMPTY(_0)) {
		ZEPHIR_CALL_METHOD(NULL, this_ptr, "initconf", NULL, 64);
		zephir_check_call_status();
	}
	ZEPHIR_INIT_VAR(_1);
	object_init_ex(_1, zephir_get_internal_ce(SS("phalcon\\di\\factorydefault") TSRMLS_CC));
	ZEPHIR_CALL_METHOD(NULL, _1, "__construct", NULL, 0);
	zephir_check_call_status();
	zephir_update_property_this(getThis(), SL("di"), _1 TSRMLS_CC);
	_2 = zephir_fetch_nproperty_this(this_ptr, SL("di"), PH_NOISY_CC);
	ZEPHIR_INIT_VAR(_3);
	ZVAL_STRING(_3, "bootstrap", ZEPHIR_TEMP_PARAM_COPY);
	ZEPHIR_CALL_METHOD(NULL, _2, "setshared", NULL, 0, _3, this_ptr);
	zephir_check_temp_parameter(_3);
	zephir_check_call_status();
	ZEPHIR_INIT_NVAR(_3);
	ZEPHIR_GET_CONSTANT(_3, "APP_ROOT_COMMON_LOAD_DIR");
	ZEPHIR_INIT_VAR(globalScript);
	ZEPHIR_CONCAT_VS(globalScript, _3, "default-web.php");
	ZEPHIR_CALL_FUNCTION(&_4, "is_file", NULL, 44, globalScript);
	zephir_check_call_status();
	if (zephir_is_true(_4)) {
		ZEPHIR_CALL_METHOD(NULL, this_ptr, "load", NULL, 41, globalScript);
		zephir_check_call_status();
	} else {
		ZEPHIR_INIT_VAR(_5$$5);
		ZEPHIR_CONCAT_SV(_5$$5, "PHP Notice:  PhalconPlus\\Bootstrap Global load file not exists: ", globalScript);
		ZEPHIR_CALL_FUNCTION(NULL, "error_log", NULL, 62, _5$$5);
		zephir_check_call_status();
	}
	_6 = zephir_fetch_nproperty_this(this_ptr, SL("primaryModuleDef"), PH_NOISY_CC);
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "registermodule", NULL, 65, _6);
	zephir_check_call_status();
	if (!(needHandle)) {
		RETURN_MM_BOOL(1);
	}
	_7 = zephir_fetch_nproperty_this(this_ptr, SL("di"), PH_NOISY_CC);
	ZEPHIR_INIT_VAR(_9);
	ZVAL_STRING(_9, "backendSrv", ZEPHIR_TEMP_PARAM_COPY);
	ZEPHIR_CALL_METHOD(&_8, _7, "has", NULL, 0, _9);
	zephir_check_temp_parameter(_9);
	zephir_check_call_status();
	if (zephir_is_true(_8)) {
		_10$$7 = zephir_fetch_nproperty_this(this_ptr, SL("di"), PH_NOISY_CC);
		ZEPHIR_INIT_VAR(_11$$7);
		ZVAL_STRING(_11$$7, "backendSrv", ZEPHIR_TEMP_PARAM_COPY);
		ZEPHIR_CALL_METHOD(&backendSrv, _10$$7, "get", NULL, 0, _11$$7);
		zephir_check_temp_parameter(_11$$7);
		zephir_check_call_status();
		if (!(zephir_instance_of_ev(backendSrv, phalconplus_rpc_server_abstractserver_ce TSRMLS_CC))) {
			ZEPHIR_THROW_EXCEPTION_DEBUG_STR(zend_exception_get_default(TSRMLS_C), "Service object(DI[\"backendSrv\"]) must be type of \\PhalconPlus\\RPC\\Server\\AbstractServer", "phalconplus/Bootstrap.zep", 177);
			return;
		}
	} else {
		ZEPHIR_INIT_NVAR(backendSrv);
		object_init_ex(backendSrv, phalconplus_base_simpleserver_ce);
		_12$$9 = zephir_fetch_nproperty_this(this_ptr, SL("di"), PH_NOISY_CC);
		ZEPHIR_CALL_METHOD(NULL, backendSrv, "__construct", NULL, 66, _12$$9);
		zephir_check_call_status();
	}
	ZEPHIR_INIT_NVAR(_9);
	object_init_ex(_9, zephir_get_internal_ce(SS("yar_server") TSRMLS_CC));
	ZEPHIR_CALL_METHOD(NULL, _9, "__construct", NULL, 0, backendSrv);
	zephir_check_call_status();
	zephir_update_property_this(getThis(), SL("application"), _9 TSRMLS_CC);
	_13 = zephir_fetch_nproperty_this(this_ptr, SL("application"), PH_NOISY_CC);
	ZEPHIR_CALL_METHOD(NULL, _13, "handle", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_MM_RESTORE();

}

PHP_METHOD(PhalconPlus_Bootstrap, execTask) {

	zend_bool _1;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *argv_param = NULL, *di = NULL, *needHandle = NULL, *_0, *_3, *_4, *_5, *globalScript = NULL, *_6, *_7 = NULL, *_9, *_10, *_11, *_12, *_2$$4, *_8$$7;
	zval *argv = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 2, &argv_param, &di, &needHandle);

	zephir_get_arrval(argv, argv_param);
	if (!di) {
		di = ZEPHIR_GLOBAL(global_null);
	}
	if (!needHandle) {
		needHandle = ZEPHIR_GLOBAL(global_true);
	}


	ZEPHIR_OBS_VAR(_0);
	zephir_read_property_this(&_0, this_ptr, SL("config"), PH_NOISY_CC);
	if (ZEPHIR_IS_EMPTY(_0)) {
		ZEPHIR_CALL_METHOD(NULL, this_ptr, "initconf", NULL, 64);
		zephir_check_call_status();
	}
	_1 = Z_TYPE_P(di) == IS_NULL;
	if (!(_1)) {
		_1 = !((zephir_instance_of_ev(di, zephir_get_internal_ce(SS("phalcon\\di\\factorydefault\\cli") TSRMLS_CC) TSRMLS_CC)));
	}
	if (_1) {
		ZEPHIR_INIT_VAR(_2$$4);
		object_init_ex(_2$$4, zephir_get_internal_ce(SS("phalcon\\di\\factorydefault\\cli") TSRMLS_CC));
		ZEPHIR_CALL_METHOD(NULL, _2$$4, "__construct", NULL, 0);
		zephir_check_call_status();
		zephir_update_property_this(getThis(), SL("di"), _2$$4 TSRMLS_CC);
	} else {
		zephir_update_property_this(getThis(), SL("di"), di TSRMLS_CC);
	}
	ZEPHIR_INIT_VAR(_3);
	object_init_ex(_3, zephir_get_internal_ce(SS("phalcon\\cli\\console") TSRMLS_CC));
	ZEPHIR_CALL_METHOD(NULL, _3, "__construct", NULL, 0);
	zephir_check_call_status();
	zephir_update_property_this(getThis(), SL("application"), _3 TSRMLS_CC);
	_4 = zephir_fetch_nproperty_this(this_ptr, SL("application"), PH_NOISY_CC);
	_5 = zephir_fetch_nproperty_this(this_ptr, SL("di"), PH_NOISY_CC);
	ZEPHIR_CALL_METHOD(NULL, _4, "setdi", NULL, 0, _5);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(_6);
	ZEPHIR_GET_CONSTANT(_6, "APP_ROOT_COMMON_LOAD_DIR");
	ZEPHIR_INIT_VAR(globalScript);
	ZEPHIR_CONCAT_VS(globalScript, _6, "default-cli.php");
	ZEPHIR_CALL_FUNCTION(&_7, "is_file", NULL, 44, globalScript);
	zephir_check_call_status();
	if (zephir_is_true(_7)) {
		ZEPHIR_CALL_METHOD(NULL, this_ptr, "load", NULL, 41, globalScript);
		zephir_check_call_status();
	} else {
		ZEPHIR_INIT_VAR(_8$$7);
		ZEPHIR_CONCAT_SV(_8$$7, "PHP Notice:  PhalconPlus\\Bootstrap Global load file not exists: ", globalScript);
		ZEPHIR_CALL_FUNCTION(NULL, "error_log", NULL, 62, _8$$7);
		zephir_check_call_status();
	}
	_9 = zephir_fetch_nproperty_this(this_ptr, SL("di"), PH_NOISY_CC);
	ZEPHIR_INIT_VAR(_10);
	ZVAL_STRING(_10, "bootstrap", ZEPHIR_TEMP_PARAM_COPY);
	ZEPHIR_CALL_METHOD(NULL, _9, "setshared", NULL, 0, _10, this_ptr);
	zephir_check_temp_parameter(_10);
	zephir_check_call_status();
	_11 = zephir_fetch_nproperty_this(this_ptr, SL("primaryModuleDef"), PH_NOISY_CC);
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "registermodule", NULL, 65, _11);
	zephir_check_call_status();
	if (!(zephir_is_true(needHandle))) {
		RETURN_MM_BOOL(1);
	}
	_12 = zephir_fetch_nproperty_this(this_ptr, SL("application"), PH_NOISY_CC);
	ZEPHIR_RETURN_CALL_METHOD(_12, "handle", NULL, 0, argv);
	zephir_check_call_status();
	RETURN_MM();

}

PHP_METHOD(PhalconPlus_Bootstrap, getPrimaryModuleDef) {

	

	RETURN_MEMBER(getThis(), "primaryModuleDef");

}

PHP_METHOD(PhalconPlus_Bootstrap, getPrimaryModule) {

	zval *name = NULL, *_0, *_1, *_4, *_5, *_2$$3, *_3$$3;
	zend_long ZEPHIR_LAST_CALL_STATUS;

	ZEPHIR_MM_GROW();

	_0 = zephir_fetch_nproperty_this(this_ptr, SL("primaryModuleDef"), PH_NOISY_CC);
	ZEPHIR_CALL_METHOD(&name, _0, "getname", NULL, 0);
	zephir_check_call_status();
	_1 = zephir_fetch_nproperty_this(this_ptr, SL("activeModules"), PH_NOISY_CC);
	if (!(zephir_array_isset(_1, name))) {
		ZEPHIR_INIT_VAR(_2$$3);
		object_init_ex(_2$$3, zend_exception_get_default(TSRMLS_C));
		ZEPHIR_INIT_VAR(_3$$3);
		ZEPHIR_CONCAT_SV(_3$$3, "Module not exists: ", name);
		ZEPHIR_CALL_METHOD(NULL, _2$$3, "__construct", NULL, 7, _3$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(_2$$3, "phalconplus/Bootstrap.zep", 233 TSRMLS_CC);
		ZEPHIR_MM_RESTORE();
		return;
	}
	_4 = zephir_fetch_nproperty_this(this_ptr, SL("activeModules"), PH_NOISY_CC);
	zephir_array_fetch(&_5, _4, name, PH_NOISY | PH_READONLY, "phalconplus/Bootstrap.zep", 235 TSRMLS_CC);
	RETURN_CTOR(_5);

}

PHP_METHOD(PhalconPlus_Bootstrap, getModule) {

	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *name_param = NULL, *_0, *_3, *_4, *_1$$3;
	zval *name = NULL, *_2$$3;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &name_param);

	if (UNEXPECTED(Z_TYPE_P(name_param) != IS_STRING && Z_TYPE_P(name_param) != IS_NULL)) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'name' must be a string") TSRMLS_CC);
		RETURN_MM_NULL();
	}
	if (EXPECTED(Z_TYPE_P(name_param) == IS_STRING)) {
		zephir_get_strval(name, name_param);
	} else {
		ZEPHIR_INIT_VAR(name);
		ZVAL_EMPTY_STRING(name);
	}


	_0 = zephir_fetch_nproperty_this(this_ptr, SL("activeModules"), PH_NOISY_CC);
	if (!(zephir_array_isset(_0, name))) {
		ZEPHIR_INIT_VAR(_1$$3);
		object_init_ex(_1$$3, zend_exception_get_default(TSRMLS_C));
		ZEPHIR_INIT_VAR(_2$$3);
		ZEPHIR_CONCAT_SV(_2$$3, "Module not exists: ", name);
		ZEPHIR_CALL_METHOD(NULL, _1$$3, "__construct", NULL, 7, _2$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(_1$$3, "phalconplus/Bootstrap.zep", 241 TSRMLS_CC);
		ZEPHIR_MM_RESTORE();
		return;
	}
	_3 = zephir_fetch_nproperty_this(this_ptr, SL("activeModules"), PH_NOISY_CC);
	zephir_array_fetch(&_4, _3, name, PH_NOISY | PH_READONLY, "phalconplus/Bootstrap.zep", 243 TSRMLS_CC);
	RETURN_CTOR(_4);

}

PHP_METHOD(PhalconPlus_Bootstrap, getModuleDef) {

	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *name_param = NULL, *_0, *_3, *_4, *_1$$3;
	zval *name = NULL, *_2$$3;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &name_param);

	if (UNEXPECTED(Z_TYPE_P(name_param) != IS_STRING && Z_TYPE_P(name_param) != IS_NULL)) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'name' must be a string") TSRMLS_CC);
		RETURN_MM_NULL();
	}
	if (EXPECTED(Z_TYPE_P(name_param) == IS_STRING)) {
		zephir_get_strval(name, name_param);
	} else {
		ZEPHIR_INIT_VAR(name);
		ZVAL_EMPTY_STRING(name);
	}


	_0 = zephir_fetch_nproperty_this(this_ptr, SL("activeModules"), PH_NOISY_CC);
	if (!(zephir_array_isset(_0, name))) {
		ZEPHIR_INIT_VAR(_1$$3);
		object_init_ex(_1$$3, zend_exception_get_default(TSRMLS_C));
		ZEPHIR_INIT_VAR(_2$$3);
		ZEPHIR_CONCAT_SV(_2$$3, "Module not exists: ", name);
		ZEPHIR_CALL_METHOD(NULL, _1$$3, "__construct", NULL, 7, _2$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(_1$$3, "phalconplus/Bootstrap.zep", 249 TSRMLS_CC);
		ZEPHIR_MM_RESTORE();
		return;
	}
	_3 = zephir_fetch_nproperty_this(this_ptr, SL("activeModules"), PH_NOISY_CC);
	zephir_array_fetch(&_4, _3, name, PH_NOISY | PH_READONLY, "phalconplus/Bootstrap.zep", 251 TSRMLS_CC);
	ZEPHIR_RETURN_CALL_METHOD(_4, "getdef", NULL, 0);
	zephir_check_call_status();
	RETURN_MM();

}

PHP_METHOD(PhalconPlus_Bootstrap, dependModule) {

	zend_long ZEPHIR_LAST_CALL_STATUS;
	zephir_fcall_cache_entry *_0 = NULL;
	zval *moduleName_param = NULL, *module = NULL, *moduleDef = NULL, *moduleDir = NULL, *moduleConf = NULL, *_1 = NULL, *_2 = NULL, *_3;
	zval *moduleName = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &moduleName_param);

	if (UNEXPECTED(Z_TYPE_P(moduleName_param) != IS_STRING && Z_TYPE_P(moduleName_param) != IS_NULL)) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'moduleName' must be a string") TSRMLS_CC);
		RETURN_MM_NULL();
	}
	if (EXPECTED(Z_TYPE_P(moduleName_param) == IS_STRING)) {
		zephir_get_strval(moduleName, moduleName_param);
	} else {
		ZEPHIR_INIT_VAR(moduleName);
		ZVAL_EMPTY_STRING(moduleName);
	}


	ZEPHIR_CALL_CE_STATIC(&moduleDir, phalconplus_enum_sys_ce, "getmoduledirbyname", &_0, 67, moduleName);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(moduleDef);
	object_init_ex(moduleDef, phalconplus_base_moduledef_ce);
	ZEPHIR_CALL_METHOD(NULL, moduleDef, "__construct", NULL, 63, this_ptr, moduleDir);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&module, this_ptr, "registermodule", NULL, 65, moduleDef);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(moduleConf);
	object_init_ex(moduleConf, zephir_get_internal_ce(SS("phalcon\\config") TSRMLS_CC));
	ZEPHIR_CALL_METHOD(&_2, moduleDef, "getconfigpath", NULL, 68);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&_1, this_ptr, "load", NULL, 41, _2);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(NULL, moduleConf, "__construct", NULL, 0, _1);
	zephir_check_call_status();
	_3 = zephir_fetch_nproperty_this(this_ptr, SL("config"), PH_NOISY_CC);
	ZEPHIR_CALL_METHOD(NULL, moduleConf, "merge", NULL, 0, _3);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "setconfig", NULL, 69, moduleConf);
	zephir_check_call_status();
	RETURN_CCTOR(module);

}

PHP_METHOD(PhalconPlus_Bootstrap, isDebug) {

	zval *_0;


	_0 = zephir_fetch_nproperty_this(this_ptr, SL("debug"), PH_NOISY_CC);
	RETURN_BOOL(Z_TYPE_P(_0) != IS_NULL);

}

PHP_METHOD(PhalconPlus_Bootstrap, getDebug) {

	

	RETURN_MEMBER(getThis(), "debug");

}

PHP_METHOD(PhalconPlus_Bootstrap, getEnv) {

	

	RETURN_MEMBER(getThis(), "env");

}

PHP_METHOD(PhalconPlus_Bootstrap, getConfig) {

	

	RETURN_MEMBER(getThis(), "config");

}

PHP_METHOD(PhalconPlus_Bootstrap, setConfig) {

	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *config, *globalConf = NULL, *_0, *_1 = NULL, *_2 = NULL, *_4, *_5, *_3$$4;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &config);



	_0 = zephir_fetch_nproperty_this(this_ptr, SL("di"), PH_NOISY_CC);
	ZEPHIR_INIT_VAR(_2);
	ZVAL_STRING(_2, "config", ZEPHIR_TEMP_PARAM_COPY);
	ZEPHIR_CALL_METHOD(&_1, _0, "has", NULL, 0, _2);
	zephir_check_temp_parameter(_2);
	zephir_check_call_status();
	if (!(zephir_is_true(_1))) {
		ZEPHIR_INIT_VAR(globalConf);
		object_init_ex(globalConf, zephir_get_internal_ce(SS("phalcon\\config") TSRMLS_CC));
		ZEPHIR_CALL_METHOD(NULL, globalConf, "__construct", NULL, 0);
		zephir_check_call_status();
	} else {
		_3$$4 = zephir_fetch_nproperty_this(this_ptr, SL("di"), PH_NOISY_CC);
		ZEPHIR_CALL_METHOD(&globalConf, _3$$4, "getconfig", NULL, 0);
		zephir_check_call_status();
	}
	ZEPHIR_CALL_METHOD(NULL, globalConf, "merge", NULL, 0, config);
	zephir_check_call_status();
	zephir_update_property_this(getThis(), SL("config"), globalConf TSRMLS_CC);
	_4 = zephir_fetch_nproperty_this(this_ptr, SL("di"), PH_NOISY_CC);
	_5 = zephir_fetch_nproperty_this(this_ptr, SL("config"), PH_NOISY_CC);
	ZEPHIR_INIT_NVAR(_2);
	ZVAL_STRING(_2, "config", ZEPHIR_TEMP_PARAM_COPY);
	ZEPHIR_CALL_METHOD(NULL, _4, "set", NULL, 0, _2, _5);
	zephir_check_temp_parameter(_2);
	zephir_check_call_status();
	RETURN_THIS();

}

PHP_METHOD(PhalconPlus_Bootstrap, getDI) {

	

	RETURN_MEMBER(getThis(), "di");

}

PHP_METHOD(PhalconPlus_Bootstrap, load) {

	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *filePath, *_0 = NULL, *rootPath = NULL, *loader = NULL, *config = NULL, *application = NULL, *bootstrap = NULL, *di = NULL, *_3 = NULL, *_4 = NULL, *_5 = NULL, *_6, *_7 = NULL, *_8 = NULL, *_9 = NULL, *_10 = NULL, *_11 = NULL, *_1$$3, *_2$$3;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &filePath);



	ZEPHIR_CALL_FUNCTION(&_0, "is_file", NULL, 44, filePath);
	zephir_check_call_status();
	if (!(zephir_is_true(_0))) {
		ZEPHIR_INIT_VAR(_1$$3);
		object_init_ex(_1$$3, zend_exception_get_default(TSRMLS_C));
		ZEPHIR_INIT_VAR(_2$$3);
		ZEPHIR_CONCAT_SV(_2$$3, "The file you try to load is not exists. file position: ", filePath);
		ZEPHIR_CALL_METHOD(NULL, _1$$3, "__construct", NULL, 7, _2$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(_1$$3, "phalconplus/Bootstrap.zep", 317 TSRMLS_CC);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(rootPath);
	ZVAL_STRING(rootPath, "rootPath", 1);
	ZEPHIR_INIT_VAR(loader);
	ZVAL_STRING(loader, "loader", 1);
	ZEPHIR_INIT_VAR(config);
	ZVAL_STRING(config, "config", 1);
	ZEPHIR_INIT_VAR(application);
	ZVAL_STRING(application, "application", 1);
	ZEPHIR_INIT_VAR(bootstrap);
	ZVAL_STRING(bootstrap, "bootstrap", 1);
	ZEPHIR_INIT_VAR(di);
	ZVAL_STRING(di, "di", 1);
	ZEPHIR_INIT_VAR(_3);
	ZEPHIR_GET_CONSTANT(_3, "APP_ROOT_DIR");
	ZEPHIR_CPY_WRT(_4, _3);
	if (zephir_set_symbol(rootPath, _4 TSRMLS_CC) == FAILURE) {
		return;
	}
	ZEPHIR_INIT_NVAR(_3);
	object_init_ex(_3, zephir_get_internal_ce(SS("phalcon\\loader") TSRMLS_CC));
	if (zephir_has_constructor(_3 TSRMLS_CC)) {
		ZEPHIR_CALL_METHOD(NULL, _3, "__construct", NULL, 0);
		zephir_check_call_status();
	}
	ZEPHIR_CPY_WRT(_5, _3);
	if (zephir_set_symbol(loader, _5 TSRMLS_CC) == FAILURE) {
		return;
	}
	_6 = zephir_fetch_nproperty_this(this_ptr, SL("config"), PH_NOISY_CC);
	ZEPHIR_CPY_WRT(_7, _6);
	if (zephir_set_symbol(config, _7 TSRMLS_CC) == FAILURE) {
		return;
	}
	_6 = zephir_fetch_nproperty_this(this_ptr, SL("application"), PH_NOISY_CC);
	ZEPHIR_CPY_WRT(_8, _6);
	if (zephir_set_symbol(application, _8 TSRMLS_CC) == FAILURE) {
		return;
	}
	ZEPHIR_CPY_WRT(_9, this_ptr);
	if (zephir_set_symbol(bootstrap, _9 TSRMLS_CC) == FAILURE) {
		return;
	}
	_6 = zephir_fetch_nproperty_this(this_ptr, SL("di"), PH_NOISY_CC);
	ZEPHIR_CPY_WRT(_10, _6);
	if (zephir_set_symbol(di, _10 TSRMLS_CC) == FAILURE) {
		return;
	}
	ZEPHIR_OBSERVE_OR_NULLIFY_PPZV(&_11);
	if (zephir_require_zval_ret(&_11, filePath TSRMLS_CC) == FAILURE) {
		RETURN_MM_NULL();
	}
	RETURN_CCTOR(_11);

}

zend_object_value zephir_init_properties_PhalconPlus_Bootstrap(zend_class_entry *class_type TSRMLS_DC) {

		zval *_0, *_1$$3;

		ZEPHIR_MM_GROW();
	
	{
		zval zthis       = zval_used_for_init;
		zval *this_ptr   = &zthis;
		zend_object* obj = ecalloc(1, sizeof(zend_object));
		zend_object_value retval;

		zend_object_std_init(obj, class_type TSRMLS_CC);
		object_properties_init(obj, class_type);
		retval.handle   = zend_objects_store_put(obj, (zend_objects_store_dtor_t)zend_objects_destroy_object, zephir_free_object_storage, NULL TSRMLS_CC);
		retval.handlers = zend_get_std_object_handlers();

		Z_TYPE(zthis)   = IS_OBJECT;
		Z_OBJVAL(zthis) = retval;

		_0 = zephir_fetch_nproperty_this(this_ptr, SL("activeModules"), PH_NOISY_CC);
		if (Z_TYPE_P(_0) == IS_NULL) {
			ZEPHIR_INIT_VAR(_1$$3);
			array_init(_1$$3);
			zephir_update_property_this(getThis(), SL("activeModules"), _1$$3 TSRMLS_CC);
		}
		ZEPHIR_MM_RESTORE();
		return retval;
	}

}

