using System;
using System.Reflection;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using SF;
using SF.Tool;

namespace SF.Tool.Builder
{
    /// <summary>
    /// Base build action
    /// </summary>
    public abstract class BuildScriptAction
    {
        /// <summary>
        /// Build command name for this action
        /// </summary>
        public abstract string ScriptCommand { get; }

        /// <summary>
        /// Build argument for this action
        /// </summary>
        public string[] Arguments { get; internal set; }

        /// <summary>
        /// Run build command
        /// </summary>
        public abstract void Run(BuildActionContext context);
    }
    
}
