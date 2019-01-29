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
    class BuildScriptActionManager
    {
        static Dictionary<string, Type> stm_BuildActionMap;

        static BuildScriptActionManager()
        {
            stm_BuildActionMap = new Dictionary<string, Type>();

            // Register build classes
            RegisterClasses(Assembly.GetExecutingAssembly());
            if (Assembly.GetEntryAssembly() != Assembly.GetExecutingAssembly())
            {
                RegisterClasses(Assembly.GetEntryAssembly());
            }
        }

        static internal void RegisterClasses(Assembly assembly)
        {
            var q = from t in assembly.GetTypes()
                    where t.IsClass && t.IsSubclassOf(typeof(BuildScriptAction))
                    select t;

            var buildActions = q.ToList();
            foreach (Type buildActionType in buildActions)
            {
                var buildAction = Activator.CreateInstance(buildActionType) as BuildScriptAction;
                stm_BuildActionMap[buildAction.ScriptCommand] = buildActionType;
            }
        }

        // Parse
        static public BuildScriptAction ParseBuildAction(string commandString)
        {
            var args = commandString.Split(':');
            if (args == null || args.Length == 0) return null;

            var command = args[0];
            BuildScriptAction newAction = null;

            Type found;
            if (stm_BuildActionMap.TryGetValue(command, out found))
            {
                var buildAction = Activator.CreateInstance(found) as BuildScriptAction;
                buildAction.Arguments = args;
            }


            return newAction;
        }

    }
}
