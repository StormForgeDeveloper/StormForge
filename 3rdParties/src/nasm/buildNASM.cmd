
%~d0
cd %~dp0


IF '%VCCMAKEGENERATOR%'=='' (
  call ..\..\FindVC.cmd
)


set NASMSRC=nasm-2.15.02

cmd.exe /c "cd %NASMSRC% & nmake /f Mkfiles/msvc.mak"


xcopy %NASMSRC%\*.exe ..\..\Windows\Common\bin\ /d /Y
xcopy %NASMSRC%\*.lib ..\..\Windows\Common\lib\ /d /Y

