////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2018 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Result code generator C#
//
////////////////////////////////////////////////////////////////////////////////


using System;
using System.Runtime.InteropServices;
using System.IO;
using System.Text;
using System.Xml;
using System.Xml.Serialization;
using Microsoft.VisualStudio;
using Microsoft.VisualStudio.Shell;
using Microsoft.VisualStudio.Shell.Interop;
using VSLangProj80;
using SF;
using SF.Tool;

namespace SF.Tool
{
    /// <summary>
    /// This is the generator class. 
    /// </summary>
    [ComVisible(true)]
    [Guid("EF7BDD61-55F9-41DC-99F2-D604331468F8")]
    [CodeGeneratorRegistration(typeof(ResultCodeGeneratorSharpVS), "StormForge ResultCode C# Generator", "{FAE04EC1-301F-11D3-BF4B-00C04F79EFBC}"/*vsContextGuids.vsContextGuidVCSProject*/, GeneratesDesignTimeSource = true)]
    [ProvideObject(typeof(ResultCodeGeneratorSharpVS))]
    public class ResultCodeGeneratorSharpVS : IVsSingleFileGenerator
    {
        /// <summary>
        /// Implements the IVsSingleFileGenerator.Generate method.
        /// Return default extension
        /// </summary>
        public int DefaultExtension(out string pbstrDefaultExtension)
        {
            pbstrDefaultExtension = ".cs";
            return VSConstants.S_OK;
        }


        /// <summary>
        /// Implements the IVsSingleFileGenerator.Generate method.
        /// Executes the transformation and returns the newly generated output file, whenever a custom tool is loaded, or the input file is saved
        /// </summary>
        /// <param name="wszInputFilePath">The full path of the input file. May be a null reference (Nothing in Visual Basic) in future releases of Visual Studio, so generators should not rely on this value</param>
        /// <param name="bstrInputFileContents">The contents of the input file. This is either a UNICODE BSTR (if the input file is text) or a binary BSTR (if the input file is binary). If the input file is a text file, the project system automatically converts the BSTR to UNICODE</param>
        /// <param name="wszDefaultNamespace">This parameter is meaningful only for custom tools that generate code. It represents the namespace into which the generated code will be placed. If the parameter is not a null reference (Nothing in Visual Basic) and not empty, the custom tool can use the following syntax to enclose the generated code</param>
        /// <param name="rgbOutputFileContents">[out] Returns an array of bytes to be written to the generated file. You must include UNICODE or UTF-8 signature bytes in the returned byte array, as this is a raw stream. The memory for rgbOutputFileContents must be allocated using the .NET Framework call, System.Runtime.InteropServices.AllocCoTaskMem, or the equivalent Win32 system call, CoTaskMemAlloc. The project system is responsible for freeing this memory</param>
        /// <param name="pcbOutput">[out] Returns the count of bytes in the rgbOutputFileContent array</param>
        /// <param name="pGenerateProgress">A reference to the IVsGeneratorProgress interface through which the generator can report its progress to the project system</param>
        /// <returns>If the method succeeds, it returns S_OK. If it fails, it returns E_FAIL</returns>
        int IVsSingleFileGenerator.Generate(string wszInputFilePath, string bstrInputFileContents, string wszDefaultNamespace, IntPtr[] rgbOutputFileContents, out uint pcbOutput, IVsGeneratorProgress pGenerateProgress)
        {
            if (bstrInputFileContents == null)
            {
                throw new ArgumentNullException(bstrInputFileContents);
            }

            if (wszInputFilePath == null)
            {
                throw new ArgumentNullException(bstrInputFileContents);
            }

            string InputFilePath = wszInputFilePath;
            string FileNameSpace = wszDefaultNamespace;

            try
            {
                var inputPath = Path.GetDirectoryName(InputFilePath);

                var resultCodeProcessor = new ResultCodeProcessor();
                resultCodeProcessor.LoadFacility(Path.Combine(inputPath, "ResultFacility.xml"));

                //var exporterXml = new ResultCodeExporterXml();
                using (var inputStream = new MemoryStream(Encoding.UTF8.GetBytes(bstrInputFileContents)))
                {
                    resultCodeProcessor.LoadCodes(inputStream);
                }

                resultCodeProcessor.UpdateResultCode();

                var memoryStream = new MemoryStream();
                resultCodeProcessor.GenerateSharp(memoryStream);
                if (memoryStream.Length == 0)
                {
                    rgbOutputFileContents = null;
                    pcbOutput = 0;

                    return VSConstants.E_FAIL;
                }
                else
                {
                    int outputLength = (int)memoryStream.Length;
                    rgbOutputFileContents[0] = Marshal.AllocCoTaskMem(outputLength);
                    Marshal.Copy(memoryStream.GetBuffer(), 0, rgbOutputFileContents[0], outputLength);
                    pcbOutput = (uint)outputLength;
                    return VSConstants.S_OK;
                }

            }
            catch (Exception)
            {
                rgbOutputFileContents = null;
                pcbOutput = 0;
                return VSConstants.E_FAIL;
            }
        }

    }
}