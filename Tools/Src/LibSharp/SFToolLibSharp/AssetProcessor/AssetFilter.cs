////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2018 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Asset filter
//
////////////////////////////////////////////////////////////////////////////////

using System;
using System.IO;
using SF.Tool;
using SF.Tool.Schema;

namespace SF.Asset.Build
{
    public abstract class AssetFilter : AssetProcessor
    {

        /// <summary>
        /// Run build command
        /// </summary>
        public override void Start(AssetBuildContext context)
        {
            Process(context);
        }

        // Process asset
        public abstract void Process(AssetBuildContext context);
    }

}
