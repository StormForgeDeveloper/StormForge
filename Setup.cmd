
cd %~d0
cd %~dp0

@echo off


set SF_PATH=%~dp0
set SF_SDK=%SF_PATH%..
set TOOL_PATH=%SF_PATH%\3rdParties\tool\bin

call 3rdParties\FindVC.cmd


set ATF_PATH=%SF_PATH%\..\ATF


if not exist %ATF_PATH% (
	echo %ATF_PATH%
	git clone https://github.com/blue3k/ATFClone.git %ATF_PATH%
)

rem move to %SF_SDK%
cd %SF_SDK%

set FBX_SDK_INSTALL_FILE_WIN=fbx20201_fbxsdk_vs2017_win.exe
if not exist %FBX_SDK_INSTALL_FILE_WIN% (
	echo downloading FBXSDK
    call %TOOL_PATH%\httpget +url:https://www.autodesk.com/content/dam/autodesk/www/adn/fbx/2020-1/%FBX_SDK_INSTALL_FILE_WIN%
	%FBX_SDK_INSTALL_FILE_WIN% /D=%SF_SDK%\FBXSDK
)


set VULKAN_SDK_WIN=VulkanSDK-1.2.148.1-Installer.exe
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

cd %~dp0



pause
