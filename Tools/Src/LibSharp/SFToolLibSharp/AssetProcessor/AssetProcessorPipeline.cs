////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2018 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Asset processor pipeline
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

namespace SF.Asset
{
    // Build item base
    public class AssetProcessorPipeline
    {
        public List<AssetProcessor> Pipeline { get; internal set; }

        public ConcurrentBag<Asset> InputAssets { get; internal set; }

        public ConcurrentBag<Asset> OutputAssets { get; internal set; }

        public AssetProcessorPipeline()
        {
            Pipeline = new List<AssetProcessor>();
            InputAssets = new ConcurrentBag<Asset>();
            OutputAssets = new ConcurrentBag<Asset>();
        }
    }
    
}
