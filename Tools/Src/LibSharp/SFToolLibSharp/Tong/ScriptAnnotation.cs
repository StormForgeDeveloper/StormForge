////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2018 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Tong script annotation
//
////////////////////////////////////////////////////////////////////////////////


using Sce.Atf.Dom;
using Sce.Atf.Controls.Adaptable.Graphs.CircuitBasicSchema;

namespace SF.Tong
{
    /// <summary>
    /// Adapts DomNode to script annotation, that is, note on the script</summary>
    public class ScriptAnnotation : Sce.Atf.Controls.Adaptable.Graphs.Annotation
    {
        /// <summary>
        /// Gets annotation text attribute</summary>
        protected override AttributeInfo TextAttribute
        {
            get { return annotationType.textAttribute; }
        }

        /// <summary>
        /// Gets annotation x-coordinate position attribute</summary>
        protected override AttributeInfo XAttribute
        {
            get { return annotationType.xAttribute; }
        }

        /// <summary>
        /// Gets annotation y-coordinate position attribute</summary>
        protected override AttributeInfo YAttribute
        {
            get { return annotationType.yAttribute; }
        }

        /// <summary>
        /// Gets annotation width attribute</summary>
        protected override AttributeInfo WidthAttribute
        {
            get { return annotationType.widthAttribute; }
        }

        /// <summary>
        /// Gets annotation height attribute</summary>
        protected override AttributeInfo HeightAttribute
        {
            get { return annotationType.heightAttribute; }
        }

        /// <summary>
        /// Gets annotation background color attribute</summary>
        protected override AttributeInfo BackColorAttribute
        {
            get { return annotationType.backcolorAttribute; }
        }

        /// <summary>
        /// Gets annotation foreColorAttribute color attribute</summary>
        protected override AttributeInfo ForeColorAttribute
        {
            get { return annotationType.foreColorAttribute; }
        }
    }
}
