////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2018 Kyungkun Ko
// 
// Author : KyungKun Ko
//
////////////////////////////////////////////////////////////////////////////////



using System;
using System.Collections.Generic;
using System.ComponentModel.Composition;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml;
using Sce.Atf;
using Sce.Atf.Adaptation;
using Sce.Atf.Applications;
using Sce.Atf.Controls.Adaptable.Graphs;
using Sce.Atf.Controls.Adaptable.Graphs.CircuitBasicSchema;
using Sce.Atf.Dom;
using SF.Tool;

namespace SFConvertVSProj2CMake
{
    [Export(typeof(VS2CMakeImport))]
    [Export(typeof(IBatchTask))]
    class VS2CMakeImport : IBatchTask, IInitializable
    {
        public override int Priority => 1;

        [ImportingConstructor]
        public VS2CMakeImport(IBatchTaskManager manager)
            : base(manager)
        {
        }

        public void Initialize()
        {

        }

        /// <summary>
        /// Execute the task
        /// </summary>
        public override void Execute()
        {
            var inputList = AppConfig.GetValueSet("in");
            if (inputList == null)
            {
                Outputs.WriteLine(OutputMessageType.Error, "No input source");
                throw new InvalidDataException("Input list is empty. add parameter +in=<sourceFile>");
            }

            foreach (var input in inputList)
            {
                try
                {
                    Uri uri = new Uri(Path.GetFullPath(input.Key));
                    LoadXML(uri);
                }
                catch (Exception exp)
                {
                    Outputs.WriteLine(OutputMessageType.Error, "Failed to loading {0}, error:{1}", input.Value, exp.Message);
                    throw exp;
                }
            }
        }

        public bool LoadXML(Uri uri)
        {
            XmlReaderSettings settings = new XmlReaderSettings();
            settings.IgnoreComments = true;
            settings.IgnoreProcessingInstructions = true;
            //settings.IgnoreWhitespace = true;
            using (FileStream stream = new FileStream(uri.AbsolutePath, FileMode.Open, FileAccess.Read))
            using (XmlReader reader = XmlReader.Create(stream, settings))
            {
                m_SrcDir = Path.GetDirectoryName(uri.AbsolutePath);
                if (!m_SrcDir.EndsWith("\\") && !m_SrcDir.EndsWith("/"))
                    m_SrcDir = m_SrcDir + Path.DirectorySeparatorChar;

                reader.MoveToContent();

                return ReadElement(reader);
            }
        }
        protected virtual bool ReadElement(XmlReader reader)
        {
            bool IsInclude = reader.LocalName == "ClInclude";
            bool IsCompile = reader.LocalName == "ClCompile";
            if (IsInclude || IsCompile)
            {
                // read attributes
                if (reader.MoveToFirstAttribute())
                {
                    do
                    {
                        if (reader.LocalName == "Include")
                        {
                            var absolutePath = ToAbsolutePath(reader.Value);

                            if (IsInclude)
                                m_compileContext.HeaderFiles.Add(absolutePath);
                            else
                                m_compileContext.SourceFiles.Add(absolutePath);

                            break;
                        }
                    } while (reader.MoveToNextAttribute());
                }

            }

            // read all elements
            reader.MoveToElement();
            if (!reader.IsEmptyElement)
            {
                // read child elements
                while (reader.Read())
                {
                    if (reader.NodeType == XmlNodeType.Element)
                    {
                        if (!ReadElement(reader))
                            return false;
                    }
                    else if (reader.NodeType == XmlNodeType.EndElement)
                    {
                        break;
                    }
                }
            }

            reader.MoveToContent();

            return true;
        }

        string ToAbsolutePath(string inputPath)
        {
            return inputPath.Replace("$(MSBuildThisFileDirectory)", m_SrcDir);
        }


        string m_SrcDir;


        [Import(AllowDefault = false)]
        protected VS2CMakeContext m_compileContext = null;
    }
}
