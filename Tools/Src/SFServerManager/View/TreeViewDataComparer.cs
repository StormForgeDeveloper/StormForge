////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2017 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Connection interface
//	
//
////////////////////////////////////////////////////////////////////////////////

using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Windows.Forms;

using Sce.Atf;
using Sce.Atf.Adaptation;
using Sce.Atf.Controls;
using Sce.Atf.Dom;

namespace SF
{
   
    /// <summary>
    /// Class to compare data items for sorting</summary>
    class TreeViewDataComparer : IComparer<TreeListView.Node>
    {
        struct ColumnInfo
        {
            public AttributeInfo AttributeInfo;
            public Func<object,object, int> CompareFunction;
        };
        private List<ColumnInfo> m_CompareAttrubites = new List<ColumnInfo>();

        /// <summary>
        /// Constructor with TreeListView</summary>
        /// <param name="control">Tree list view</param>
        public TreeViewDataComparer(TreeListView control)
        {
            m_control = control;
        }

        public void UpdateColumnAttributeList(DomNodeType type, DomNodeType type2)
        {
            // Initialize only once
            if (m_CompareAttrubites.Count != 0) return;

            // find attribute list
            m_CompareAttrubites.Clear();
            if (m_control.Columns == null || m_control.Columns.Count == 0) return;

            foreach (var column in m_control.Columns)
            {
                ColumnInfo columnInfo = new ColumnInfo();

                var type1Attr = type.GetAttributeInfo(column.Label);
                var type2Attr = type2.GetAttributeInfo(column.Label);

                if(type1Attr == null || type2Attr == null || type1Attr != type2Attr)
                {
                    m_CompareAttrubites.Add(columnInfo);
                    continue;
                }

                columnInfo.AttributeInfo = type1Attr;

                if (columnInfo.AttributeInfo.Type.ClrType == typeof(string))
                {
                    columnInfo.CompareFunction = (xValue,yValue) => { return string.Compare((string)xValue, (string)yValue); };
                }
                else if (columnInfo.AttributeInfo.Type.ClrType == typeof(int))
                {
                    columnInfo.CompareFunction = (xValue, yValue) => { return (int)xValue - (int)yValue; };
                }
                else if (columnInfo.AttributeInfo.Type.ClrType == typeof(uint))
                {
                    columnInfo.CompareFunction = (xValue, yValue) => { return (int)(uint)xValue - (int)(uint)yValue; };
                }
                else if (columnInfo.AttributeInfo.Type.ClrType == typeof(Int64))
                {
                    columnInfo.CompareFunction = (xValue, yValue) => { return (int)((Int64)xValue - (Int64)yValue); };
                }
                else if (columnInfo.AttributeInfo.Type.ClrType == typeof(UInt64))
                {
                    columnInfo.CompareFunction = (xValue, yValue) => { return (int)((Int64)(UInt64)xValue - (Int64)(UInt64)yValue); };
                }
                else
                {
                    columnInfo.CompareFunction = (xValue, yValue) => { return string.Compare(xValue.ToString(), yValue.ToString()); };
                }
                m_CompareAttrubites.Add(columnInfo);
            }
        }

        /// <summary>
        /// Compares two objects and returns a value indicating whether 
        /// one is less than, equal to, or greater than the other</summary>
        /// <param name="x">First object to compare</param>
        /// <param name="y">Second object to compare</param>
        /// <returns>Signed integer that indicates the relative values of x and y. 
        /// Less than zero: x is less than y. Zero: x equals y. Greater than zero: x is greater than y.</returns>
        public int Compare(TreeListView.Node x, TreeListView.Node y)
        {

            if ((x == null) && (y == null))
                return 0;

            if (x == null)
                return 1;

            if (y == null)
                return -1;

            if (ReferenceEquals(x, y))
                return 0;

            var lhs = x.Tag.As<DomNode>();
            var rhs = y.Tag.As<DomNode>();

            if ((lhs == null) && (rhs == null))
                return 0;

            if (lhs == null)
                return 1;

            if (rhs == null)
                return -1;

            if (!m_control.IsSortingEnabled)
            {
                return string.Compare(lhs.GetId(), rhs.GetId());
            }


            UpdateColumnAttributeList(lhs.Type, rhs.Type);


            var result = 0;

            var sortColumn = m_control.SortColumn;
            if (sortColumn >= 0 && sortColumn < m_CompareAttrubites.Count && m_CompareAttrubites[sortColumn].AttributeInfo != null)
            {
                result = CompareAttribute(m_CompareAttrubites[sortColumn], lhs, rhs);
                if (result != 0)
                {
                    if (m_control.SortOrder == SortOrder.Descending)
                        result *= -1;

                    return result;
                }
            }


            // disable normal compare
            //int maxCompare = Math.Max(m_CompareAttrubites.Count, 1); // It's too slow for large records. limits the maximum
            //for (var iFunc = 0; iFunc < maxCompare; iFunc++)
            //{
            //    if (iFunc == m_control.SortColumn[0] || iFunc == m_control.SortColumn[1]) continue;

            //    result = CompareAttribute(m_CompareAttrubites[iFunc], lhs, rhs);
            //    if (result != 0)
            //        break;
            //}

            if (m_control.SortOrder == SortOrder.Descending)
                result *= -1;

            return result;
        }

        private static int CompareAttribute(ColumnInfo column, DomNode x, DomNode y)
        {
            var xValue = x.GetAttribute(column.AttributeInfo);
            var yValue = y.GetAttribute(column.AttributeInfo);

            return column.CompareFunction(xValue, yValue);
        }

        private readonly TreeListView m_control;
    }
}
