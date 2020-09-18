using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
using SF.ToolLib;

namespace copyfile
{
    class Program
    {
        static int Main(string[] args)
        {
            ToolEnvironment.CheckDebugOption("copyfile");

            string srcPath = ToolEnvironment.GetSettingString("src");
            if (string.IsNullOrEmpty(srcPath))
            {
                Console.WriteLine("copyfile: Invalid src parameter is specified: {0}", srcPath);
                return 2;
            }

            string destPath = ToolEnvironment.GetSettingString("dest");
            if (string.IsNullOrEmpty(destPath))
            {
                Console.WriteLine("copyfile: Invalid dest parameter is specified : {0}", destPath);
                return 2;
            }

            bool isRecursive = ToolEnvironment.GetSetting<bool>("Recursive");

            try
            {
                PathTool.CopyFiles(ToolEnvironment.GetSettingString("BASE_PATH") + srcPath, ToolEnvironment.GetSettingString("BASE_PATH") + destPath, isRecursive);
            }
            catch(Exception exp)
            {
                Console.WriteLine("copyfile failed: exception: {0}", exp.Message);
                return 3;
            }

            return 0;
        }

    }
}
