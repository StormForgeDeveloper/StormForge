////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2018 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Asset reference
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
    public class AssetRef
    {
        // TODO: need to implement access to the asset
        public Asset Asset
        {
            get;
        }

        // Resource path. some unique path to a resource
        public string ResourcePath { get; internal set; }
    }


}
