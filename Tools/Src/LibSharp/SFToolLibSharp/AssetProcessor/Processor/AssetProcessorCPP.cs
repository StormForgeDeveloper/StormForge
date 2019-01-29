////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2018 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Asset processor cpp
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
using System.Diagnostics;
using SF.Tool;

namespace SF.Asset
{
    
    // Asset processor CPP
    public abstract class AssetProcessorCPP : AssetProcessorExternal
    {
        protected static readonly Type[] stm_InputAssetTypes =
        {
            typeof(AssetC),
            typeof(AssetCPP)
        };

        protected static readonly Type[] stm_OutputAssetTypes =
        {
            typeof(AssetObj)
        };

    }

    public class AssetProcessorCPPVC : AssetProcessorCPP
    {
        static string Command = "cl.exe";
        static Dictionary<string, string> stm_OptionMap;
        // For __BASE_FILE__, http://stackoverflow.com/questions/15509061/msvcs-equivalent-of-gccs-base-file
        static string DefaultCompileOptions = "/c /showIncludes /Zi /Gm /fp:precise /D_VARIADIC_MAX=10 /D_MBCS /errorReport:prompt /WX- /Zc:forScope /RTC1 /Gd /EHsc /nologo /D_CRT_SECURE_NO_DEPRECATE /DWIN32 /D_WINDOWS __BASE_FILE__=\"%(Filename)%(Extension)\" /I./";

        string GetCommandPath()
        {
            //var vsPath = AppConfig.GetValue<string>("VS_PATH");
            //ToolDebug.Assert(!string.IsNullOrEmpty(vsPath));
            //return Path.Combine(vsPath, @"VC\BIN\x86_amd64", Command);
            return Command;
        }

        static AssetProcessorCPPVC()
        {
            stm_OptionMap = new Dictionary<string, string>();
            stm_OptionMap.Add("includes", "/I");
            stm_OptionMap.Add("defines", "/D");
            stm_OptionMap.Add("pdb", "/Fd");
            stm_OptionMap.Add("warning_level", "/W");
            stm_OptionMap.Add("usePCH", "/Yu");
            stm_OptionMap.Add("createPCH", "/Yc");
            stm_OptionMap.Add("pch", "/Fp");
        }

        public static Type[] InputAssetTypes { get { return stm_InputAssetTypes; } }
        public static Type[] OutputAssetTypes { get { return stm_OutputAssetTypes; } }

        // Initialize application library
        public AssetProcessorCPPVC()
        {
            AvailablePlatforms.Add(BuildPlatform.WIN64);
        }

        public override void Start(AssetBuildContext context)
        {
            StringBuilder commandParameter = new StringBuilder();
            commandParameter.AppendFormat("{0}", DefaultCompileOptions);
            commandParameter.AppendFormat(" {0}{1} {0}_{1}", "/D", context.Target.TargetConfiguration.ToString().ToUpper());
            commandParameter.AppendFormat(" {0}{1} {0}_{1}", "/D", context.Target.TargetPlatform.ToString().ToUpper());

            if (context.Target.TargetConfiguration == BuildConfiguration.Debug)
            {
                commandParameter.Append(" /GS /Gs /Ob1 /Od /MDd");
            }
            else
            {
                commandParameter.Append(" /Ox /MD");
            }

            AddParameterSetting(context, commandParameter, stm_OptionMap);

            var outputPath = PathTool.NormalizePathAndCreate(context.CurrentOutput.SourceFilePath);
            commandParameter.AppendFormat(" /Fo:{0}", outputPath);

            foreach (var input in context.CurrentInputs)
            {
                commandParameter.AppendFormat(" {0}", input.SourceFilePath);
            }

            StartInfo.FileName = GetCommandPath();
            StartInfo.Arguments = commandParameter.ToString();
            base.Start(context);
        }

        protected override void OnExited(object sender, EventArgs e)
        {
            base.OnExited(sender, e);

            var includes = ParseIncludes(Output.ToString());
            foreach(var include in includes)
            {
                var dependencyPath = PathTool.NormalizePathToProjectBase(include);
                var dependency = Context.AssetDB.AddOrGetAsset(dependencyPath);
                Context.CurrentOutput.AddBuildDependency(dependency);
            }
        }

        //public ResultCode UpdateDependency(AssetBuildContext context, Asset assetFrom, Asset assetTo)
        //{
        //    if (assetFrom == null || assetTo == null)
        //        return new ResultCode(ResultCode.E_INVALIDARG);

        //    StringBuilder commandParameter = new StringBuilder();
        //    commandParameter.AppendFormat("{0}", DefaultCompileOptions);
        //    commandParameter.AppendFormat(" {0}{1} {0}_{1}", "/D", context.Target.TargetConfiguration.ToString().ToUpper());
        //    commandParameter.AppendFormat(" {0}{1} {0}_{1}", "/D", context.Target.TargetPlatform.ToString().ToUpper());

