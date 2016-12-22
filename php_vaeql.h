/*
 * From
 *  http://devzone.zend.com/303/
 */
#ifndef PHP_VAEQL_H
#define PHP_VAEQL_H 1

#ifdef ZTS
  #include "TSRM.h"
#endif
#ifdef HAVE_CONFIG_H
  #include "config.h"
#endif


#include "php.h"
#include "php_ini.h"
#include "zend.h"
#include "zend_compile.h"
#include "zend_constants.h"
#include "zend_API.h"
#include "zend_hash.h"
#include "vaeql.h"

#include "VaeQueryLanguageLexer.h"
#include "VaeQueryLanguageParser.h"
#include "VaeQueryLanguageTreeParser.h"

ZEND_BEGIN_MODULE_GLOBALS(vaeql)
ZEND_END_MODULE_GLOBALS(vaeql)

#ifdef ZTS
#define VAEQL_G(v) TSRMG(vaeql_globals_id, zend_vaeql_globals *, v)
#else
#define VAEQL_G(v) (vaeql_globals.v)
#endif

#define PHP_VAEQL_WORLD_VERSION "1.0"
#define PHP_VAEQL_WORLD_EXTNAME "vaeql"

PHP_MINIT_FUNCTION(vaeql);
PHP_MSHUTDOWN_FUNCTION(vaeql);

PHP_RINIT_FUNCTION(vaeql);
PHP_RSHUTDOWN_FUNCTION(vaeql);

PHP_MINFO_FUNCTION(vaeql);

PHP_GINIT_FUNCTION(vaeql);
PHP_GSHUTDOWN_FUNCTION(vaeql);

PHP_FUNCTION(_vaeql_query_internal);


extern zend_module_entry vaeql_module_entry;
#define phpext_vaeql_ptr &vaeql_module_entry

#endif
