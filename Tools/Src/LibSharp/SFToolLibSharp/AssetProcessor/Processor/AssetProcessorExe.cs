////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2018 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Asset processor exe
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
    public abstract class AssetProcessorExe : AssetProcessorExternal
    {
        protected static readonly Type[] stm_InputAssetTypes =
        {
            typeof(AssetObj)
        };

        protected static readonly Type[] stm_OutputAssetTypes =
        {
            typeof(AssetExe)
        };

    }

    public class AssetProcessorExeWin : AssetProcessorExe
    {
        static string Command = "link.exe";
        static Dictionary<string, string> stm_OptionMap;
        static string DefaultLinkerOptions = "/INCREMENTAL /MANIFEST /NXCOMPAT /DYNAMICBASE /TLBID:1 /SUBSYSTEM:WINDOWS /arch:AVX2";
        static string DefaultLibraries = "kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib Mswsock.lib";

        static AssetProcessorExeWin()
        {
            stm_OptionMap = new Dictionary<string, string>();
            stm_OptionMap.Add("libpath", "/LIBPATH:");
            stm_OptionMap.Add("lib", "");
            stm_OptionMap.Add("machine", "/MACHINE:");
            stm_OptionMap.Add("out", "/OUT:");
            stm_OptionMap.Add("pdb", "/PDB:");
            stm_OptionMap.Add("assembly", "/ASSEMBLYMODULE:");
        }
        public static Type[] InputAssetTypes { get { return stm_InputAssetTypes; } }
        public static Type[] OutputAssetTypes { get { return stm_OutputAssetTypes; } }

        // Initialize application library
        public AssetProcessorExeWin()
        {
            AvailablePlatforms.Add(BuildPlatform.WIN64);
        }

        public override void Start(AssetBuildContext context)
        {
            StringBuilder commandParameter = new StringBuilder();
            commandParameter.AppendFormat(" {0}", DefaultLinkerOptions);
            commandParameter.AppendFormat(" {0}", DefaultLibraries);

            if (context.Target.TargetConfiguration == BuildConfiguration.Debug)
            {
                commandParameter.Append(" /DEBUG /LTCG:INCREMENTAL");
            }
            else
            {
                //commandParameter.Append(" /Ox /MD");
            }

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


    public class AssetProcessorExeLinux : AssetProcessorCPP
    {
        static string Command = "g++";
        static Dictionary<string, string> stm_OptionMap = new Dictionary<string, string>();
        static string DefaultLinkerOptions = "-g -std=c++14 -pthread -static-libgcc  -static-libstdc++";
        static string DefaultLibraries = "c kqueue z xml2 ssl crypto jsoncpp curl mysqlclient";
        public static Type[] InputAssetTypes { get { return stm_InputAssetTypes; } }
        public static Type[] OutputAssetTypes { get { return stm_OutputAssetTypes; } }

        // Initialize application library
        public AssetProcessorExeLinux()
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
            commandParameter.AppendFormat(" {0} {1}", DefaultLinkerOptions, DefaultLibraries);

            AddParameterSetting(context, commandParameter, stm_OptionMap);

            StartInfo.FileName = Command;
            StartInfo.Arguments = commandParameter.ToString();
            base.Start(context);
        }
    }
}
