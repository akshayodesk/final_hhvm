set(HPHP_HOME "/usr/bin/hphpize")

include_directories(
  ./
  /usr/include/hphp/runtime/ext_zend_compat/php-src
  /usr/include/hphp/runtime/ext_zend_compat/php-src/Zend/
  /usr/include/hphp/runtime/ext_zend_compat/php-src/TSRM/
  /usr/include/hphp/runtime/ext_zend_compat/php-src/main/
)

#include_directories(
#  ./
#  /usr/include/php/20151012/
#  /usr/include/php/20151012/Zend/
#  /usr/include/php/20151012/TSRM/
#  /usr/include/php/20151012/main/
#)

HHVM_EXTENSION(vaeql    php_vaeql.cpp VaeQueryLanguageLexer.cpp  VaeQueryLanguageParser.cpp  VaeQueryLanguageTreeParser.cpp vaeql.cpp )
target_link_libraries(vaeql antlr3c)
HHVM_SYSTEMLIB(vaeql ext_vaeql.php)
