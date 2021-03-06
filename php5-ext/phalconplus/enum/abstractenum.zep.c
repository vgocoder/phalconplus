
#ifdef HAVE_CONFIG_H
#include "../../ext_config.h"
#endif

#include <php.h>
#include "../../php_ext.h"
#include "../../ext.h"

#include <Zend/zend_operators.h>
#include <Zend/zend_exceptions.h>
#include <Zend/zend_interfaces.h>

#include "kernel/main.h"
#include "kernel/memory.h"
#include "kernel/fcall.h"
#include "kernel/object.h"
#include "kernel/operators.h"
#include "kernel/exception.h"
#include "ext/spl/spl_exceptions.h"
#include "kernel/array.h"
#include "kernel/concat.h"
#include "kernel/string.h"


ZEPHIR_INIT_CLASS(PhalconPlus_Enum_AbstractEnum) {

	ZEPHIR_REGISTER_CLASS(PhalconPlus\\Enum, AbstractEnum, phalconplus, enum_abstractenum, phalconplus_enum_abstractenum_method_entry, ZEND_ACC_EXPLICIT_ABSTRACT_CLASS);

	zend_declare_property_null(phalconplus_enum_abstractenum_ce, SL("val"), ZEND_ACC_PROTECTED TSRMLS_CC);

	zend_declare_class_constant_string(phalconplus_enum_abstractenum_ce, SL("DEFAULT_VALUE"), "__PhalconPlus_AbstractEnum_DefaultValue__" TSRMLS_CC);

	zend_class_implements(phalconplus_enum_abstractenum_ce TSRMLS_CC, 1, zephir_get_internal_ce(SS("jsonserializable") TSRMLS_CC));
	return SUCCESS;

}

PHP_METHOD(PhalconPlus_Enum_AbstractEnum, __construct) {

	zephir_fcall_cache_entry *_9 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *val = NULL, *reflection = NULL, *defaultVal = NULL, *_0, *_1 = NULL, *_2, *_3$$3, *_4$$3 = NULL, *_5$$4, *_6$$4, _7$$4, *_8$$4 = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 1, &val);

	if (!val) {
		ZEPHIR_INIT_VAR(val);
		ZVAL_STRING(val, "__PhalconPlus_AbstractEnum_DefaultValue__", 1);
	}


	ZEPHIR_INIT_VAR(reflection);
	object_init_ex(reflection, zephir_get_internal_ce(SS("reflectionclass") TSRMLS_CC));
	ZEPHIR_INIT_VAR(_0);
	zephir_get_called_class(_0 TSRMLS_CC);
	ZEPHIR_CALL_METHOD(NULL, reflection, "__construct", NULL, 4, _0);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(_2);
	ZVAL_STRING(_2, "__default", ZEPHIR_TEMP_PARAM_COPY);
	ZEPHIR_CALL_METHOD(&_1, reflection, "hasconstant", NULL, 11, _2);
	zephir_check_temp_parameter(_2);
	zephir_check_call_status();
	if (zephir_is_true(_1)) {
		ZEPHIR_INIT_VAR(_3$$3);
		ZVAL_STRING(_3$$3, "__default", ZEPHIR_TEMP_PARAM_COPY);
		ZEPHIR_CALL_METHOD(&defaultVal, reflection, "getconstant", NULL, 12, _3$$3);
		zephir_check_temp_parameter(_3$$3);
		zephir_check_call_status();
		ZEPHIR_CALL_STATIC(&_4$$3, "isvalid", NULL, 0, defaultVal);
		zephir_check_call_status();
		if (!(zephir_is_true(_4$$3))) {
			ZEPHIR_INIT_VAR(_5$$4);
			object_init_ex(_5$$4, spl_ce_OutOfRangeException);
			ZEPHIR_INIT_VAR(_6$$4);
			zephir_get_class(_6$$4, this_ptr, 0 TSRMLS_CC);
			ZEPHIR_SINIT_VAR(_7$$4);
			ZVAL_STRING(&_7$$4, "Invalid __default enumeration %s for Enum %s", 0);
			ZEPHIR_CALL_FUNCTION(&_8$$4, "sprintf", NULL, 13, &_7$$4, defaultVal, _6$$4);
			zephir_check_call_status();
			ZEPHIR_CALL_METHOD(NULL, _5$$4, "__construct", NULL, 14, _8$$4);
			zephir_check_call_status();
			zephir_throw_exception_debug(_5$$4, "phalconplus/Enum/AbstractEnum.zep", 17 TSRMLS_CC);
			ZEPHIR_MM_RESTORE();
			return;
		}
	}
	if (ZEPHIR_IS_STRING(val, "__PhalconPlus_AbstractEnum_DefaultValue__")) {
		ZEPHIR_CALL_METHOD(NULL, this_ptr, "setvalue", &_9, 0, defaultVal);
		zephir_check_call_status();
	} else {
		ZEPHIR_CALL_METHOD(NULL, this_ptr, "setvalue", &_9, 0, val);
		zephir_check_call_status();
	}
	ZEPHIR_MM_RESTORE();

}

