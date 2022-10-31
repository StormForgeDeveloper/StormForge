// See https://aka.ms/new-console-template for more information
using SF.ToolLib;

using System.Net;
using System.Net.Http.Headers;
using System.Text;

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

        outputPath = url.Substring(lastSlash + 1);
    }

    using (var client = new HttpClient())
    {
        using HttpResponseMessage response = await client.GetAsync(url);
        response.EnsureSuccessStatusCode();
        string responseBody = await response.Content.ReadAsStringAsync();

        string fileName = Path.GetFileName(url);

        if (!string.IsNullOrEmpty(user) && !string.IsNullOrEmpty(password))
        {
            var byteArray = Encoding.ASCII.GetBytes(String.Format("{0}:{1}", user, password));
            var header = new AuthenticationHeaderValue("Basic", Convert.ToBase64String(byteArray));
            client.DefaultRequestHeaders.Authorization = header;
        }

        System.Console.WriteLine("Downloading {0} to {1}", url, fileName);

        await using var ms = await response.Content.ReadAsStreamAsync();
        await using var fs = File.Create(fileName);
        ms.Seek(0, SeekOrigin.Begin);
        ms.CopyTo(fs);

        System.Console.WriteLine("Downloaded to {0}", outputPath);
    }
}
catch (Exception exp)
{
    Console.WriteLine("httpget excetpion: {0}", exp.Message);
}

return 0;
