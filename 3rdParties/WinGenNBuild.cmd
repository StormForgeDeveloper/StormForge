
@echo on

call ..\build\FindVC.cmd


rem build helper tools
cmd /c "cd tool & buildTool.cmd"


set PATH=%~dp0\Windows\Common\bin;%PATH%


rem Build main part
rem cmd /c "call WinGenMain.cmd nopause"
rem cmd /c "call WinBuildMain.cmd nopause"

cmd /c "cd src\flatbuffer & call download.cmd nopause"


if not "%1" == "nopause" pause

