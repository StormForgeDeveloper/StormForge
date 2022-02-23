
set TOOL_PATH=..\..\tool\bin


echo downloading libuv
git clone https://github.com/libuv/libuv.git


rem patch
rem xcopy /s patch\* %ARCHIVE_SRC%\ /y
