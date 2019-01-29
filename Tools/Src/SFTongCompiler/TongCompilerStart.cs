////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2018 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Tong compiler start task
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

namespace SFTongCompiler
{
    [Export(typeof(TongCompilerStart))]
    [Export(typeof(IBatchTask))]
    class TongCompilerStart : IBatchTask
    {
        public override int Priority => 0;

        [ImportingConstructor]
        public TongCompilerStart(IBatchTaskManager manager)
            : base(manager)
        {
        }

        /// <summary>
        /// Execute the task
        /// </summary>
        public override void Execute()
        {

        }

    }
}
