/*
  +----------------------------------------------------------------------+
  | PHP Version 5                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2014 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author: Xiahou                                                       |
  +----------------------------------------------------------------------+
*/

/* $Id$ */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_psak.h"

/* If you declare any globals in php_psak.h uncomment this:
ZEND_DECLARE_MODULE_GLOBALS(psak)
*/

/* True global resources - no need for thread safety here */
static int le_psak;


/* {{{ PHP_INI
 */
/* Remove comments and fill if you need to have entries in php.ini
PHP_INI_BEGIN()
    STD_PHP_INI_ENTRY("psak.global_value",      "42", PHP_INI_ALL, OnUpdateLong, global_value, zend_psak_globals, psak_globals)
    STD_PHP_INI_ENTRY("psak.global_string", "foobar", PHP_INI_ALL, OnUpdateString, global_string, zend_psak_globals, psak_globals)
PHP_INI_END()
*/
/* }}} */

/* Remove the following function when you have successfully modified config.m4
   so that your module can be compiled into PHP, it exists only for testing
   purposes. */

/* Every user-visible function in PHP should document itself in the source */
/* {{{ proto string rc4(string arg)
   Return a string to confirm that the module is compiled in */
PHP_FUNCTION(rc4)
{
	char *pwd, *data;
	int pwd_len, data_len;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ss", &pwd, &pwd_len, &data, &data_len) == FAILURE)
		return;

	char strg[data_len];
	int key[256], box[256];
	int i, tmp = 0, j = 0;
	for (i = 0; i < 256; i++)
    {
        key[i] = pwd[i % pwd_len];
        box[i] = i;
    }

    for (i = 0; i < 256; i++)
    {
        j = (j + box[i] + key[i]) % 256;
        tmp = box[i];
        box[i] = box[j];
        box[j] = tmp;
    }
    j = 0;
    int a = 0, k = 0;
    for (i = 0; i < data_len; i++)
    {
        a = (a + 1) % 256;
        j = (j + box[a]) % 256;
        tmp = box[a];
        box[a] = box[j];
        box[j] = tmp;
        k = box[((box[a] + box[j]) % 256)];
        int ord = data[i];
        strg[i] = ord ^ k; 
    }
	RETURN_STRINGL(strg, data_len, 1);
}
/* }}} */
/* The previous line is meant for vim and emacs, so it can correctly fold and 
   unfold functions in source code. See the corresponding marks just before 
   function definition, where the functions purpose is also documented. Please 
   follow this convention for the convenience of others editing your code.
*/


/* {{{ php_psak_init_globals
 */
/* Uncomment this function if you have INI entries
static void php_psak_init_globals(zend_psak_globals *psak_globals)
{
	psak_globals->global_value = 0;
	psak_globals->global_string = NULL;
}
*/
/* }}} */

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(psak)
{
	/* If you have INI entries, uncomment these lines 
	REGISTER_INI_ENTRIES();
	*/
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(psak)
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
PHP_RINIT_FUNCTION(psak)
{
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request end */
/* {{{ PHP_RSHUTDOWN_FUNCTION
 */
PHP_RSHUTDOWN_FUNCTION(psak)
{
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(psak)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "psak support", "enabled");
	php_info_print_table_end();

	/* Remove comments if you have entries in php.ini
	DISPLAY_INI_ENTRIES();
	*/
}
/* }}} */

/* {{{ psak_functions[]
 *
 * Every user visible function must have an entry in psak_functions[].
 */
const zend_function_entry psak_functions[] = {
	PHP_FE(rc4,	NULL)		/* For testing, remove later. */
	PHP_FE_END	/* Must be the last line in psak_functions[] */
};
/* }}} */

/* {{{ psak_module_entry
 */
zend_module_entry psak_module_entry = {
	STANDARD_MODULE_HEADER,
	"psak",
	psak_functions,
	PHP_MINIT(psak),
	PHP_MSHUTDOWN(psak),
	PHP_RINIT(psak),		/* Replace with NULL if there's nothing to do at request start */
	PHP_RSHUTDOWN(psak),	/* Replace with NULL if there's nothing to do at request end */
	PHP_MINFO(psak),
	PHP_PSAK_VERSION,
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_PSAK
ZEND_GET_MODULE(psak)
#endif

