using System;
using System.IO;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using SF;
using SF.Tool;
using SF.Tool.Asset.Build;
using SF.Tool.Asset;
using SF.Tool.Builder;

namespace SF.Builder
{
    // Debug param: +TARGET_PLATFORM=WIN64 +BUILD_CONFIGURATION=Debug +OBJ_PATH=..\..\..\Intermediate +out=../../../lib/out.lib +in=libiconv-1.14/libcharset/lib/localcharset.c;libiconv-1.14/lib/relocatable.c;libiconv-1.14/lib/iconv.c +INCLUDES=libiconv-1.14;libiconv-1.14/include;libiconv-1.14/libcharset;libiconv-1.14/libcharset/include; +DEFINES=LIBDIR
    // Debug work: C:\Work\StormForge\3rdParties\src\libiconv\

    class Program
    {
        static List<Asset> SourceList = new List<Asset>();
        static void Main(string[] args)
        {
            var assetDB = BuilderAssetDB.Instance;

            ToolApplication.StartApplication();
            ToolDebug.Log(AppConfig.GetValueString("ModuleDirectory"));

            var context = new AssetBuildContext();
            context.Parameters = AppConfig.Clone();
            context.Target = new BuildTarget(AppConfig.GetValue<BuildPlatform>("TARGET_PLATFORM"), AppConfig.GetValue<BuildConfiguration>("BUILD_CONFIGURATION"));
            context.AssetDB = assetDB;

            var output = AppConfig.GetValue<string>("out");
            if(output == null)
            {
                ToolDebug.Error("Failed to find output");
                return;
            }
            
            var outputAsset = assetDB.AddOrGetAsset(output);
            if (outputAsset == null)
            {
                ToolDebug.Error("Failed to find output asset for {0}", output);
                return;
            }
            context.OutputAsset = outputAsset;


            // Compile argument manually
            // We need order of argument
            var valueSet = AppConfig.GetValueSet("in");
            if(valueSet != null)
            {
                foreach(var value in valueSet)
                {
                    RegisterSourceAsset(context, value.Key);
                }
            }
            else
            {
                var value = AppConfig.GetValue<string>("in");
                if(value != null)
                {
                    RegisterSourceAsset(context, value);
                }
                else
                {
                    ToolDebug.Error("No input files");
                    return;
                }
            }

            //var objPath = AppConfig.GetValue<string>("OBJ_PATH");
            //objPath = PathTool.NormalizePathToProjectBase(objPath);
            //context.Parameters.SetValue("OBJ_PATH", objPath);
            // setup intermediate path for current builds

            foreach (var input in context.SourceAssets)
            {
                CreateAssetBuildPath(context, input);
            }

            Build(context, context.OutputAsset);
        }


        static void RegisterSourceAsset(AssetBuildContext context, string resourcePath)
        {
            if (string.IsNullOrEmpty(resourcePath)) return;
            var assetDB = context.AssetDB;

            var asset = assetDB.AddOrGetAsset(resourcePath);
            if(asset == null)
            {
                ToolDebug.Error("Failed to find asset for {0}", resourcePath);
                return;
            }

            context.SourceAssets.Add(asset);
        }

        static ResultCode CreateAssetBuildPath(AssetBuildContext context, Asset asset)
        {
            if (asset == null) return ResultCode.E_FAIL;
            var assetDB = context.AssetDB;
            var destType = context.OutputAsset.AssetTypeName;
            var intermediatePath = context.Parameters.GetValue<string>("OBJ_PATH");
            var intermediateFilePath =  PathTool.CombinePath(intermediatePath, asset.SourcePath);
            var assetType = asset.GetType();

            if (asset.ConvertableToTypes.FindIndex((x) => x == destType) >= 0)
            {
                if (context.OutputAsset.AddDependency(asset).IsSuccessed())
                    return ResultCode.S_OK;
            }
            else if (asset.ConvertableToTypes.Count > 0)
            {
                // TODO: I should do shortest path search
                // For now, try to search one by one, DFS
                foreach (var convertableType in asset.ConvertableToTypes)
                {
                    var childAsset = assetDB.CreateTargetAsset(intermediateFilePath, convertableType);
                    childAsset.IsIntermediate = true;
                    if (CreateAssetBuildPath(context, childAsset).IsSuccessed())
                    {
                        ToolDebug.Assert(childAsset.AddDependency(asset).IsSuccessed());
                        var processor = context.AssetDB.GetProcessorFor(context.Target, asset, childAsset.GetType());
                        ToolDebug.Assert(processor != null);
                        if (processor == null)
                            return ResultCode.E_FAIL;

                        return ResultCode.S_OK;
                    }
                }
            }

            ToolDebug.Error("Failed to find build path for the target. from {0} to {1}", asset.SourcePath, context.OutputAsset.SourcePath);

            return ResultCode.E_FAIL;
        }


        static ResultCode Build(AssetBuildContext context, Asset targetAsset)
        {
            if(targetAsset.AssetTypeName == ".lib"
                || targetAsset.AssetTypeName == ".exe"
                || targetAsset.AssetTypeName == ".dll"
                || targetAsset.AssetTypeName == ".so")
            {
                var objPath = Path.ChangeExtension(targetAsset.FullPath, "pdb");
                objPath = PathTool.NormalizePathAndCreate(objPath);
                context.Parameters.SetValue("pdb", objPath);
            }
            else
            {
                var objPath = targetAsset.FullPath;
                PathTool.NormalizePathAndCreate(objPath);
            }

            List<Asset> currentInput = new List<Asset>(targetAsset.Dependencies.Dependencies.Count);
            int numUpdatedDependency = 0;
            foreach (var dependency in targetAsset.BuildDependencies.Dependencies)
            {
                var sourceAsset = dependency.Value.OwnerAsset;
                var ret = Build(context, sourceAsset);
                if (ret.IsFailed())
                    return ret;

                if (sourceAsset.LatestUpdate == default(DateTime) || sourceAsset.LatestUpdate > targetAsset.LatestUpdate)
                {
                    numUpdatedDependency++;
                }
            }

            Type sourceType = null;
            foreach (var dependency in targetAsset.Dependencies.Dependencies)
            {
                var sourceAsset = dependency.Value.OwnerAsset;
                var ret = Build(context, sourceAsset);
                if (ret.IsFailed())
                    return ret;

                currentInput.Add(sourceAsset);

                // TODO: support multiple type
                ToolDebug.Assert(sourceType == null || sourceType == sourceAsset.GetType());
                sourceType = sourceAsset.GetType();

                if (sourceAsset.LatestUpdate == default(DateTime) || sourceAsset.LatestUpdate > targetAsset.LatestUpdate)
                {
                    numUpdatedDependency++;
                }
            }


            if(numUpdatedDependency > 0)
            {
                context.CurrentInputs.Clear();
                context.CurrentInputs.AddRange(currentInput);
                context.CurrentOutput = targetAsset;

                if(sourceType == null)
                {
                    ToolDebug.Assert(sourceType != null);
                    return ResultCode.E_FAIL;
                }

                var processor = context.AssetDB.GetProcessorFor(context.Target, sourceType, targetAsset.GetType());
                ToolDebug.Assert(processor != null);
                processor.Start(context);
                // TODO: let's find make it parallel
                while(!processor.IsFinished())
                {
                    System.Threading.Thread.Sleep(10);
                }

                processor.Stop();

                if (processor.ProcessResult.IsFailed())
                {
                    ToolDebug.Error("{0} is failed. {1}", processor.Name, processor.ProcessResult);
                }
            }

            return ResultCode.S_OK;
        }
    }
}


