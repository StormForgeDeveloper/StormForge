////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2018 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Asset processor lib
//
////////////////////////////////////////////////////////////////////////////////

using System;
using System.IO;
using System.Collections.Generic;
using System.Collections.Concurrent;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using SF;
using SF.Asset.Build;
using SF.Tool;

namespace SF.Asset
{
    
    // Asset processor CPP
    public abstract class AssetProcessorLib : AssetProcessorExternal
    {
        protected static readonly Type[] stm_InputAssetTypes =
        {
            typeof(AssetObj)
        };

        protected static readonly Type[] stm_OutputAssetTypes =
        {
            typeof(AssetLib)
        };
    }

    public class AssetProcessorLibVC : AssetProcessorLib
    {
        static string Command = "lib.exe";
        static Dictionary<string, string> stm_OptionMap = new Dictionary<string, string>();
        static string DefaultLibOptions = "/LTCG";

        static AssetProcessorLibVC()
        {
            stm_OptionMap.Add("lib", "");
            stm_OptionMap.Add("machine", "/MACHINE:");
            stm_OptionMap.Add("assembly", "/ASSEMBLYMODULE:");
        }
        public static Type[] InputAssetTypes { get { return stm_InputAssetTypes; } }
        public static Type[] OutputAssetTypes { get { return stm_OutputAssetTypes; } }

        // Initialize application library
        public AssetProcessorLibVC()
        {
            AvailablePlatforms.Add(BuildPlatform.WIN64);
        }

        public override void Start(AssetBuildContext context)
        {
            StringBuilder commandParameter = new StringBuilder();
            commandParameter.AppendFormat(" {0}", DefaultLibOptions);

            AddParameterSetting(context, commandParameter, stm_OptionMap);

            var outputPath = PathTool.NormalizePathAndCreate(context.CurrentOutput.SourceFilePath);
            commandParameter.AppendFormat(" /OUT:{0}", outputPath);

            foreach (var input in context.CurrentInputs)
            {
                commandParameter.AppendFormat(" {0}", input.SourceFilePath);
            }

            StartInfo.FileName = Command;
            StartInfo.Arguments = commandParameter.ToString();
            base.Start(context);
        }
    }


    public class AssetProcessorLibGCC : AssetProcessorLib
    {
        static string Command = "ar";
        static Dictionary<string, string> stm_OptionMap = new Dictionary<string, string>();
        static string DefaultLibOptions = "cr ";
        public static Type[] InputAssetTypes { get { return stm_InputAssetTypes; } }
        public static Type[] OutputAssetTypes { get { return stm_OutputAssetTypes; } }

        // Initialize application library
        public AssetProcessorLibGCC()
        {
            AvailablePlatforms.Add(BuildPlatform.LINUX);
            AvailablePlatforms.Add(BuildPlatform.ANDROID);
            AvailablePlatforms.Add(BuildPlatform.IOS);

            stm_OptionMap.Add("libpath", "-L=");
            stm_OptionMap.Add("lib", "-l");
        }

        public override void Start(AssetBuildContext context)
        {
            StringBuilder commandParameter = new StringBuilder();
            commandParameter.AppendFormat(" {0}", DefaultLibOptions);

            AddParameterSetting(context, commandParameter, stm_OptionMap);

            StartInfo.FileName = Command;
            StartInfo.Arguments = commandParameter.ToString();
            base.Start(context);

        }
    }
}
