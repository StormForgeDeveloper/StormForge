
%~d0
cd %~dp0


set SF_PATH=%~dp0
set SF_SDK=%SF_PATH%..
set TOOL_PATH=%SF_PATH%\3rdParties\tool\bin

call 3rdParties\FindVC.cmd
call SetupSDKPath.cmd


cmd /c "cd %SF_PATH%\3rdParties\tool & buildTool.cmd"

set ATF_PATH=%SF_PATH%\..\ATF


if not exist %ATF_PATH% (
	echo %ATF_PATH%
	git clone https://github.com/blue3k/ATFClone.git %ATF_PATH%
)

rem move to %SF_SDK%
cd %SF_SDK%



set ZIP7_INSTALL_FILE_WIN=7z1900-x64.exe
if not exist %ZIP7_INSTALL_FILE_WIN% (
	echo downloading 7zip
    call %TOOL_PATH%\httpget +url:https://www.7-zip.org/a/%ZIP7_INSTALL_FILE_WIN%
	%ZIP7_INSTALL_FILE_WIN%
)

if not exist %VK_SDK_PATH% (
	echo VK_SDK_PATH not found. Need Vulkan SDK installed
)


set FBX_SDK_INSTALL_FILE_WIN=fbx20201_fbxsdk_vs2017_win.exe
if not exist %FBX_SDK_INSTALL_FILE_WIN% (
	echo downloading FBXSDK
    call %TOOL_PATH%\httpget +url:https://www.autodesk.com/content/dam/autodesk/www/adn/fbx/2020-1/fbx20201_fbxsdk_vs2017_win.exe
	%FBX_SDK_INSTALL_FILE_WIN% /D=%FBX_SDK_PATH%
)


cd %~dp0

set MYSQL_ZIP=mysql-connector-c++-8.0.32-winx64.zip
if not exist %MYSQL_ZIP% (
	echo downloading mysql-connector
	call %TOOL_PATH%\httpget +url:https://cdn.mysql.com//Downloads/Connector-C++/mysql-connector-c++-8.0.32-winx64.zip
	mkdir 3rdParties\Windows
	7z x mysql-connector-c++-8.0.32-winx64.zip -o.\3rdParties\Windows
	rem NOTE: Register mysql dll path to your path
)


if not exist "Test/UnitTest/UnitTest1/Test/LogServer/LocalData/serveraddress.txt" (
	mkdir Test/UnitTest/UnitTest1/Test/LogServer/LocalData
	copy Test/UnitTest/UnitTest1/Test/LogServer/serveraddress_sample.txt Test/UnitTest/UnitTest1/Test/LogServer/LocalData/serveraddress.txt
)


powershell .\download_dependencies.ps1


@echo ==============================================================
@echo Register FBX_SDK_PATH to environment path
@echo Register test host names 
@echo Kafka: SFTestKafka.com
@echo host file location
@echo   - Windows 10 – “C:\Windows\System32\drivers\etc\hosts”
@echo   - Linux – “/etc/hosts”
@echo   - Mac OS X – “/private/etc/hosts”
@echo ==============================================================

pause
