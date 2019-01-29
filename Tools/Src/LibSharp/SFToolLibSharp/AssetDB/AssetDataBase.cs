////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2018 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Asset database
//
////////////////////////////////////////////////////////////////////////////////

using System;
using System.Reflection;
using System.IO;
using System.Collections;
using System.Collections.Concurrent;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using SF;
using SF.Tool;
using SF.Asset.Build;

namespace SF.Asset
{
    public class AssetDataBase
    {
        // build items by name(resourcePath)
        public ConcurrentDictionary<string, Asset> AssetItems { get; private set; }

        // asset data types by ext
        public ConcurrentDictionary<string, Type> AssetTypes { get; private set; }


        public ConcurrentDictionary<string, AssetProcessor> ProcessorByName { get; private set; }
        public ConcurrentDictionary<Type, AssetProcessor> ProcessorByType { get; private set; }
        public ConcurrentDictionary<Type, List<AssetProcessor>> ProcessorByInputType { get; private set; }


        // Initialize application library
        public AssetDataBase()
        {
            AssetItems = new ConcurrentDictionary<string, Asset>();
            AssetTypes = new ConcurrentDictionary<string, Type>();

            ProcessorByName = new ConcurrentDictionary<string, AssetProcessor>();
            ProcessorByType = new ConcurrentDictionary<Type, AssetProcessor>();
            ProcessorByInputType = new ConcurrentDictionary<Type, List<AssetProcessor>>();

            // Register build items
            RegisterClasses(Assembly.GetExecutingAssembly());
            if (Assembly.GetEntryAssembly() != Assembly.GetExecutingAssembly())
            {
                RegisterClasses(Assembly.GetEntryAssembly());
            }
        }

        // register all possible build processors form the assembly
        public void RegisterClasses(Assembly assembly)
        {
            foreach (Type classType in assembly.GetTypes())
            {
                if (!classType.IsClass || classType.IsAbstract) continue;

                if (classType.IsSubclassOf(typeof(AssetProcessor)))
                {
                    var buildProcessor = Activator.CreateInstance(classType) as AssetProcessor;

                    bool result = ProcessorByName.TryAdd(buildProcessor.Name, buildProcessor);
                    if(!result)
                        ToolDebug.Warning("Duplicated processor {0}", buildProcessor.Name);

                    result = ProcessorByType.TryAdd(buildProcessor.GetType(), buildProcessor);
                    if (!result)
                        ToolDebug.Warning("Duplicated processor {0}", buildProcessor.Name);

                    foreach(var inputType in buildProcessor.GetInputAssetTypes())
                    {
                        List<AssetProcessor> processorList;
                        if (!ProcessorByInputType.TryGetValue(inputType, out processorList))
                        {
                            processorList = new List<AssetProcessor>();
                            ProcessorByInputType.TryAdd(inputType, processorList);
                        }
                        if (processorList.IndexOf(buildProcessor) >= 0)
                            ToolDebug.Warning("Duplicated processor {0}", buildProcessor.Name);
                        else
                            processorList.Add(buildProcessor);
                    }
                }
                else if (classType.IsSubclassOf(typeof(Asset)))
                {
                    var assetData = Activator.CreateInstance(classType) as Asset;
                    AssetTypes.AddOrUpdate(assetData.AssetTypeName, classType, (name, oldValue) => { return classType; });
                }
                else
                {
                    continue;
                }

            }
        }

        public Asset GetItem( string resourcePath )
        {
            Asset found;
            AssetItems.TryGetValue(resourcePath, out found);
            return found;
        }

        public Asset CreateAssetByExt(string ext)
        {
            Type found;
            if(AssetTypes.TryGetValue(ext.ToLower(), out found))
            {
                return Activator.CreateInstance(found) as Asset;
            }

            return null;
        }

        public Asset CreateTargetAsset(string resourcePath, string assetTypeName)
        {
            Type assetType;
            if(!AssetTypes.TryGetValue(assetTypeName, out assetType))
            {
                ToolDebug.Error("Failed to find target type {0} for {1}", assetTypeName, resourcePath);
                return null;
            }

            resourcePath = Path.ChangeExtension(resourcePath, assetTypeName);
            resourcePath = PathTool.NormalizePathToProjectBase(resourcePath);

            var newAsset = Activator.CreateInstance(assetType, resourcePath) as Asset;


            //newAsset.SourcePath = resourcePath;
            return newAsset;
        }

        Asset CreateAssetByExt(string ext, params object[] args)
        {
            Type found;
            if(AssetTypes.TryGetValue(ext.ToLower(), out found))
            {
                return Activator.CreateInstance(found, args) as Asset;
            }

            return null;
        }

        public Asset AddOrGetAsset(string resourcePath)
        {
            resourcePath = PathTool.NormalizePathToProjectBase(resourcePath);
            var item = GetItem(resourcePath);
            if(item == null)
            {
                var ext = Path.GetExtension(resourcePath);
                item = CreateAssetByExt(ext, resourcePath);
                AddItem(item);
                return item;
            }

            ToolDebug.Assert(item.ResourcePath == resourcePath);

            return item;
        }

        public bool AddItem(Asset newItem)
        {
            if (newItem == null)
            {
                ToolDebug.Error("Failed to add a build item null");
                return false;
            }

            var addedItem = AssetItems.GetOrAdd(newItem.ResourcePath, newItem);
            if (addedItem != newItem)
            {
                ToolDebug.Error("Failed to add build item {0}", newItem.ResourcePath);
                return false;
            }

            return true;
        }

        public bool RemoveBuildItem(Asset itemToRemove)
        {
            if (itemToRemove == null)
            {
                ToolDebug.Error("Failed to remove a build item null");
                return false;
            }

            Asset removed;
            var result = AssetItems.TryRemove(itemToRemove.ResourcePath, out removed);
            if (!result)
            {
                ToolDebug.Error("Failed to remove build item {0}", itemToRemove.ResourcePath);
                return false;
            }

            return true;
        }

        public AssetProcessor GetProcessorFor(BuildTarget target, Asset asset, Type targetType)
        {
            return GetProcessorFor(target, asset.GetType(), targetType);
        }

        public AssetProcessor GetProcessorFor(BuildTarget target, Type sourceType, Type targetType)
        {
            List<AssetProcessor> processors;
            if (!ProcessorByInputType.TryGetValue(sourceType, out processors))
                return null;

            if (processors == null)
                return null;

            foreach (var processor in processors)
            {
                // supported platform check
                if (processor.AvailablePlatforms.FindIndex((x) => x == target.TargetPlatform) < 0) continue;

                var outputTypes = processor.GetOutputAssetTypes();
                foreach (var outType in outputTypes)
                {
                    if (outType == targetType)
                    {
                        var buildProcessor = Activator.CreateInstance(processor.GetType()) as AssetProcessor;
                        return buildProcessor;
                    }
                }
            }

            return null;
        }
    }
}
