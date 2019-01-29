using System;
using System.IO;
using System.Reflection;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using SF;
using SF.Tool;
using SF.Tool.Asset;
using SF.Tool.Asset.Build;

namespace SF.Tool.Builder
{

    /// <summary>
    /// Load assembly for update
    /// </summary>
    class BuildActionLoadAssembly : BuildScriptAction
    {
        public override string ScriptCommand { get { return "loadassembly"; } }

        public override void Run(BuildActionContext context)
        {
            var newAssembly = Assembly.LoadFile(Arguments[1]);
            if (newAssembly == null) return;

            BuildScriptActionManager.RegisterClasses(newAssembly);

            BuilderAssetDB.RegisterClasses(newAssembly);
        }
    }

    /// <summary>
    /// Start process group
    /// </summary>
    class BuildScriptActionGroupStart : BuildScriptAction
    {
        public override string ScriptCommand { get { return "group"; } }

        public override void Run(BuildActionContext context)
        {
            //context.CurrentAssets
        }
    }

    /// <summary>
    /// End process group
    /// </summary>
    class BuildScriptActionGroupEnd : BuildScriptAction
    {
        public override string ScriptCommand { get { return "}"; } }

        public override void Run(BuildActionContext context)
        {
            //AppConfig.RestoreConfig();
        }
    }

    /// <summary>
    /// Add processor
    /// </summary>
    class BuildScriptActionPorcessImporter : BuildScriptAction
    {
        public override string ScriptCommand { get { return "import"; } }

        public override void Run(BuildActionContext context)
        {
            if (Arguments == null || Arguments.Length == 0)
            {
                ToolDebug.Warning("No item specified for process");
                return;
            }

            if (Arguments.Length < 2)
            {
                ToolDebug.Warning("No resource specified {0}", Arguments[1]);
                return;
            }

            string processName = Arguments[1];
            string resourcePath = Arguments[2];

            var process = BuilderAssetDB.GetItem(processName);
            if (process == null)
            {
                ToolDebug.Warning("No process found {0}", processName);
                return;
            }

            //if (process.Object == null)
            //{
            //    ToolDebug.Warning("Invalid process item found {0}", processName);
            //    return;
            //}

            var resourceAssetItem = BuilderAssetDB.AddOrGetAsset(resourcePath);
            if(resourceAssetItem == null)
            {
                ToolDebug.Warning("No resource found {0}", resourcePath);
                return;
            }

            //AssetProcessor processor = BuilderAssetDB.Instance.GetProcessorFor(context.Target, resourceAssetItem, destType);
            //if (processor == null)
            //{
            //    ToolDebug.Error("No processor found {0}", resourcePath);
            //    return;
            //}

            // TODO: copy rest argument
            // Arguments need to be pair of name:value such as setting set
            //for (int iConfig = 3; iConfig < Arguments.Length; iConfig++)
            //{
            //    childImporter.Parameters.Add(Arguments[iConfig]);
            //}
        }
    }

    /// <summary>
    /// Add processor
    /// </summary>
    class BuildScriptActionPorcessExporter : BuildScriptAction
    {
        public override string ScriptCommand { get { return "export"; } }

        public override void Run(BuildActionContext context)
        {
            if (Arguments == null || Arguments.Length == 0)
            {
                ToolDebug.Warning("No item specified for process");
                return;
            }

            if (Arguments.Length < 2)
            {
                ToolDebug.Warning("No resource specified {0}", Arguments[1]);
                return;
            }

            string processName = Arguments[1];
            string resourcePath = Arguments[2];

            var process = BuilderAssetDB.GetItem(processName);
            if (process == null)
            {
                ToolDebug.Warning("No process found {0}", processName);
                return;
            }

            //if (process.Object == null)
            //{
            //    ToolDebug.Warning("Invalid process item found {0}", processName);
            //    return;
            //}

            var resourceAssetItem = BuilderAssetDB.AddOrGetAsset(resourcePath);
            if (resourceAssetItem == null)
            {
                ToolDebug.Warning("No resource found {0}", resourcePath);
                return;
            }

            if (context.CurrentBuildPipeline == null)
            {
                ToolDebug.Warning("Invalid buildpipeline item found {0}", processName);
                return;
            }

            //var buildPipeline = resourceAssetItem.BuildPipeline[context.CurrentTarget];
            //var orgImporterObject = process.Object as BuildProcessor;
            //var childImporter = orgImporterObject.Clone();

            //buildPipeline.ProcessorList.Add(childImporter);

            //// copy rest argument
            //for (int iConfig = 3; iConfig < Arguments.Length; iConfig++)
            //{
            //    childImporter.Parameters.Add(Arguments[iConfig]);
            //}
        }
    }

    /// <summary>
    /// Add processor
    /// </summary>
    class BuildScriptActionPorcessFilter : BuildScriptAction
    {
        public override string ScriptCommand { get { return "filter"; } }

        public override void Run(BuildActionContext context)
        {
            if (Arguments == null || Arguments.Length == 0)
            {
                ToolDebug.Warning("No item specified for process");
                return;
            }

            if (Arguments.Length < 2)
            {
                ToolDebug.Warning("No resource specified {0}", Arguments[1]);
                return;
            }

            string processName = Arguments[1];

            var process = BuilderAssetDB.GetItem(processName);
            if (process == null)
            {
                ToolDebug.Warning("No process found {0}", processName);
                return;
            }

            if (process == null)
            {
                ToolDebug.Warning("Invalid process item found {0}", processName);
                return;
            }

            if (context.CurrentBuildPipeline == null)
            {
                ToolDebug.Warning("Invalid buildpipeline item found {0}", processName);
                return;
            }

            //var buildPipeline = context.CurrentBuildPipeline[context.CurrentTarget];
            //var orgImporterObject = process.Object as BuildProcessor;
            //var childImporter = orgImporterObject.Clone();

            //buildPipeline.ProcessorList.Add(childImporter);

            //// copy rest argument
            //for (int iConfig = 3; iConfig < Arguments.Length; iConfig++)
            //{
            //    childImporter.Parameters.Add(Arguments[iConfig]);
            //}
        }
    }

}
