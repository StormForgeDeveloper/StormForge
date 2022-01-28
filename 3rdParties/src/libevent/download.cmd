
set TOOL_PATH=..\..\tool\bin


set ARCHIVE_SRC=libevent-2.1.12-stable
if not exist %ARCHIVE_SRC%.tar.gz (
	echo downloading libevent
	call %TOOL_PATH%\httpget +url:https://github.com/libevent/libevent/releases/download/release-2.1.12-stable/%ARCHIVE_SRC%.tar.gz
)

7z x %ARCHIVE_SRC%.tar.gz -so | 7z x -aoa -si -ttar

rem patch
xcopy /s patch\* %ARCHIVE_SRC%\ /y
