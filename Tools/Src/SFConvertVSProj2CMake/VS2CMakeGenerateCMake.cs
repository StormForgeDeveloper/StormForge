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
        public override int Priority => 1;

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
            var output = AppConfig.GetValueString("out");
            if(output == null)
            {
                Outputs.WriteLine(OutputMessageType.Error, "No input source");
                throw new InvalidDataException("Input list is empty. add parameter +in=<sourceFile>");
            }


            Uri uri = new Uri(Path.GetFullPath(output));

        }

        [Import(AllowDefault = false)]
        protected VS2CMakeContext m_compileContext = null;
    }
}
