StormForge requires c++17 or higher, but unreal's default is c++14.
To change UE behavior you need to set CppStandard to Cpp17. 

<CppStandard>Cpp17</CppStandard>


Best way is change Buildconfiguration.xml
Go to one of below and add CppStandard setting
 - Engine/Saved/UnrealBuildTool/BuildConfiguration.xml
 - %APPDATA%\Roaming\Unreal Engine\UnrealBuildTool\BuildConfiguration.xml
 - *My Documents*/Unreal Engine/UnrealBuildTool/BuildConfiguration.xml
 
 