#!/bin/sh

DIRNAME=`dirname $0`
REALPATH=`which realpath`
if [ ! -z "${REALPATH}" ]; then
  DIRNAME=`realpath ${DIRNAME}`
fi

if [ "$HPHP_HOME" != "" ]; then
    HHVM="${HPHP_HOME}/hphp/hhvm/hhvm"
else
    HHVM=hhvm
fi

$HHVM \
  -vDynamicExtensions.0=${DIRNAME}/vaeql.so\
  ${DIRNAME}/test.php\
  -dhhvm.enable_zend_compat=true 
