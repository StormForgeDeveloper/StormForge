////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Path tool
//
////////////////////////////////////////////////////////////////////////////////

using System;
using System.IO;

namespace SF.Tool
{
    public static class PathTool
    {
        public static string CombinePath(string path, string filename)
        {
            if (string.IsNullOrEmpty(path)) return filename;
            if (string.IsNullOrEmpty(filename)) return path;

            path = PathTool.NormalizePath(path);
            var normalizedFilename = PathTool.NormalizePath(filename);
            if (!normalizedFilename.ToLower().StartsWith(path.ToLower()))
                return Path.Combine(path, normalizedFilename);
            else
                return normalizedFilename;
        }

        public static string NormalizePath(string path)
        {
            if (string.IsNullOrEmpty(path)) return path;

            if (path.StartsWith("~/"))
            {
                var homePath = Environment.GetFolderPath(System.Environment.SpecialFolder.Personal);
                path = string.Format("{0}{1}", homePath, path.Substring(1));
            }

            return path.Replace(Path.AltDirectorySeparatorChar, Path.DirectorySeparatorChar);
        }

        public static string NormalizePathToProjectBase(string path)
        {
            return NormalizePathToRelative(AppConfig.GetValue<string>("PROJECT_BASE"), path);
        }

        public static string NormalizePathToRelative(string pathBase, string path)
        {
            pathBase = NormalizePath(pathBase);
            path = NormalizePath(path);
            ToolDebug.Assert(pathBase != null);

            var absPath = Path.GetFullPath(path);

            bool underProjectPath = absPath.ToLower().StartsWith(pathBase.ToLower());
            if (!underProjectPath)
            {
                return path;
            }

            return absPath.Substring(pathBase.Length + 1);
        }

        public static string ConvertProjectToAbsolute(string path)
        {
            var projectBase = AppConfig.GetValue<string>("PROJECT_BASE");

            var pathLower = path.ToLower();
            bool underProjectPath = pathLower.StartsWith(projectBase.ToLower());

            if (!underProjectPath)
                path = Path.Combine(projectBase, path);

            return path;
        }

        public static string NormalizePathAndCreate(string path)
        {
            if (string.IsNullOrEmpty(path)) return path;

            string[] paths = path.Split(new char[] { Path.AltDirectorySeparatorChar, Path.DirectorySeparatorChar });
            string merged = string.IsNullOrEmpty(paths[0]) ? Path.DirectorySeparatorChar.ToString() : "";
            int iPath = 0;
            for(; iPath < (paths.Length-1); iPath++)
            {
                var pathEle = paths[iPath];
                if (iPath == 0 && pathEle == "~") // replace home
                {
                    var homePath = Environment.GetFolderPath(System.Environment.SpecialFolder.Personal);
                    pathEle = homePath;
                }

                if (pathEle == ".") // skip self indicator
                    continue;

                merged += pathEle + Path.DirectorySeparatorChar;

                // Director name can have '.'
				//if(pathEle.IndexOf(".") >= 0)
				//	break;

                if (!string.IsNullOrEmpty(pathEle)
                    && pathEle.IndexOfAny(new char[] { '*', '?' }) < 0)
                {
                    if (!Directory.Exists(merged))
                    {
                        Console.WriteLine("CreatePath {0}, {1}", pathEle, merged);
                        Directory.CreateDirectory(merged);
                    }
                }
            }

            merged += paths[iPath];

            return merged;
        }

        public static void CopyFiles(string srcPath, string destPath, bool isRecursive = true)
        {
            srcPath = PathTool.NormalizePath(srcPath);
            destPath = PathTool.NormalizePathAndCreate(destPath);
            var srcDir = Path.GetDirectoryName(srcPath);
            var srcPattern = Path.GetFileName(srcPath);
            var destFileName = Path.GetFileName(destPath);

            var srcFiles = Directory.GetFiles(srcDir, srcPattern);
            foreach(var srcFile in srcFiles)
            {
                var srcFileInfo = new FileInfo(srcFile);
                if (string.IsNullOrEmpty(destFileName))
                    srcFileInfo.CopyTo(Path.Combine(destPath, Path.GetFileName(srcFile)), true);
                else
                {
                    // if dest path is a file just copy first one
                    srcFileInfo.CopyTo(destPath, true);
                    return;
                }
            }

            if(isRecursive)
            {
                var subDirs = Directory.GetDirectories(Path.GetDirectoryName(srcPath));
                foreach (var subDir in subDirs)
                {
                    var dirName = subDir.Substring(srcDir.Length + 1);
                    var subsrcPath = Path.Combine(subDir, srcPattern);
                    var subdestPath = Path.Combine(destPath, dirName) + Path.DirectorySeparatorChar;
                    CopyFiles(subsrcPath, subdestPath);
                }
            }
        }
    }
}
