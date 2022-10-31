
call FindVC.cmd

dotnet publish BuildTool.sln --configuration Release  --output bin /p:Platform="Any CPU"
