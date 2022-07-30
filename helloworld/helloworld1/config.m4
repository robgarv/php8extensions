PHP_ARG_ENABLE(php_helloworld, Whether to enable the HelloWorldPHP extension, [ --enable-helloworld-php Enable HelloWorldPHP])

if test "$PHP_HELLOWORLD" != "no"; then
    PHP_NEW_EXTENSION(php_helloworld, php_helloworld.c, $ext_shared)
fi

