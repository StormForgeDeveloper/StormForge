using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using SF.ToolLib;

using System.IO;
using System.Diagnostics;
using System.Net;

namespace shellbridge
{
    class Program
    {
        static int Main(string[] args)
        {
            ToolEnvironment.CheckDebugOption("httpget");

            string outputPath = ToolEnvironment.GetSettingString("O");
            string url = ToolEnvironment.GetSettingString("url");
            string user = ToolEnvironment.GetSettingString("user");
            string password = ToolEnvironment.GetSettingString("password");

            ServicePointManager.SecurityProtocol = SecurityProtocolType.Tls12;

            try
            {
                if (string.IsNullOrEmpty(url))
                    return -1;

                // Take last part as file name
                if (string.IsNullOrEmpty(outputPath))
                {
                    var lastSlash = url.LastIndexOf('/');
                    if (lastSlash < 0)
                    {
                        return -2;
                    }

                    outputPath = url.Substring(lastSlash+1);
                }

                using (var client = new WebClient())
                {
                    if (!string.IsNullOrEmpty(user) && !string.IsNullOrEmpty(password))
                        client.Credentials = new NetworkCredential(user, password);

                    System.Console.WriteLine("Downloading {0}", url);

                    client.DownloadFile(url, outputPath);

                    System.Console.WriteLine("Downloaded to {0}", outputPath);
                }
            }
            catch(Exception exp)
            {
                Console.WriteLine("httpget excetpion: {0}", exp.Message);
            }

            return 0;
        }
    }
}
