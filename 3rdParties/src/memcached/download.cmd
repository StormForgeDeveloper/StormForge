
bash ./download.sh

set LIBMEMCACHED_VERSION=1.0.18

rem patching...
xcopy /s patch_win\* libmemcached-%LIBMEMCACHED_VERSION%\ /y
