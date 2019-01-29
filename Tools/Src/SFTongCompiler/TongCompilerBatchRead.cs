////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2018 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Tong compiler task - read source
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

using SF.Tong;
using SF.Tong.Schema;
using SF.Tool;

namespace SFTongCompiler
{
    [Export(typeof(TongCompilerBatchRead))]
    [Export(typeof(IBatchTask))]
    class TongCompilerBatchRead : IBatchTask, IInitializable
    {
        public override int Priority => 1;

        [ImportingConstructor]
        public TongCompilerBatchRead(IBatchTaskManager manager)
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
            if(inputList == null)
            {
                Outputs.WriteLine(OutputMessageType.Error, "No input source");
                throw new InvalidDataException("Input list is empty. add parameter +in=<sourceFile>");
            }

            foreach (var input in inputList)
            {
                try
                {
                    Uri uri = new Uri(Path.GetFullPath(input.Key));
                    var docContext = new TongCompilerContext.DocumentContext();
                    docContext.ScriptDocument = Open(uri);
                    if(docContext.ScriptDocument != null)
                        m_compileContext.DocumentContexts.Add(docContext);
                }
                catch(Exception exp)
                {
                    Outputs.WriteLine(OutputMessageType.Error, "Failed to loading {0}, error:{1}", input.Value, exp.Message);
                    throw exp;
                }
            }
        }

        public ScriptDocument Open(Uri uri)
        {
            DomNode node = null;
            string filePath = uri.LocalPath;

            if (!File.Exists(filePath))
            {
                Outputs.WriteLine(OutputMessageType.Error, "Failed to open source file {0}", filePath);
                return null;
            }

            // read existing document using standard XML reader
            using (FileStream stream = new FileStream(filePath, FileMode.Open, FileAccess.Read))
            {
                ScriptReader reader = new ScriptReader(m_nodeDefinitionManager.NodeTypeManager);
                node = reader.Read(stream, uri);
            }

            ScriptDocument scriptDocument = null;
            if (node != null)
            {
                // now that the data is complete, initialize all other extensions to the Dom data
                node.InitializeExtensions();

                scriptDocument = node.Cast<ScriptDocument>();
                string fileName = Path.GetFileName(filePath);
                ControlInfo controlInfo = new ControlInfo(fileName, filePath, StandardControlGroup.Center);

                //Set IsDocument to true to prevent exception in command service if two files with the
                //  same name, but in different directories, are opened.
                controlInfo.IsDocument = true;

                scriptDocument.ControlInfo = controlInfo;
                scriptDocument.Uri = uri;
            }

            return scriptDocument;
        }

        [Import(AllowDefault = false)]
        protected TongCompilerContext m_compileContext = null;
        
        [Import(AllowDefault = false)]
        protected ScriptNodeDefinitionManager m_nodeDefinitionManager = null;
    }
}
