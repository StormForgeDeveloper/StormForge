
%~d0
cd %~dp0


IF '%VCCMAKEGENERATOR%'=='' (
  call ..\..\FindVC.cmd
)


set BUILD_DIR=%~dp0\buildWindows\build
set OUTPUT_DIR=%~dp0\buildWIndows


@if not "%1" == "Win" goto endWin
@if "%2" == "x64" set CONFIG_TARGET=VC-WIN64A
@if "%2" == "x86" set CONFIG_TARGET=VC-WIN32
:endWin

rem TODO: add handling for android: android android-armeabi android-mips android-x86 android64 android64-aarch64
@if not "%1" == "Android" goto endAndroid
@if "%2" == "x64" set CONFIG_TARGET=android64
@if "%2" == "x86" set CONFIG_TARGET=android-x86
@if "%2" == "arm" set CONFIG_TARGET=android-armeabi
@if "%2" == "arm64" set CONFIG_TARGET=a Winndroid64
:endAndroid

@set PATH=%PATH%;"%~dp0..\nasm\bin";

@echo CONFIG_TARGET=%CONFIG_TARGET%
@echo BUILD_DIR=%BUILD_DIR%
@if "%3" == "build"  @echo goto "build"
if "%3" == "build" goto build

:config

	@if not exist %BUILD_DIR% mkdir %BUILD_DIR%
	cd %BUILD_DIR% && call perl %~dp0openssl-1.1.1g\Configure %CONFIG_TARGET% enable-egd enable-ssl3 enable-ssl3-method no-threads --openssldir=%OUTPUT_DIR%\openssl --prefix=%OUTPUT_DIR%\openssl -DNOCRYPT
	goto exit

:build

	cd %BUILD_DIR%

	nmake
	
	nmake install_sw

	cd ..

:exit



