
set TOOL_PATH=..\..\tool\bin


set RELEASE_ZIP=mysql-connector-c++-8.0.27-winx64.zip
set DEBUG_ZIP=mysql-connector-c++-8.0.27-winx64-debug.zip
if not exist %RELEASE_ZIP% (
	echo downloading mysql
	call %TOOL_PATH%\httpget +url:https://dev.mysql.com/get/Downloads/Connector-C++/%RELEASE_ZIP%
	call %TOOL_PATH%\httpget +url:https://dev.mysql.com/get/Downloads/Connector-C++/%DEBUG_ZIP%
)

7z x %DEBUG_ZIP% -y
7z x %RELEASE_ZIP% -y


robocopy mysql-connector-c++-8.0.27-winx64\lib64\vs14\ mysql-connector-c++-8.0.27-winx64\lib64\vs14\RelWithDebInfo /purge *.lib

