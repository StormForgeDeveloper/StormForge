////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2018 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Tong script node element information
//
////////////////////////////////////////////////////////////////////////////////


using Sce.Atf.Controls.Adaptable.Graphs;

namespace SF.Tong
{
    /// <summary>
    /// These are additional options per circuit element, that are returned by the
    /// ICircuitElement.ElementInfo property. class implements ICircuitElement.</summary>
    public class ScriptNodeElementInfo : CircuitElementInfo
    {
        /// <summary>
        /// Gets or sets whether this circuit element should be displayed in an enabled state.
        /// The default is 'true'.</summary>
        public bool Enabled
        {
            get { return m_enabled; }
            set
            {
                if (m_enabled != value)
                {
                    m_enabled = value;
                    OnPropertyChanged("Enabled");
                }
            }
        }

        private bool m_enabled = true;
    }
}
