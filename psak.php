<?php
$br = (php_sapi_name() == "cli")? "":"<br>";

if(!extension_loaded('psak')) {
	dl('psak.' . PHP_SHLIB_SUFFIX);
}
$module = 'psak';
$functions = get_extension_funcs($module);
echo "Functions available in the psak extension:$br\n";
foreach($functions as $func) {
    echo $func."$br\n";
}
echo "$br\n";

$a = rc4("asa1232134141sa", "qwer@#$%^&*()t");

var_dump($a);

?>
