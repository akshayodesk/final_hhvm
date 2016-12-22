<?php
var_dump(extension_loaded("vaeql"));
var_dump(extension_loaded("VaeQueryLanguage"));
//var_dump(function_exists("_vaeql_query_internal11"));
var_dump(function_exists("_vaeql_query_internal"));
$stri=_vaeql_query_internal("effrfrfr rfr rf rfrf rr");
$stri=_vaeql_query_internal11("effrfrfr rfr rf rfrf rr");
$stri=_vaeql_query_internal("effrfrfr rfr rf rfrf rr");
$stri=_vaeql_query_internal("effrfrfr rfr rf rfrf rr");
$stri=_vaeql_query_internal("effrfrfr rfr rf rfrf rr");
if(is_array($stri))
    echo "is array";
    echo gettype($stri);
echo $stri;
