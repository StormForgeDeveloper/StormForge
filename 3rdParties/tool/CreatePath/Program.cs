using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;
using SF.ToolLib;

namespace CreatePath
{
    class Program
    {
        static int Main(string[] args)
        {
            ToolEnvironment.CheckDebugOption("createpath");

            if (args.Length < 1)
            {
                Console.WriteLine("CreatePath: No parameter is specified");
                return 1;
            }

            string path = args[0];
            if (string.IsNullOrEmpty(path))
            {
                Console.WriteLine("CreatePath: Invalid parameter is specified");
                return 2;
            }


            if (!path.EndsWith("/") || !path.EndsWith("\\"))
                path += "/";

            PathTool.NormalizePathAndCreate(path);

            return 0;
        }
    }
}
