
cd %~d0
cd %~dp0

@echo off


set SF_PATH=%~dp0
set SF_3RDPARTY=%SF_PATH%3rdParties 
set SF_SDK=%SF_PATH%..
set FBX_SDK_INSTALL_FILE_WIN=fbx20201_fbxsdk_vs2017_win.exe
set VULKAN_SDK_WIN=VulkanSDK-1.2.148.1-Installer.exe
set TOOL_PATH=%SF_PATH%\3rdParties\tool\bin

call 3rdParties\FindVC.cmd


set ATF_PATH=%SF_PATH%\..\ATF


if not exist %ATF_PATH% (
	echo %ATF_PATH%
	git clone https://github.com/blue3k/ATFClone.git %ATF_PATH%
)


cd %SF_3RDPARTY%\tool

msbuild -m BuildTool.sln /property:Configuration=Release /p:Platform="Any CPU"

cd %SF_SDK%

if not exist %FBX_SDK_INSTALL_FILE_WIN% (
	echo downloading FBXSDK
    call %TOOL_PATH%\httpget +url:https://www.autodesk.com/content/dam/autodesk/www/adn/fbx/2020-1/%FBX_SDK_INSTALL_FILE_WIN%
	%FBX_SDK_INSTALL_FILE_WIN% /D=%SF_SDK%\FBXSDK
)


if not exist %VULKAN_SDK_WIN% (
	echo downloading VulkanSDK
	call %TOOL_PATH%\httpget +url:https://sdk.lunarg.com/sdk/download/1.2.148.1/windows/%VULKAN_SDK_WIN%
	%VULKAN_SDK_WIN% /D=%SF_SDK%\VulkanSDK
)


set PERL_INSTALL=strawberry-perl-5.32.0.1-64bit.msi
if not exist %PERL_INSTALL% (
	echo downloading Perl
	call %TOOL_PATH%\httpget +url:http://strawberryperl.com/download/5.32.0.1/%PERL_INSTALL%
	%PERL_INSTALL%
	PATH=%PATH%;C:\Strawberry\c\bin
)


cd %SF_PATH%

set NASM_DIR=3rdParties\src\nasm
cmd /c "cd %NASM_DIR% & buildNASM.cmd"

set OPENSSL_DIR=3rdParties\src\openssl
cmd /c "cd %OPENSSL_DIR% & config1.1_Winx64.cmd"

set MYSQL_DIR=3rdParties\src\mysql
cmd /c "cd %MYSQL_DIR% & WinGen.cmd"


set OPENSSL_DIR=3rdParties\src\openssl
cmd /c "cd %OPENSSL_DIR% & build1.1_Winx64.cmd"


set MYSQL_DIR=3rdParties\src\mysql
cmd /c "cd %MYSQL_DIR% & WinBuild.cmd"


pause
