

set SF_PATH=%~dp0
set SF_SDK=%SF_PATH%..

if "%FBX_SDK_PATH%" == "" set FBX_SDK_PATH=%SF_SDK%\FBXSDK

if "%VULKAN_SDK_PATH%" == "" set VULKAN_SDK_PATH=%SF_SDK%\VulkanSDK
