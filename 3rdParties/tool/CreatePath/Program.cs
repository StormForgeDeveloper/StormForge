// See https://aka.ms/new-console-template for more information
using SF.ToolLib;

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
