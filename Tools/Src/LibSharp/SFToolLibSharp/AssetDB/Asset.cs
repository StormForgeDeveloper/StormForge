////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2018 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Asset base
//
////////////////////////////////////////////////////////////////////////////////

using System;
using System.IO;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using SF;
using SF.Tool;

namespace SF.Asset
{
    // Generic asset item
    public abstract class Asset
    {
        // Name
        public string Name { get; internal set; }

        // Resource path. some unique path to a resource
        public string ResourcePath { get; internal set; }

        public string SourceFilePath { get; internal set; }

        // item extension
        public string AssetTypeName { get; internal set; }


        // latest file/data updated time
        DateTime m_LatestUpdate = default(DateTime);
        public DateTime LatestUpdate
        {
            get
            {
                if (m_LatestUpdate == default(DateTime))
                {
                    UpdateTime();
                }
                return m_LatestUpdate;
            }
        }

        public List<string> ConvertableToTypes { get; private set; }


        public AssetGraphNode BuildDependencies { get; private set; }

        public AssetGraphNode Dependencies { get; private set; }


        // Initialize application library
        public Asset(string sourcePath)
        {
            BuildDependencies = new AssetGraphNode(this);
            Dependencies = new AssetGraphNode(this);

            ConvertableToTypes = new List<string>();
            ResourcePath = sourcePath;
            SourceFilePath = PathTool.ConvertProjectToAbsolute(ResourcePath);
        }

        /// <summary>
        /// UpdateTime
        /// </summary>
        void UpdateTime()
        {
            // put initial datetime
            m_LatestUpdate = default(DateTime);
            if (string.IsNullOrEmpty(SourceFilePath))
            {
                return;
            }

            FileInfo info = new FileInfo(SourceFilePath);
            if(info.Exists)
                m_LatestUpdate = info.LastWriteTime;
        }

        public Asset(string itemName, string sourcePath, string itemType)
            : this(sourcePath)
        {
            Name = itemName;
            AssetTypeName = itemType.ToLower();
        }

        // manually added dependencies
        public ResultCode AddDependency(Asset dependency)
        {
            var result = Dependencies.AddDependency(dependency.Dependencies);
            if (!result.IsSuccessed())
            {
                ToolDebug.Error("Add dependency is failed: {0} <-> {1}", Name, dependency.Name);
                return result;
            }

            return new ResultCode(ResultCode.SUCCESS);
        }

        // dependencies calculated during built
        // This will be updated when it rebuilt
        public ResultCode AddBuildDependency(Asset dependency)
        {
            // Skip if they are already depend on each other
            if(Dependencies.Contains(dependency.Dependencies))
                return new ResultCode(ResultCode.SUCCESS);

            var result = BuildDependencies.AddDependency(dependency.BuildDependencies);
            if (!result.IsSuccessed())
            {
                ToolDebug.Error("Add dependency is failed: {0} <-> {1}", Name, dependency.Name);
                return result;
            }

            return new ResultCode(ResultCode.SUCCESS);
        }





    }


}
