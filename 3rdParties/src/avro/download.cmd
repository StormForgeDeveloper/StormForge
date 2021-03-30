
set TOOL_PATH=..\..\tool\bin

set AVRO_SRC=avro-src-1.10.2
if not exist %AVRO_SRC%.tar.gz (
	echo downloading Avro
	call %TOOL_PATH%\httpget +url:https://downloads.apache.org/avro/avro-1.10.2/%AVRO_SRC%.tar.gz
)

7z x %AVRO_SRC%.tar.gz -so | 7z x -aoa -si -ttar

rem patch
xcopy /s patch\* avro-src-1.10.2\ /y
