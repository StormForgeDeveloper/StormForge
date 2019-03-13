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

using Sce.Atf;
using Sce.Atf.Adaptation;
using Sce.Atf.Applications;
using Sce.Atf.Controls.Adaptable.Graphs;
using Sce.Atf.Controls.Adaptable.Graphs.CircuitBasicSchema;
using Sce.Atf.Dom;
using SF.Tool;

namespace SFConvertVSProj2CMake
{
    [Export(typeof(VS2CMakeGenerateCMake))]
    [Export(typeof(IBatchTask))]
    class VS2CMakeGenerateCMake : IBatchTask, IInitializable
    {
        public override int Priority => 2;

        [ImportingConstructor]
        public VS2CMakeGenerateCMake(IBatchTaskManager manager)
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
            var makeinput = AppConfig.GetValueString("makein");
            if(makeinput == null)
            {
                Outputs.WriteLine(OutputMessageType.Error, "No input schematic specified");
                throw new InvalidDataException("No input schematic +makein=<inputSchematicFile>");
            }

            var inputSchematic = Path.GetFullPath(makeinput);
            var inputSchematicDir = Path.GetDirectoryName(Path.GetFullPath(makeinput));
            var outputFullPath = Path.Combine(inputSchematicDir, "CMakeLists.txt");

            string[] inputPattern = File.ReadAllLines(inputSchematic);

            if (!inputSchematicDir.EndsWith("\\") && !inputSchematicDir.EndsWith("/"))
                inputSchematicDir = inputSchematicDir + Path.DirectorySeparatorChar;
            Uri baseDir = new Uri(inputSchematicDir);
            m_SourceList = BuildFileListString(baseDir, m_compileContext.SourceFiles.ToList());
            m_HeaderList = BuildFileListString(baseDir, m_compileContext.HeaderFiles.ToList());

            using (StreamWriter outputStream = new StreamWriter(outputFullPath, false, Encoding.UTF8))
            {
                foreach (string line in inputPattern)
                {
                    var outputString = line.Replace("%SOURCE_LIST%", m_SourceList);
                    outputString = outputString.Replace("%HEADER_LIST%", m_HeaderList);

                    outputStream.WriteLine(outputString);
                }
            }
        }

        string BuildFileListString(Uri baseDir, IList<string> fileList)
        {
            StringBuilder listBuilder = new StringBuilder();
            foreach(var file in fileList)
            {
                Uri fullPath = new Uri(file);
                var relative = baseDir.MakeRelativeUri(fullPath);
                listBuilder.Append("\t");
                listBuilder.AppendLine(relative.ToString());
            }

            return listBuilder.ToString();
        }

        string m_SourceList;
        string m_HeaderList;

        [Import(AllowDefault = false)]
        protected VS2CMakeContext m_compileContext = null;
    }
}
