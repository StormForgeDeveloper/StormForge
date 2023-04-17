
@echo on

call ..\build\FindVC.cmd


rem build helper tools
cmd /c "cd tool & buildTool.cmd"


set PATH=%~dp0\Windows\Common\bin;%PATH%


rem Build main part
cmd /c "call WinGenMain.cmd nopause"
cmd /c "call WinBuildMain.cmd nopause"


if not "%1" == "nopause" pause

