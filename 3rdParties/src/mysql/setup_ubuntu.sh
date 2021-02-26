
if [ ! -f "libmysqlcppconn-dev_8.0.21-1ubuntu18.04_amd64.deb" ]; then

	rm libmysqlcppconn*.deb
	wget https://dev.mysql.com/get/Downloads/Connector-C++/libmysqlcppconn7_8.0.21-1ubuntu18.04_amd64.deb
	wget https://dev.mysql.com/get/Downloads/Connector-C++/libmysqlcppconn8-2_8.0.21-1ubuntu18.04_amd64.deb
	wget https://dev.mysql.com/get/Downloads/Connector-C++/libmysqlcppconn-dev_8.0.21-1ubuntu18.04_amd64.deb

	sudo apt install ./libmysqlcppconn7_8.0.21-1ubuntu18.04_amd64.deb
	sudo apt install ./libmysqlcppconn8-2_8.0.21-1ubuntu18.04_amd64.deb
	sudo apt install ./libmysqlcppconn-dev_8.0.21-1ubuntu18.04_amd64.deb
fi
