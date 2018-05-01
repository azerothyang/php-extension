/*
  +----------------------------------------------------------------------+
  | PHP Version 7                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2017 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author:                                                              |
  +----------------------------------------------------------------------+
*/

/* $Id$ */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_sample.h"

/* If you declare any globals in php_sample.h uncomment this:
ZEND_DECLARE_MODULE_GLOBALS(sample)
*/

/* True global resources - no need for thread safety here */
static int le_sample;

/* {{{ PHP_INI
 */
/* Remove comments and fill if you need to have entries in php.ini
PHP_INI_BEGIN()
    STD_PHP_INI_ENTRY("sample.global_value",      "42", PHP_INI_ALL, OnUpdateLong, global_value, zend_sample_globals, sample_globals)
    STD_PHP_INI_ENTRY("sample.global_string", "foobar", PHP_INI_ALL, OnUpdateString, global_string, zend_sample_globals, sample_globals)
PHP_INI_END()
*/
/* }}} */

/* Remove the following function when you have successfully modified config.m4
   so that your module can be compiled into PHP, it exists only for testing
   purposes. */

/* Every user-visible function in PHP should document itself in the source */
/* {{{ proto string confirm_sample_compiled(string arg)
   Return a string to confirm that the module is compiled in */
PHP_FUNCTION(confirm_sample_compiled)
{
	char *arg = NULL;
	size_t arg_len, len;
	zend_string *strg;

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "s", &arg, &arg_len) == FAILURE) {
		return;
	}

	strg = strpprintf(0, "Congratulations! You have successfully modified ext/%.78s/config.m4. Module %.78s is now compiled into PHP.", "sample", arg);

	RETURN_STR(strg);
}


// PHP
/* }}} */
/* The previous line is meant for vim and emacs, so it can correctly fold and
   unfold functions in source code. See the corresponding marks just before
   function definition, where the functions purpose is also documented. Please
   follow this convention for the convenience of others editing your code.
*/


/* {{{ php_sample_init_globals
 */
