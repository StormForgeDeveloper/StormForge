


set PATH=C:\DevEnv\Android\cmake\3.10.2.4988404\bin;%PATH%
set CMAKE_SYSTEM_NAME=Android

if not exist Intermediate mkdir Intermediate
if not exist Intermediate\%CMAKE_SYSTEM_NAME% mkdir Intermediate\%CMAKE_SYSTEM_NAME%

cd Intermediate\%CMAKE_SYSTEM_NAME%



cmake --build .


pause
