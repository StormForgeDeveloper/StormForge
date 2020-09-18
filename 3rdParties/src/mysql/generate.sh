mkdir buildLinux
cd buildLinux

cmake ../mysql-connector-c++-8.0.20-src/ -G "Unix Makefiles"  -DWITH_SSL=system

