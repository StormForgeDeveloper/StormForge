
set TOOL_PATH=..\..\tool\bin

set SRC_PATH=curl
if not exist %SRC_PATH% (
	echo downloading Curl
	git clone https://github.com/curl/curl.git
)


rem patch
rem xcopy /s patch\* %SRC_PATH%\ /y
