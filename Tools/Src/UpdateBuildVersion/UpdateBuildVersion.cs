using System.Diagnostics;

string DepotPath = "";
string RootDepotPath = "";


Console.WriteLine("Starting CommandLine Build");

ParseCommandLineArguments();

var versionControl = new SF.Tool.VersionControlPerforce();

uint revision = versionControl.GetCurrentRevision(RootDepotPath);

string localFilePath = versionControl.GetLocalFilePath(DepotPath);

versionControl.CheckOutFile(DepotPath);

Console.WriteLine($"Writing revision:{revision} to {localFilePath}");

File.WriteAllText(localFilePath, revision.ToString());

Console.WriteLine("Finished command line build");


void ParseCommandLineArguments()
{
	string[] args = System.Environment.GetCommandLineArgs();

	DepotPath = "";
	RootDepotPath = "";

	string argumentString;
	for (int i = 0; i < args.Length; i++)
	{
		argumentString = args[i];
		Console.WriteLine(" InputArg:{0}", argumentString);
		if (argumentString.StartsWith("-versionfile=", StringComparison.CurrentCultureIgnoreCase) == true)
		{
			DepotPath = argumentString.Substring("-versionfile=".Length);
		}
		else if (argumentString.StartsWith("-depotroot=", StringComparison.CurrentCultureIgnoreCase) == true)
		{
			RootDepotPath = argumentString.Substring("-depotroot=".Length);
		}
	}

	if (string.IsNullOrEmpty(DepotPath) || string.IsNullOrEmpty(RootDepotPath))
	{
		throw new Exception("requires both -versionfile and -depotroot");
	}
}

