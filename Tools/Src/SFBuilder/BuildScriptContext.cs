using System;
using System.Reflection;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using SF;
using SF.Tool;
using SF.Tool.Asset;

namespace SF.Tool.Builder
{
    public class BuildActionContext : AssetBuildContext
    {
        public AssetProcessorPipeline CurrentBuildPipeline;

        public BuildActionContext()
        {
        }
        
    }
}
