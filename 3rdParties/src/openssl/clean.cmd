
%~d0
cd %~dp0


set BUILD_DIR=%~dp0..\..\..\Intermediate\%1\openssl\%2
set OUTPUT_DIR=%~dp0..\..\..\Bin\%1\%2



rd /s /q %BUILD_DIR%
rd /s /q %OUTPUT_DIR%


