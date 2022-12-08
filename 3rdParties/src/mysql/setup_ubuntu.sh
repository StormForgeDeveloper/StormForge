
if [ ! -f "libmysqlcppconn9_8.0.27-1ubuntu21.04_amd64.deb" ]; then

	rm libmysqlcppconn*.deb
	wget https://dev.mysql.com/get/Downloads/Connector-C++/libmysqlcppconn9_8.0.31-1ubuntu22.04_amd64.deb
	wget https://dev.mysql.com/get/Downloads/MySQL-8.0/mysql-community-client-plugins_8.0.31-1ubuntu22.04_amd64.deb
	wget https://dev.mysql.com/get/Downloads/Connector-C++/libmysqlcppconn8-2_8.0.31-1ubuntu22.04_amd64.deb
	wget https://dev.mysql.com/get/Downloads/Connector-C++/libmysqlcppconn-dev_8.0.31-1ubuntu22.04_amd64.deb

	sudo apt install ./libmysqlcppconn9_8.0.31-1ubuntu22.04_amd64.deb
	sudo apt install ./mysql-community-client-plugins_8.0.31-1ubuntu22.04_amd64.deb
	sudo apt install ./libmysqlcppconn8-2_8.0.31-1ubuntu22.04_amd64.deb
	sudo apt install ./libmysqlcppconn-dev_8.0.31-1ubuntu22.04_amd64.deb
fi


