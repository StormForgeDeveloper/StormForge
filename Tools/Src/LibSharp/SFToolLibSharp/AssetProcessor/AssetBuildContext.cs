////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2018 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Asset build context
//
////////////////////////////////////////////////////////////////////////////////

using System;
using System.IO;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using SF.Tool.Schema;
using SF.Tool;

namespace SF.Asset
{
    public class AssetBuildContext
    {
        public AssetDataBase AssetDB { get; set; }

        public BuildTarget Target { get; set; }
        public ToolSetting Parameters { get; set; }

        public Asset OutputAsset { get; set; }

        public List<Asset> SourceAssets { get; private set; }

        public DateTime LatestBuildTime { get; set; }

        public List<Asset> CurrentInputs { get; private set; }

        public Asset CurrentOutput { get; set; }

        public AssetBuildContext()
        {
            CurrentInputs = new List<Asset>();
            SourceAssets = new List<Asset>();
        }
    }

}
