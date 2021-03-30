
set TOOL_PATH=..\..\tool\bin


if not exist xz-5.2.5.tar.gz (
	echo downloading Avro
	call %TOOL_PATH%\httpget +url:"https://cfhcable.dl.sourceforge.net/project/lzmautils/xz-5.2.5.tar.gz"
)

7z x xz-5.2.5.tar.gz -so | 7z x -aoa -si -ttar 


rem patch
rem xcopy /s c\* lzma918\lang\c\ /y
