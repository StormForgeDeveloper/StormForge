

https://zookeeper.apache.org/releases.html#download

wget http://apache.mirrors.hoobly.com/zookeeper/zookeeper-3.6.2/apache-zookeeper-3.6.2.tar.gz
tar -xvf apache-zookeeper-3.6.2.tar.gz
cd apache-zookeeper-3.6.2

sudo apt install openjdk-11-jdk-headless 
export JAVA_HOME=$(realpath /usr/bin/javadoc | sed 's@bin/javadoc$@@')

use maven install
