#include "php_vaeql.h"
#include "vaeql.h"
#include "zend_API.h"
#define EMPTY_STRING ""

int vaeql_php_post_deactivate(void)
{
    return SUCCESS;
}

ZEND_DECLARE_MODULE_GLOBALS(vaeql)

    char *resolveFunction(char *function, char **args) {
        zval func, retval, *params[2];
        char *result, **arg;
        ZVAL_STRING(params[0], function,0);
        ZVAL_STRING(&func, "_vaeql_function",0);
        array_init(params[1]);
        for (arg = args; *arg; arg++) {
            add_next_index_string(params[1], (const char *)*arg,1);
        } 
        if (call_user_function(EG(function_table), NULL, &func, &retval, 2, params,0) == FAILURE) {
            return strdup(EMPTY_STRING);
        }
        char *str = Z_STRVAL_P(&retval);
        result = strdup(str);
        // zend_string_release(str);
        if(str)
            free(str);
        return result;
    }

RangeFunctionRange resolveRangeFunction(char *function, char **args) {
    zval **func, retval, *params[2], *retdata;
    HashTable *ret_hash;
    char **arg, foundLow = 0, foundHigh = 0;
    RangeFunctionRange r;
    r.low = r.high = 0;

    ZVAL_STRING(params[0], function,0);
    ZVAL_STRING(*func, "_vaeql_range_function",0);
    array_init(params[1]);
    for (arg = args; *arg; arg++) {
        add_next_index_string(params[1], *arg,1);
    } 
    if (call_user_function(EG(function_table), NULL, *func, &retval, 2, params,0) == FAILURE) {
        return r;
    }
    r.low = 0;
    r.high = 99999999999999;
    // from here
    zval **one_text;

    HashPosition ptr;
    HashTable *arr = Z_ARRVAL_P(&retval);
    for (zend_hash_internal_pointer_reset_ex(arr, &ptr); zend_hash_get_current_data_ex(arr, (void **) &one_text, &ptr) == SUCCESS; zend_hash_move_forward_ex(arr, &ptr)) {
        //  result = (char *) bw_replace_text(trie, (byte *) Z_STRVAL_PP(one_text), replacement[0], wordbound);
        if (!foundLow) {
            r.low = Z_LVAL_PP(one_text);
            foundLow = 1;
        } else if (!foundHigh) {
            r.high = Z_LVAL_PP(one_text);
            foundHigh = 1;
        }
        // add_next_index_string(return_value, result, 1);

    }
    // ending here
    /*
       ZEND_HASH_FOREACH_VAL(Z_ARRVAL(retval), retdata) {
       if (!foundLow) {
       r.low = zval_get_long(retdata);
       foundLow = 1;
       } else if (!foundHigh) {
       r.high = zval_get_long(retdata);
       foundHigh = 1;
       }
       } ZEND_HASH_FOREACH_END();
     */
    return r;
}

char *resolvePath(char *path) {
    zval func, retval, param, *params[1];
    char *result;

    ZVAL_STRING(params[0], path,0);
    ZVAL_STRING(&func, "_vaeql_path",0);
    if (call_user_function(EG(function_table), NULL, &func, &retval, 1, params,0) == FAILURE) {
        return strdup(EMPTY_STRING);
    }
    char *str = Z_STRVAL_P(&retval);
    result = strdup(str);
    if(str)
        free(str);
    //  zend_string_release(str);
    return result;       
}

char *resolveVariable(char *variable) {
    zval func, retval, param, *params[1];
    char *result;

    ZVAL_STRING(params[0], variable,0);
    ZVAL_STRING(&func, "_vaeql_variable",0);
    if (call_user_function(EG(function_table), NULL, &func, &retval, 1, params,0) == FAILURE) {
        return strdup(EMPTY_STRING);
    }
    char *str = Z_STRVAL_P(&retval);
    result = strdup(str);
    if(str)
        free(str);
    ///  zend_string_release(str);
    return result;
}

static zend_function_entry vaeql_functions[] = {
        PHP_FE(_vaeql_query_internal, NULL)
        {NULL, NULL, NULL, 0, 0}
};

zend_module_entry vaeql_module_entry = {
    STANDARD_MODULE_HEADER,
    PHP_VAEQL_WORLD_EXTNAME,
    vaeql_functions,

    PHP_MINIT(vaeql),
    PHP_MSHUTDOWN(vaeql),

    PHP_RINIT(vaeql),
    PHP_RSHUTDOWN(vaeql),

    PHP_MINFO(vaeql),
    PHP_VAEQL_WORLD_VERSION,

    PHP_MODULE_GLOBALS(vaeql),
    PHP_GINIT(vaeql),
    PHP_GSHUTDOWN(vaeql),

    vaeql_php_post_deactivate,

    STANDARD_MODULE_PROPERTIES_EX
};

static PHP_INI_MH(vaeql_greeting_mh)
{
    return SUCCESS;
}

PHP_INI_BEGIN()
PHP_INI_END()

static void php_vaeql_init_globals(zend_vaeql_globals *vaeql_globals)
{
}

