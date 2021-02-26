
rm mysql-connector-c++*.tar.gz
wget https://dev.mysql.com/get/Downloads/Connector-C++/mysql-connector-c++-8.0.21-linux-glibc2.12-x86-64bit.tar.gz

mkdir linuxLib
tar -xvf mysql-connector-c++-8.0.21-linux-glibc2.12-x86-64bit.tar.gz -C linuxLib --strip 1

