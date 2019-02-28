
set SF_PATH=%~dp0


git clone https://github.com/blue3k/ATFClone.git %SF_PATH%..\ATF

rem mklink /J %SF_PATH%ATF %SF_PATH%..\ATF

git clone https://github.com/blue3k/StormForge3rdParties.git %SF_PATH%..\StormForge3rdParties

mklink /J %SF_PATH%3rdParties %SF_PATH%..\StormForge3rdParties\3rdParties

pause
