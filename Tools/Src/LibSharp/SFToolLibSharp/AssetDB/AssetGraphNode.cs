////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2018 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Asset graph node
//
////////////////////////////////////////////////////////////////////////////////

using System;
using System.IO;
using System.Collections;
using System.Collections.Concurrent;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using SF;

namespace SF.Asset
{
    public class AssetGraphNode
    {
        public Asset OwnerAsset { get; private set; }

        public string Name {  get { return OwnerAsset.Name; } }
        public string SourcePath { get { return OwnerAsset.ResourcePath; } }

        // Dependency list from build pipeline
        public ConcurrentDictionary<string, AssetGraphNode> Dependencies { get; private set; }

        // Assets referencing this
        public ConcurrentDictionary<string, AssetGraphNode> References { get; private set; }

        public AssetGraphNode(Asset owner)
        {
            OwnerAsset = owner;
            Dependencies = new ConcurrentDictionary<string, AssetGraphNode>();
            References = new ConcurrentDictionary<string, AssetGraphNode>();
        }

        public bool Contains(AssetGraphNode dependency)
        {
            AssetGraphNode existDependency;
            return Dependencies.TryGetValue(dependency.SourcePath, out existDependency);
        }

        public Result AddDependency(AssetGraphNode dependency)
        {
            var added = Dependencies.AddOrUpdate(dependency.SourcePath, dependency, (x, oldValue) => {
                ToolDebug.Assert(oldValue == dependency);
                return oldValue;
            });

            if (added != dependency)
            {
                return ResultCode.SUCCESS_FALSE;
            }

            dependency.References.AddOrUpdate(SourcePath, this, (x, oldValue) => {
                ToolDebug.Assert(oldValue == this);
                return this;
            });

            return ResultCode.SUCCESS;
        }

        public void RemoveDependency(AssetGraphNode dependencyToRemove)
        {
            AssetGraphNode removed;
            var ret = Dependencies.TryRemove(dependencyToRemove.SourcePath, out removed);
            ToolDebug.Assert(ret);
            if(ret)
            {
                ret = dependencyToRemove.References.TryRemove(SourcePath, out removed);
                ToolDebug.Assert(ret);
            }
        }

        public void Clear()
        {
            foreach (var dependency in Dependencies)
            {
                AssetGraphNode removed;
                var ret = dependency.Value.References.TryRemove(SourcePath, out removed);
                ToolDebug.Assert(ret);
            }
            Dependencies.Clear();
        }
    }

}
