////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2018 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : tool application helper
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

namespace SF.Tool
{
    static public class ToolApplication
    {
        public static string AppName { get; private set; }


        // Initialize application library
        static ToolApplication()
        {
            AppName = System.Reflection.Assembly.GetEntryAssembly().GetName().Name;

        }


        static public void StartApplication()
        {
            var tool_debug = AppConfig.GetValueSet("tool_debug");
            if(tool_debug != null)
            {
                foreach (var tool in tool_debug)
                {
                    if (tool.Key == AppName)
                    {
                        ToolDebug.Assert(false);
                        break;
                    }
                }
            }
            var toolDebugString = AppConfig.GetValue<string>("tool_debug");
            if(toolDebugString == AppName)
            {
                ToolDebug.Assert(false);
            }
        }
    }
}
