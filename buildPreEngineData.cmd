
PATH=%PATH%;C:\cygwin64\bin;"C:\Program Files (x86)\Windows Kits\10\bin\x64";

cd %~dp0\Engine\Data

bash buildData.sh build

pause
