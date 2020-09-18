using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using SF.ToolLib;

using System.IO;
using System.Diagnostics;

namespace shellbridge
{
    class Program
    {
        static void Main(string[] args)
        {
            ToolEnvironment.CheckDebugOption("shellbridge");

            string command = ToolEnvironment.GetSettingString("cmd");
            string argument = ToolEnvironment.GetSettingString("arg");

            // convert path to local
            argument = argument.Replace('\\', '/');

            try
            {
                Process process = new Process();
                ProcessStartInfo startInfo = new ProcessStartInfo();
                startInfo.WindowStyle = ProcessWindowStyle.Hidden;
                startInfo.WorkingDirectory = Directory.GetCurrentDirectory();
                startInfo.FileName = command;
                startInfo.Arguments = argument;
                startInfo.UseShellExecute = false;
                startInfo.RedirectStandardError = true;
                startInfo.RedirectStandardOutput = true; 
                process.StartInfo = startInfo;
                process.Start();

                string output = process.StandardOutput.ReadToEnd();
                Console.WriteLine(output);
                output = process.StandardError.ReadToEnd();
                Console.WriteLine(output);
            }
            catch(Exception exp)
            {
                Console.WriteLine("shellbridge excetpion: {0}", exp.Message);
            }
        }
    }
}
