////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2018 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Asset processor
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
using SF.Tool;
using SF.Asset.Build;
using System.Diagnostics;

namespace SF.Asset
{
    
    // Build Pipeline informations
    public abstract class AssetProcessor
    {
        public string Name
        {
            get; protected set;
        }

        // currently building context
        public AssetBuildContext Context { get; protected set; }

        public ToolSetting ParameterSetting { get; private set; }

        public ResultCode ProcessResult { get; protected set; }

        public Type[] GetInputAssetTypes()
        {
            var inputAssetTypesProperty = GetType().GetProperty("InputAssetTypes");
            ToolDebug.Assert(inputAssetTypesProperty != null);
            ToolDebug.Assert(inputAssetTypesProperty.PropertyType == typeof(Type[]));
            return (Type[])inputAssetTypesProperty.GetValue(null);
        }

        public Type[] GetOutputAssetTypes()
        {
            var outputAssetTypesProperty = GetType().GetProperty("OutputAssetTypes");
            ToolDebug.Assert(outputAssetTypesProperty != null);
            ToolDebug.Assert(outputAssetTypesProperty.PropertyType == typeof(Type[]));
            return (Type[])outputAssetTypesProperty.GetValue(null);

        }

        /// <summary>
        /// Available platforms. empty means available for all platform
        /// </summary>
        public List<BuildPlatform> AvailablePlatforms { get; private set; }

        // Initialize application library
        public AssetProcessor()
        {
            Name = GetType().Name;
            ParameterSetting = new ToolSetting();
            AvailablePlatforms = new List<BuildPlatform>();
            ProcessResult = new ResultCode(ResultCode.SUCCESS_FALSE);
        }

        public abstract void Start(AssetBuildContext context);
        public abstract void Stop();
        public abstract bool IsFinished();

    }


    // Build Pipeline informations
    public abstract class AssetProcessorExternal : AssetProcessor
    {
       public ProcessStartInfo StartInfo { get; private set; }
        Process m_RunningProcess;

        public StringBuilder ErrorOutput { get; private set; }
        public StringBuilder Output { get; private set; }

        public AssetProcessorExternal()
        {
            ErrorOutput = new StringBuilder();
            Output = new StringBuilder();

            StartInfo = new ProcessStartInfo();

            StartInfo.CreateNoWindow = false;
            StartInfo.UseShellExecute = false;
            StartInfo.WindowStyle = ProcessWindowStyle.Hidden;
            StartInfo.StandardErrorEncoding = Encoding.UTF8;
            StartInfo.StandardOutputEncoding = Encoding.UTF8;
            StartInfo.RedirectStandardError = true;
            StartInfo.RedirectStandardInput = true;
            StartInfo.RedirectStandardOutput = true;
        }

        protected void AddParameterSetting(AssetBuildContext context, StringBuilder commandBuilder, Dictionary<string, string> optionMap)
        {
            foreach (var setting in context.Parameters)
            {
                AddParameterSetting(commandBuilder, optionMap, setting);
            }

            foreach (var setting in ParameterSetting)
            {
                AddParameterSetting(commandBuilder, optionMap, setting);
            }
        }

        void AddParameterSetting(StringBuilder commandBuilder, Dictionary<string, string> optionMap, SettingValue setting)
        {
            string mappingValue;
            if (!optionMap.TryGetValue(setting.Key, out mappingValue)) return;
            if (string.IsNullOrEmpty(mappingValue)) return;

            var settingString = setting as SettingValueString;
            if (settingString != null)
            {
                commandBuilder.AppendFormat(" {0}{1}", mappingValue, settingString.Value);
                return;
            }

            var settingSet = setting as SettingValueSet;
            if (settingSet != null)
            {
                foreach (var settingSetString in settingSet)
                {
                    commandBuilder.AppendFormat(" {0}{1}", mappingValue, settingSetString.Key);
                }
                return;
            }
        }
        protected void ExitHandler(object sender, EventArgs e)
        {
            OnExited(sender, e);
        }

        protected virtual void OnExited(object sender, EventArgs e)
        {
        }

        void OnOutput(object sender, DataReceivedEventArgs e)
        {
            if (!String.IsNullOrEmpty(e.Data))
            {
                ToolDebug.Log("{0}: ", StartInfo.FileName, e.Data);
            }
            Output.AppendFormat("{0}\r",e.Data);
        }

        void OnErrorOutput(object sender, DataReceivedEventArgs e)
        {
            if (!String.IsNullOrEmpty(e.Data))
            {
                ToolDebug.Log("{0}: ", StartInfo.FileName, e.Data);
            }
            ErrorOutput.AppendFormat("{0}\r", e.Data);
        }

        public override void Start(AssetBuildContext context)
        {
            Context = context;
            try
            {
                Output.Clear();
                ErrorOutput.Clear();

                m_RunningProcess = new Process();
                m_RunningProcess.StartInfo = StartInfo;

                // Enable async events
                m_RunningProcess.EnableRaisingEvents = true;
                m_RunningProcess.Exited += new EventHandler(ExitHandler);
                m_RunningProcess.OutputDataReceived += new DataReceivedEventHandler(OnOutput);
                m_RunningProcess.ErrorDataReceived += new DataReceivedEventHandler(OnErrorOutput);

                m_RunningProcess.Start();
                m_RunningProcess.BeginOutputReadLine();
                m_RunningProcess.BeginErrorReadLine();
            }
            catch (Exception exp)
            {
                ToolDebug.Error("Failed to run {0}, {1}", StartInfo.FileName, exp.Message);
                m_RunningProcess = null;
                // Log error.
            }
        }
        public override void Stop()
        {
            if(m_RunningProcess != null)
            {
                if(!m_RunningProcess.HasExited)
                {
                    m_RunningProcess.Kill();
                    ProcessResult = new ResultCode(ResultCode.FAIL);
                }
                else
                {
                    if (m_RunningProcess.ExitCode != 0)
                        ProcessResult = new ResultCode(ResultCode.FAIL);
                    else
                        ProcessResult = new ResultCode(ResultCode.SUCCESS);
                }

                m_RunningProcess.Dispose();
                m_RunningProcess = null;
            }
        }
        public override bool IsFinished()
        {
            return m_RunningProcess == null || m_RunningProcess.HasExited;
        }


    }
}
