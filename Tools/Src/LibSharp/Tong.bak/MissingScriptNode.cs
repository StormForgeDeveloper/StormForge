////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2018 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Tong script Missing script node
//
////////////////////////////////////////////////////////////////////////////////


using Sce.Atf;
using Sce.Atf.Controls.Adaptable.Graphs;

namespace SF.Tong
{
    public class MissingScriptNode : ScriptNode
    {
        protected override void OnNodeSet()
        {
            base.OnNodeSet();
            m_missingElementType = new MissingElementType(MissingTypeName);
            m_missingElementType.Image = ResourceUtil.GetImage(Sce.Atf.Resources.PackageErrorImage);
        }

        /// <summary>
        /// Gets ICircuitElementType type</summary>
        public override ICircuitElementType ElementType
        {
            get { return m_missingElementType; }
        }

        public static string MissingTypeName = "?Missing?";
        private MissingElementType m_missingElementType;
    }
}
