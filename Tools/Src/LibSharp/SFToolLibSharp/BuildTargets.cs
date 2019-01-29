////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2018 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : build platform and target information
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

namespace SF
{
    public enum BuildPlatform
    {
        WIN64,
        LINUX,
        ANDROID,
        IOS,
    }

    public enum BuildConfiguration
    {
        Debug,
        Release,
        Publish,
    }

    public class BuildTarget
    {
        // target platform
        public BuildPlatform TargetPlatform;
        public BuildConfiguration TargetConfiguration;


        public BuildTarget()
        {

        }

        public BuildTarget(BuildPlatform platform, BuildConfiguration buildType)
        {
            TargetPlatform = platform;
            TargetConfiguration = buildType;
        }


        public bool Parse(string buildTargetString)
        {
            BuildPlatform platform;
            BuildConfiguration buildType;

            if(!Parse(buildTargetString, out platform, out buildType))
                return false;

            TargetPlatform = platform;
            TargetConfiguration = buildType;

            return true;
        }

        static public bool Parse(string buildTargetString, out BuildPlatform platform, out BuildConfiguration buildType)
        {
            platform = BuildPlatform.WIN64;
            buildType = BuildConfiguration.Debug;

            if (string.IsNullOrEmpty(buildTargetString))
                return false;

            var args = buildTargetString.Split('_');
            if (args.Length < 2)
                return false;

            if (!Enum.TryParse<BuildPlatform>(args[0], out platform))
                return false;

            if (!Enum.TryParse<BuildConfiguration>(args[1], out buildType))
                return false;

            return true;
        }

        public override string ToString()
        {
            return string.Format("{0}_{1}", TargetPlatform, TargetConfiguration);
        }
    }
}
