////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2018 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Asset data
//
////////////////////////////////////////////////////////////////////////////////


using System;
using System.IO;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using SF.Tool.Schema;

namespace SF.Asset
{
    // Data asset data
    public abstract class AssetData : Asset
    {
        public abstract string DataExt { get; }

        public abstract object Data { get; }

        // Build pipelines
        public AssetProcessorPipeline BuildPipeline { get; private set; }

        public AssetData(string sourcePath)
            : base(sourcePath)
        {
            BuildPipeline = new AssetProcessorPipeline();
        }
    }
    

}