PHP_METHOD(PhalconPlus_Enum_AbstractEnum, setValue) {

	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *val, *_0 = NULL, *_1$$3, *_2$$3, _3$$3, *_4$$3 = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &val);



	ZEPHIR_CALL_STATIC(&_0, "isvalid", NULL, 0, val);
	zephir_check_call_status();
	if (!(zephir_is_true(_0))) {
		ZEPHIR_INIT_VAR(_1$$3);
		object_init_ex(_1$$3, spl_ce_InvalidArgumentException);
		ZEPHIR_INIT_VAR(_2$$3);
		zephir_get_class(_2$$3, this_ptr, 0 TSRMLS_CC);
		ZEPHIR_SINIT_VAR(_3$$3);
		ZVAL_STRING(&_3$$3, "Invalid enumeration %s for Enum %s", 0);
		ZEPHIR_CALL_FUNCTION(&_4$$3, "sprintf", NULL, 13, &_3$$3, val, _2$$3);
		zephir_check_call_status();
		ZEPHIR_CALL_METHOD(NULL, _1$$3, "__construct", NULL, 15, _4$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(_1$$3, "phalconplus/Enum/AbstractEnum.zep", 31 TSRMLS_CC);
		ZEPHIR_MM_RESTORE();
		return;
	}
	zephir_update_property_this(getThis(), SL("val"), val TSRMLS_CC);
	ZEPHIR_MM_RESTORE();

}

PHP_METHOD(PhalconPlus_Enum_AbstractEnum, getValue) {

	

	RETURN_MEMBER(getThis(), "val");

}

PHP_METHOD(PhalconPlus_Enum_AbstractEnum, isValid) {

	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *val, *_0 = NULL, *_1 = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &val);



	ZEPHIR_CALL_STATIC(&_0, "validvalues", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_FUNCTION(&_1, "in_array", NULL, 16, val, _0, ZEPHIR_GLOBAL(global_true));
	zephir_check_call_status();
	if (!(zephir_is_true(_1))) {
		RETURN_MM_BOOL(0);
	}
	RETURN_MM_BOOL(1);

}

PHP_METHOD(PhalconPlus_Enum_AbstractEnum, validValues) {

	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *assoc_param = NULL, *reflection = NULL, *consts = NULL, *_0, *countValues = NULL, *duplicated$$3 = NULL, *_1$$3 = NULL, *_2$$3, *_3$$3, *_4$$3, *_5$$3, *_6$$3;
	zend_bool assoc;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 1, &assoc_param);

	if (!assoc_param) {
		assoc = 0;
	} else {
		assoc = zephir_get_boolval(assoc_param);
	}


	ZEPHIR_INIT_VAR(reflection);
	object_init_ex(reflection, zephir_get_internal_ce(SS("reflectionclass") TSRMLS_CC));
	ZEPHIR_INIT_VAR(_0);
	zephir_get_called_class(_0 TSRMLS_CC);
	ZEPHIR_CALL_METHOD(NULL, reflection, "__construct", NULL, 4, _0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&consts, reflection, "getconstants", NULL, 17);
	zephir_check_call_status();
	zephir_array_unset_string(&consts, SS("__default"), PH_SEPARATE);
	ZEPHIR_CALL_FUNCTION(&countValues, "array_count_values", NULL, 18, consts);
	zephir_check_call_status();
	if (zephir_fast_count_int(consts TSRMLS_CC) != zephir_fast_count_int(countValues TSRMLS_CC)) {
		ZEPHIR_INIT_VAR(duplicated$$3);
		array_init(duplicated$$3);
		ZEPHIR_INIT_VAR(_1$$3);
		ZEPHIR_INIT_NVAR(_1$$3);
		zephir_create_closure_ex(_1$$3, NULL, phalconplus_0__closure_ce, SS("__invoke") TSRMLS_CC);
		ZEPHIR_CALL_FUNCTION(&duplicated$$3, "array_filter", NULL, 19, countValues, _1$$3);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(_2$$3);
		object_init_ex(_2$$3, spl_ce_RuntimeException);
		ZEPHIR_INIT_VAR(_3$$3);
		zephir_get_called_class(_3$$3 TSRMLS_CC);
		ZEPHIR_INIT_VAR(_4$$3);
		ZEPHIR_INIT_VAR(_5$$3);
		zephir_array_keys(_5$$3, duplicated$$3 TSRMLS_CC);
		zephir_json_encode(_4$$3, &(_4$$3), _5$$3, 0  TSRMLS_CC);
		ZEPHIR_INIT_VAR(_6$$3);
		ZEPHIR_CONCAT_SVSV(_6$$3, "Duplicated values were found in Enum Class: ", _3$$3, " with values in ", _4$$3);
		ZEPHIR_CALL_METHOD(NULL, _2$$3, "__construct", NULL, 20, _6$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(_2$$3, "phalconplus/Enum/AbstractEnum.zep", 65 TSRMLS_CC);
		ZEPHIR_MM_RESTORE();
		return;
	}
	if (assoc == 1) {
		RETURN_CCTOR(consts);
	} else {
		ZEPHIR_RETURN_CALL_FUNCTION("array_values", NULL, 21, consts);
		zephir_check_call_status();
		RETURN_MM();
	}

}

PHP_METHOD(PhalconPlus_Enum_AbstractEnum, jsonSerialize) {

	zend_long ZEPHIR_LAST_CALL_STATUS;

	ZEPHIR_MM_GROW();

	ZEPHIR_RETURN_CALL_METHOD(this_ptr, "getvalue", NULL, 0);
	zephir_check_call_status();
	RETURN_MM();

}

PHP_METHOD(PhalconPlus_Enum_AbstractEnum, __toString) {

	zval *_1 = NULL;
	zval *_0 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;

	ZEPHIR_MM_GROW();

	ZEPHIR_CALL_METHOD(&_0, this_ptr, "getvalue", NULL, 0);
	zephir_check_call_status();
	zephir_get_strval(_1, _0);
	RETURN_CTOR(_1);

}