/* Uncomment this function if you have INI entries
static void php_sample_init_globals(zend_sample_globals *sample_globals)
{
	sample_globals->global_value = 0;
	sample_globals->global_string = NULL;
}
*/
/* }}} */

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(sample)
{
	/* If you have INI entries, uncomment these lines
	REGISTER_INI_ENTRIES();
	*/
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(sample)
{
	/* uncomment this line if you have INI entries
	UNREGISTER_INI_ENTRIES();
	*/
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request start */
/* {{{ PHP_RINIT_FUNCTION
 */
PHP_RINIT_FUNCTION(sample)
{
#if defined(COMPILE_DL_SAMPLE) && defined(ZTS)
	ZEND_TSRMLS_CACHE_UPDATE();
#endif
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request end */
/* {{{ PHP_RSHUTDOWN_FUNCTION
 */
PHP_RSHUTDOWN_FUNCTION(sample)
{
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(sample)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "sample support", "enabled");
	php_info_print_table_end();

	/* Remove comments if you have entries in php.ini
	DISPLAY_INI_ENTRIES();
	*/
}
/* }}} */

/* {{{ sample_functions[]
 *
 * Every user visible function must have an entry in sample_functions[].
 */
PHP_FUNCTION(sample_hello_world)
{
	// char *arg = NULL;
	// size_t arg_len, len;
	// zend_string *strg;

	long n, i;
	register long sum = 0;
	if (zend_parse_parameters(ZEND_NUM_ARGS(), "l", &n) == FAILURE) {
		return;
	}
	for (i = 0; i < n; ++i){
		/* code */
		sum += i;
	}
	RETVAL_LONG(sum);
	return;
}

PHP_FUNCTION(sample_array_range)
{
	int i;
	/*return an array from 0-999*/
	array_init(return_value);
	for (i = 0; i < 1000; ++i)
	{
		/* code */
		add_next_index_long(return_value, i);
	}
	return;
}

PHP_FUNCTION(sample_get_long)
{
	long max, i;
	register long sum = 0;
	if (zend_parse_parameters(ZEND_NUM_ARGS(), "l", &max) == FAILURE) {
		RETURN_NULL();
	}
	php_printf("get right long data: %ld\n", max);
	for (i = 0; i <= max; ++i){
		/* code */
		sum += i;
	}
	RETURN_LONG(sum);
}



// 传值
int callback(zval *val) {
	/* Duplicate the zval so that
* the original's contents are not destroyed */
  zval tmpcopy = *val;
  // ZVAL_COPY(&tmpcopy, val);

  convert_to_string(&tmpcopy);

  php_printf("The value is: [ ");
  PHPWRITE(Z_STRVAL(tmpcopy), Z_STRLEN(tmpcopy));
  php_printf(" ]\n");

  zval_dtor(&tmpcopy); // 主动释放临时 zval，不然会内存泄漏
  return ZEND_HASH_APPLY_KEEP;
}

int callback_args(zval *val, int num_args, va_list args, zend_hash_key *hash_key) {
  zval zvaltmp = *val;
  convert_to_string(&zvaltmp);
 
  // 打印键值对结果
  php_printf("The key is : [ ");
  if (hash_key->key) {
  	/* String Key / Associative */
    PHPWRITE(ZSTR_VAL(hash_key->key), ZSTR_LEN(hash_key->key));
  } else {
  	/* Numeric Key */
    php_printf("%ld", hash_key->h);
  }
  php_printf(" ], the value is: [ ");
  PHPWRITE(Z_STRVAL(zvaltmp), Z_STRLEN(zvaltmp));
  php_printf(" ]\n");
 
  zval_dtor(&zvaltmp); // 主动释放临时 zval，不然会内存泄漏
  return ZEND_HASH_APPLY_KEEP;
}

PHP_FUNCTION(sample_foreach_array)
{
	zval *arr, *val;
	zend_string *arKey, *key;
	zend_ulong numKey;
	arKey = zend_string_init("y", strlen("y"), 0);
	if (zend_parse_parameters(ZEND_NUM_ARGS(), "a", &arr) == FAILURE) {
		RETURN_NULL();
	}
	// 获取hash数组值
	// if(val = zend_hash_find(Z_ARRVAL_P(arr), arKey)){
	// 	zend_string *zstr = zval_get_string(val);
	// 	php_printf("y=>%s\n", ZSTR_VAL(zstr));
	// }
	// else{
	// 	php_printf("This is my string: %s\n", ZSTR_VAL(arKey));	
	// }


	// 遍历值
	php_printf("value list is :\n");
	// zend_hash_apply(Z_ARRVAL_P(arr), callback);


	ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(arr), numKey, key, zval* val){
		php_printf("numKey:%ld, key:%s, val:%s\n", numKey, ZSTR_VAL(key), Z_STRVAL_P(val));

	}ZEND_HASH_FOREACH_END();
	// php_printf("key => value list is :\n");
	// 遍历键和值
  	// zend_hash_apply_with_arguments(Z_ARRVAL_P(arr), callback_args, 0);
	return;
}







const zend_function_entry sample_functions[] = {
	PHP_FE(confirm_sample_compiled,	NULL)		/* For testing, remove later. */
	PHP_FE(sample_hello_world,	NULL)		/*sample_hello_world*/
	PHP_FE(sample_array_range,	NULL)		/*sample_array_range*/
	PHP_FE(sample_get_long,	NULL)		/*sample_get_long*/
	PHP_FE(sample_foreach_array,	NULL)		/*sample_get_long*/
	PHP_FE_END	/* Must be the last line in sample_functions[] */
};
/* }}} */

/* {{{ sample_module_entry
 */
zend_module_entry sample_module_entry = {
	STANDARD_MODULE_HEADER,
	PHP_SAMPLE_EXTNAME,
	sample_functions,
	PHP_MINIT(sample),
	PHP_MSHUTDOWN(sample),
	PHP_RINIT(sample),		/* Replace with NULL if there's nothing to do at request start */
	PHP_RSHUTDOWN(sample),	/* Replace with NULL if there's nothing to do at request end */
	PHP_MINFO(sample),
	PHP_SAMPLE_VERSION,
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_SAMPLE
#ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE()
#endif
ZEND_GET_MODULE(sample)
#endif

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
