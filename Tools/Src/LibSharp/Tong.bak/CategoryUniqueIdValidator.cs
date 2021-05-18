////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2018 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Tong script category uniqueid validator
//
////////////////////////////////////////////////////////////////////////////////


using Sce.Atf.Dom;

namespace SF.Tong
{
    internal class CategoryUniqueIdValidator : Sce.Atf.Dom.CategoryUniqueIdValidator
    {
        internal interface IDocumentTag { }

        /// <summary>
        /// Get the id category of the given node</summary>
        protected override object GetIdCategory(DomNode node)
        {
	        return node.GetTag(typeof (CategoryUniqueIdValidator.IDocumentTag));
        }
    }
}
