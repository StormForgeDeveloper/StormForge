
call ..\FindVC.cmd

dotnet publish BuildTool.sln --configuration Release --property PublishDir=bin /p:Platform="Any CPU"
