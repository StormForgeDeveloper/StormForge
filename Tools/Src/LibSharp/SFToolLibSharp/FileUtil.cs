////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2018 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : file utility
//
////////////////////////////////////////////////////////////////////////////////

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
using System.Threading.Tasks;

namespace SF.Tool
{
    public class FileUtil
    {
        static public void WriteIfChanged(string strTargetPath, byte[] bufferDataToWrite, long length, bool forceWrite = false)
        {
            strTargetPath = PathTool.NormalizePath(strTargetPath);
            PathTool.NormalizePathAndCreate(Path.GetFullPath(strTargetPath));
            //string targetDir = Path.GetDirectoryName(strTargetPath);
            string targetFileName = Path.GetFileName(strTargetPath);

            var sourceFileBuffer = new byte[7 * 1024];
            int sourceFileReadSize = 0;
            var targetFileBuffer = new byte[7 * 1024];
            int targetFileReadSize = 0;


            bool bIsMissMatched = false;
            try
            {
                using (var source = new FileStream(strTargetPath, FileMode.Open, FileAccess.Read, FileShare.Read))
                using (var memoryFile = new MemoryStream(bufferDataToWrite, 0, (int)length, false))
                {
                    if(source.Length != length)
                        bIsMissMatched = true;

                    while (!bIsMissMatched)
                    {
                        sourceFileReadSize = source.Read(sourceFileBuffer, 0, sourceFileBuffer.Length);
                        targetFileReadSize = memoryFile.Read(targetFileBuffer, 0, targetFileBuffer.Length);

                        if (targetFileReadSize != sourceFileReadSize)
                        {
                            bIsMissMatched = true;
                            break;
                        }
                        else if (targetFileReadSize == 0)
                        {
                            break;
                        }

                        int iChar = 0;
                        for (iChar = 0; iChar < sourceFileReadSize; iChar++)
                        {
                            if (sourceFileBuffer[iChar] != targetFileBuffer[iChar])
                            {
                                bIsMissMatched = true;
                                break;
                            }
                        }
                    }
                }
            }
            catch (Exception exp)
            {
                System.Diagnostics.Debug.WriteLine(exp.Message);
                // maybe file not exist, create new one
                bIsMissMatched = true;
            }

            if (bIsMissMatched)
            {
                Console.WriteLine("Writing : " + targetFileName);
                using (var source = new FileStream(strTargetPath, FileMode.Create, FileAccess.Write, FileShare.None))
                {
                    source.Write(bufferDataToWrite, 0, (int)length);
                }
            }
            else
            {
                //Console.WriteLine("All updated. Skipping : " + targetFileName);
            }
        }


        static public void CopyIfChanged(string strTargetPath, string sourceFilePath)
        {
            string targetFilePath = strTargetPath + sourceFilePath;
            string targetDir = Path.GetDirectoryName(targetFilePath);

            Directory.CreateDirectory(targetDir);

            char[] sourceFileBuffer = new char[7 * 1024];
            int sourceFileReadSize = 0;
            char[] targetFileBuffer = new char[7 * 1024];
            int targetFileReadSize = 0;

            bool bIsMissMatched = false;
            using (FileStream source = new FileStream(sourceFilePath, FileMode.Open, FileAccess.Read, FileShare.Read))
            using (StreamReader sourceFile = new StreamReader(source, Encoding.UTF8))
            {
                try
                {
                    using (FileStream target = new FileStream(targetFilePath, FileMode.Open, FileAccess.Read, FileShare.Read))
                    using (StreamReader targetFile = new StreamReader(target, Encoding.UTF8))
                    {
                        while (!bIsMissMatched)
                        {
                            sourceFileReadSize = sourceFile.Read(sourceFileBuffer, 0, sourceFileBuffer.Length);
                            targetFileReadSize = targetFile.Read(targetFileBuffer, 0, targetFileBuffer.Length);
                            if (targetFileReadSize != sourceFileReadSize)
                            {
                                bIsMissMatched = true;
                                break;
                            }
                            else if (targetFileReadSize == 0)
                            {
                                break;
                            }

                            int iChar = 0;
                            for (iChar = 0; iChar < sourceFileReadSize; iChar++)
                            {
                                if (sourceFileBuffer[iChar] != targetFileBuffer[iChar])
                                {
                                    bIsMissMatched = true;
                                    break;
                                }
                            }
                        }
                    }
                }
                catch (System.IO.IOException)
                {
                    // maybe file not exist, create new one
                    bIsMissMatched = true;
                }
            }

            if (!bIsMissMatched)
                return;

            Console.WriteLine("Copying : " + targetFilePath);

            File.Copy(sourceFilePath, targetFilePath, true);
        }

    }
}