/* zm_globals_ctor_vaeql */
PHP_GINIT_FUNCTION(vaeql)
{
}

/* zm_globals_dtor_vaeql */
PHP_GSHUTDOWN_FUNCTION(vaeql)
{
}

/* zm_activate_vaeql */
PHP_RINIT_FUNCTION(vaeql)
{
    return SUCCESS;
}

/* zm_deactivate_vaeql */
PHP_RSHUTDOWN_FUNCTION(vaeql)
{
    return SUCCESS;
}

/* zm_startup_vaeql */
PHP_MINIT_FUNCTION(vaeql)
{
    ZEND_INIT_MODULE_GLOBALS(vaeql, php_vaeql_init_globals, NULL);
    REGISTER_INI_ENTRIES();
    return SUCCESS;
}

/* zm_shutdown_vaeql */
PHP_MSHUTDOWN_FUNCTION(vaeql)
{
    UNREGISTER_INI_ENTRIES();
    return SUCCESS;
}

/* zif_vaeql_world */

/* zif__vaeql_query_internal */
PHP_FUNCTION(_vaeql_query_internal)
{
    //RETURN_DOUBLE(3.1415926535);
    zval * args;
    char *query;
  //  char *s;
zval *tmp=NULL;;
    /* VaeQueryLanguage */
    VaeQueryLanguageParser_start_return langAST;
    pVaeQueryLanguageLexer lxr;
    pVaeQueryLanguageParser psr;
    pVaeQueryLanguageTreeParser treePsr;
    pANTLR3_INPUT_STREAM istream;
    pANTLR3_COMMON_TOKEN_STREAM    tstream;
    pANTLR3_COMMON_TREE_NODE_STREAM      nodes;
    VaeQueryLanguageTreeParser_start_return result;

    /* Pull in arg from PHP */
    if(ZEND_NUM_ARGS()!=1)
    {
        WRONG_PARAM_COUNT;
    }
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z",  &args) == FAILURE) {

WRONG_PARAM_COUNT;

    }
    ALLOC_ZVAL(tmp);

    ZVAL_COPY_VALUE(tmp, args);
    zval_copy_ctor(tmp);
    convert_to_string(tmp);
//    if (ZEND_NUM_ARGS() != 1  || zend_get_parameters_array_ex(1, args) != SUCCESS) {

//        WRONG_PARAM_COUNT("wrong");
  //  }
    // char *str = Z_STRVAL_P(args);
   //   char * str=args;
  //  query = 
    //query =(char*)s; 
    query =Z_STRVAL_P(tmp); 
    if(Z_TYPE_P(tmp) == IS_STRING)
    {
    }

    /* Lex and Parse */
    if (istream = antlr3NewAsciiStringInPlaceStream((uint8_t *)query, (ANTLR3_UINT64)strlen(query), NULL)) {
        if (lxr    = VaeQueryLanguageLexerNew(istream)) {
            if (tstream = antlr3CommonTokenStreamSourceNew(ANTLR3_SIZE_HINT, TOKENSOURCE(lxr))) {
                if (psr      = VaeQueryLanguageParserNew(tstream)) {
                    langAST = psr->start(psr);
                    if (psr->pParser->rec->state->errorCount == 0) {
                        if (nodes       = antlr3CommonTreeNodeStreamNewTree(langAST.tree, ANTLR3_SIZE_HINT)) {
                            if (treePsr       = VaeQueryLanguageTreeParserNew(nodes)) {
                                result = treePsr->start(treePsr);
                                if (result.result) {
                                    array_init(return_value);
                                    add_next_index_bool(return_value, result.isPath);
                                    add_next_index_string(return_value, (const char *)result.result->chars,0); 
                                } else {
                                    ZVAL_LONG(return_value, -2);
                                }
                                treePsr->free(treePsr);
                            } else {
                                ZVAL_LONG(return_value, -101);
                            } 
                            nodes->free(nodes);
                        } else {
                            ZVAL_LONG(return_value, -102);
                        }
                    } else {
                        ZVAL_LONG(return_value, -1);
                    }
                    psr->free(psr);
                } else {
                    ZVAL_LONG(return_value, -103);
                }
                tstream->free(tstream);
            } else {
                ZVAL_LONG(return_value, -104);
            }
            lxr->free(lxr);
        } else {
            ZVAL_LONG(return_value, -105);
        }
        istream->close(istream);
    } else {
        ZVAL_LONG(return_value, -106);
    }
    if (tmp==NULL)
    {
    }
    else
    {
    zval_dtor(tmp);
   tmp=NULL; 
    }
}


/* zm_info_vaeql */
PHP_MINFO_FUNCTION(vaeql)
{
}

#ifdef __cplusplus
extern "C" {
#endif

#if defined(HHVM)
#define COMPILE_DL_VAEQL 1
#endif

#ifdef COMPILE_DL_VAEQL
    ZEND_DLEXPORT zend_module_entry *get_module (void);
    ZEND_GET_MODULE (vaeql)
#endif

#ifdef __cplusplus
}
#endif