        //    if (context.Target.TargetConfiguration == BuildConfiguration.Debug)
        //    {
        //        commandParameter.Append(" /Od /MDd");
        //    }
        //    else
        //    {
        //        commandParameter.Append(" /Ox /MD");
        //    }

        //    commandParameter.AppendFormat(" /showIncludes /w /c {0}", assetFrom.SourcePath);

        //    AddParameterSetting(commandParameter, stm_OptionMap);

        //    var startInfo = new ProcessStartInfo();

        //    startInfo.CreateNoWindow = false;
        //    startInfo.UseShellExecute = false;
        //    startInfo.WindowStyle = ProcessWindowStyle.Hidden;
        //    startInfo.StandardErrorEncoding = Encoding.UTF8;
        //    startInfo.StandardOutputEncoding = Encoding.UTF8;
        //    startInfo.RedirectStandardError = true;
        //    startInfo.RedirectStandardInput = true;
        //    startInfo.RedirectStandardOutput = true;
        //    startInfo.FileName = GetCommandPath();
        //    startInfo.Arguments = commandParameter.ToString();

        //    var runningProcess = new Process();
        //    runningProcess.StartInfo = startInfo;
        //    runningProcess.Start();

        //    var errors = runningProcess.StandardError.ReadToEnd();
        //    var outputs = runningProcess.StandardOutput.ReadToEnd();

        //    if(runningProcess.ExitCode != 0)
        //    {
        //        ToolDebug.Error("UpdateDependency is failed by {0}", runningProcess.ExitCode);
        //        return new ResultCode(ResultCode.E_FAIL);
        //    }

        //    // TODO: parse
        //    var includes = ParseIncludes(outputs);

        //    return new ResultCode(ResultCode.S_OK);
        //}
        
        static string[] ParseIncludes(string inputString)
        {
            var stringLines = inputString.Split('\r');
            var resultStrings = new List<string>();
            const string startStringPattern = "Note: including file:";
            foreach(var line in stringLines)
            {
                var includeString = line.Trim();
                if (includeString.StartsWith(startStringPattern))
                {
                    includeString = includeString.Substring(startStringPattern.Length + 1);
                    includeString = includeString.TrimStart();
                    resultStrings.Add(includeString);
                }
            }

            return resultStrings.ToArray();
        }
    }


    public class AssetProcessorCPPGCC : AssetProcessorCPP
    {
        static string Command = "g++";
        static Dictionary<string, string> stm_OptionMap = new Dictionary<string, string>();
        static string DefaultCompileOptions = "-c -g -std=c++14 -pthread -static-libgcc -static-libstdc++ -Wall";

        static AssetProcessorCPPGCC()
        {
            stm_OptionMap.Add("includes", "-I");
            stm_OptionMap.Add("defines", "-D");
            stm_OptionMap.Add("warning_level", "-W");
        }
        public static Type[] InputAssetTypes { get { return stm_InputAssetTypes; } }
        public static Type[] OutputAssetTypes { get { return stm_OutputAssetTypes; } }

        // Initialize application library
        public AssetProcessorCPPGCC()
        {
            AvailablePlatforms.Add(BuildPlatform.LINUX);
            AvailablePlatforms.Add(BuildPlatform.ANDROID);
            AvailablePlatforms.Add(BuildPlatform.IOS);

        }

        public override void Start(AssetBuildContext context)
        {
            StringBuilder commandParameter = new StringBuilder();
            commandParameter.AppendFormat("{0}", DefaultCompileOptions);
            commandParameter.AppendFormat(" {0}{1} {0}_{1}", "-D", context.Target.TargetConfiguration.ToString().ToUpper());
            commandParameter.AppendFormat(" {0}{1} {0}_{1}", "-D", context.Target.TargetPlatform.ToString().ToUpper());

            if (context.Target.TargetConfiguration == BuildConfiguration.Debug)
            {
                commandParameter.Append(" -O0");
            }
            else
            {
                commandParameter.Append(" -Ofast");
            }

            AddParameterSetting(context, commandParameter, stm_OptionMap);

            commandParameter.AppendFormat(" -o:{0}", context.CurrentOutput.ResourcePath);

            foreach (var input in context.CurrentInputs)
            {
                commandParameter.AppendFormat(" {0}", input.ResourcePath);
            }

            StartInfo.FileName = Command;
            StartInfo.Arguments = commandParameter.ToString();
            base.Start(context);
        }

        protected override void OnExited(object sender, EventArgs e)
        {
            base.OnExited(sender, e);

            var includes = ParseIncludes(Output.ToString());

        }

        static string[] ParseIncludes(string inputString)
        {
            // TODO: make dependency check for gcc
            var stringLines = inputString.Split('\r');
            var resultStrings = new List<string>();
            const string startStringPattern = "Note: including file:";
            foreach (var line in stringLines)
            {
                var includeString = line.Trim();
                if (includeString.StartsWith(startStringPattern))
                {
                    includeString = includeString.Substring(startStringPattern.Length + 1);
                    includeString = includeString.TrimStart();
                    resultStrings.Add(includeString);
                }
            }

            return resultStrings.ToArray();
        }
    }
}
