////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2018 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Tong compiler context
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



namespace SFConvertVSProj2CMake
{
    [Export(typeof(VS2CMakeContext))]
    class VS2CMakeContext : IInitializable
    {

        public HashSet<string> SourceFiles { get; } = new HashSet<string>();

        public HashSet<string> HeaderFiles { get; } = new HashSet<string>();



        [ImportingConstructor]
        public VS2CMakeContext()
        {
        }

        public void Initialize()
        {

        }
    }
}
