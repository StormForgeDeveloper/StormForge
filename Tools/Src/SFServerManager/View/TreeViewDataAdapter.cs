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
using System.Linq;

using Sce.Atf;
using Sce.Atf.Adaptation;
using Sce.Atf.Applications;
using Sce.Atf.Dom;
using System.ComponentModel;
using Sce.Atf.Controls;
using Sce.Atf.Controls.DataEditing;
using System.Drawing.Design;
using Sce.Atf.Controls.PropertyEditing;

namespace SF
{
    /// <summary>
    /// Information structure for the column info
    /// </summary>
    public struct TreeListViewColumnInfo
    {
        public string Name;
        public string[] BindAttributes;
        public int DefaultWidth;
    }

    /// <summary>
    /// Adapts root DomNode to ITreeView, IItemView, and IObservableContext so it can be
    /// displayed by the TreeLister</summary>
    public class TreeViewDataAdapter : DomNodeAdapter, ITreeView, IItemView, IObservableContext, ISelectionContext
    {

        IPropertyEditingContext m_propertyContext;

        virtual public TreeListViewColumnInfo[] ListViewColumnInfos
        {
            get { return null; }
        }

        /// <summary>
        /// Child list info member info query
        /// </summary>
        public virtual ChildInfo ChildListInfo { get { return null; } }

        public DataEditorTheme Theme { get; set; }


        public TreeViewDataAdapter()
        {
            m_selection.Changing += TheSelectionChanging;
            m_selection.Changed += TheSelectionChanged;


            if (s_dataImageIndex == -1)
            {
                s_dataImageIndex =
                    ResourceUtil.GetImageList16().Images.IndexOfKey(
                        Resources.DataImage);
            }

            if (s_folderImageIndex == -1)
            {
                s_folderImageIndex =
                    ResourceUtil.GetImageList16().Images.IndexOfKey(
                        Resources.FolderImage);
            }

        }



        /// <summary>
        /// Performs initialization when the adapter is connected to the tree view's DomNode</summary>
        protected override void OnNodeSet()
        {
            DomNode.AttributeChanged += root_AttributeChanged;
            DomNode.ChildInserted += root_ChildInserted;
            DomNode.ChildRemoved += root_ChildRemoved;
            Reloaded.Raise(this, EventArgs.Empty);

            base.OnNodeSet();
        }

        public void BindPropertyContext(IPropertyEditingContext context)
        {
            m_propertyContext = context;
        }

        #region IObservableContext Members

        /// <summary>
        /// Event that is raised when a tree item is inserted</summary>
        public event EventHandler<ItemInsertedEventArgs<object>> ItemInserted;

        /// <summary>
        /// Event that is raised when a tree item is removed</summary>
        public event EventHandler<ItemRemovedEventArgs<object>> ItemRemoved;

        /// <summary>
        /// Event that is raised when a tree item is changed</summary>
        public event EventHandler<ItemChangedEventArgs<object>> ItemChanged;

        /// <summary>
        /// Event that is raised when the tree is reloaded</summary>
        public event EventHandler Reloaded;

        #endregion

        #region ITreeView Members

        /// <summary>
        /// Gets the root object of the tree</summary>
        public object Root
        {
            get { return DomNode; }
        }

        /// <summary>
        /// Gets the children of the given parent object</summary>
        /// <param name="parent">Parent object</param>
        /// <returns>Children of the parent object</returns>
        public IEnumerable<object> GetChildren(object parent)
        {
            DomNode node = parent as DomNode;
            if (node != null)
            {
                // get child Dom nodes and empty reference "slots"
                foreach (ChildInfo childInfo in node.Type.Children)
                {
                    // skip over control points.
                    if (childInfo.IsList)
                    {
                        foreach (DomNode child in node.GetChildList(childInfo))
                            yield return child;
                    }
                    else
                    {
                        DomNode child = node.GetChild(childInfo);
                        if (child != null)
                        {
                            yield return child;
                        }
                    }
                }
            }
        }

        #endregion


        #region IItemView Interface



        /// <summary>
        /// Fills in or modifies the given display info for the item</summary>
        /// <param name="obj">Item</param>
        /// <param name="info">Display info to update</param>
        public void GetInfo(object obj, ItemInfo info)
        {
            var data = obj.As<DomNode>();
            if (data == null)
                return;

            info.ImageIndex = data.Children.Count() > 0 ? s_folderImageIndex : s_dataImageIndex;

            var nameAttributeInfo = data.Type.GetAttributeInfo("Name");
            if (nameAttributeInfo != null)
                info.Label = data.GetAttribute(nameAttributeInfo) as string;
            else
                info.Label = data.GetId();

            info.IsLeaf = !GetChildren(data).Any();


            //if (editorList.Count > 0)
            //    info.Properties = editorList.ToArray();
            List<object> propList = new List<object>();
            for (int iColumn = 0; iColumn < ListViewColumnInfos.Length; iColumn++)
            {
                var column = ListViewColumnInfos[iColumn];
                AttributeInfo attributeInfo = null;
                if (column.BindAttributes != null)
                {
                    foreach(var itAttributeName in column.BindAttributes)
                    {
                        attributeInfo = data.Type.GetAttributeInfo(itAttributeName);
                        if (attributeInfo != null)
                            break;
                    }
                }
                if (attributeInfo == null)
                {
                    propList.Add(null);
                    continue;
                }

                var propDesc = GetPropDescription(data.Type, attributeInfo);
                var editor = GetEditor(data, propDesc);

                // editor should hold column name
                if (editor != null)
                    editor.Name = column.Name;

                propList.Add(editor);
            }

            info.Properties = propList.ToArray();
        }


        AttributePropertyDescriptor GetPropDescription(DomNodeType nodeType, AttributeInfo attrInfo)
        {
            if (nodeType == null)
                return null;

            var descriptionTag = nodeType.GetTag(typeof(PropertyDescriptorCollection)) as PropertyDescriptorCollection;
            if (descriptionTag != null)
            {
                foreach (AttributePropertyDescriptor description in descriptionTag)
                {
                    if (description.Name == attrInfo.Name)
                        return description;
                }
            }

            return GetPropDescription(nodeType.BaseType, attrInfo);
        }

        DataEditor GetEditor(DomNode node, AttributePropertyDescriptor desc)
        {
            var transactionContext = m_propertyContext.As<ITransactionContext>();
            if (desc == null)
            {
                return null;
            }

            var maxRule = desc.AttributeInfo.Type.GetRule<NumericMaxRule>();
            var mainule = desc.AttributeInfo.Type.GetRule<NumericMinRule>();


            DataEditor newEditor = null;
            bool usePropertyContext = true;
            switch (desc.AttributeInfo.Type.ClrType.Name)
            {
                case "Boolean":
                    newEditor = new BoolDataEditor(Theme);
                    break;
                case "Single":
                    newEditor = new FloatDataEditor(Theme)
                    {
                        Max = maxRule != null ? (float)maxRule.MaximumValue : float.MaxValue,
                        Min = maxRule != null ? (float)mainule.MinimumValue : float.MinValue,
                    };
                    break;
                case "Int32":
                    newEditor = new IntDataEditor(Theme)
                    {
                        Value = (int)node.GetAttribute(desc.AttributeInfo),
                        Max = maxRule != null ? (int)maxRule.MaximumValue : int.MaxValue,
                        Min = maxRule != null ? (int)mainule.MinimumValue : int.MinValue,
                    };
                    break;
                case "UInt32":
                    newEditor = new IntDataEditor(Theme)
                    {
                        Max = maxRule != null ? (int)maxRule.MaximumValue : int.MaxValue,
                        Min = maxRule != null ? (int)mainule.MinimumValue : 0,
                    };
                    break;
                case "Int64":
                    newEditor = new Int64DataEditor(Theme)
                    {
                        Value = (Int64)node.GetAttribute(desc.AttributeInfo),
                        Max = maxRule != null ? (Int64)maxRule.MaximumValue : Int64.MaxValue,
                        Min = maxRule != null ? (Int64)mainule.MinimumValue : Int64.MinValue,
                    };
                    break;
                case "UInt64":
                    newEditor = new Int64DataEditor(Theme)
                    {
                        Max = maxRule != null ? (Int64)maxRule.MaximumValue : Int64.MaxValue,
                        Min = maxRule != null ? (Int64)mainule.MinimumValue : 0,
                    };
                    break;
                case "String":
                    var enumRule = desc.AttributeInfo.Type.GetRule<StringEnumRule>();
                    if (enumRule != null)
                    {
                        newEditor = new EnumDataEditor(Theme, enumRule.Values as string[]);
                    }
                    else
                    {
                        newEditor = new StringDataEditor(Theme);
                    }
                    break;

                // Not supported for now
                case "DateTime":
                    newEditor = new DateTimeDataEditor(Theme);
                    break;

                //case "DomNode":
                //    var refSetting = desc.GetValue(node).As<GameDataSetting>();
                //    if (refSetting != null)
                //    {
                //        usePropertyContext = false;

                //        newEditor = new StringDataEditor(Theme)
                //        {
                //            ReadOnly = true,
                //            Value = refSetting.Name,
                //        };
                //    }
                //    break;
                default:
                    throw new Exception("Not supported attribute type");
            }

            if (newEditor != null)
            {
                newEditor.ReadOnly = desc.IsReadOnly;

                if (usePropertyContext)
                    newEditor.EditingContext = new DataEditorPropertyContext(node, desc, transactionContext);
                newEditor.Name = desc.Name;
            }

            return newEditor;
        }


        #endregion


        #region ISelectionContext Interface

        /// <summary>
        /// Gets or sets the enumeration of selected items</summary>
        public IEnumerable<object> Selection
        {
            get { return m_selection; }
            set { m_selection.SetRange(value); }
        }

        /// <summary>
        /// Returns all selected items of the given type</summary>
        /// <typeparam name="T">Desired item type</typeparam>
        /// <returns>All selected items of the given type</returns>
        public IEnumerable<T> GetSelection<T>() where T : class
        {
            return m_selection.AsIEnumerable<T>();
        }

        /// <summary>
        /// Gets the last selected item</summary>
        public object LastSelected
        {
            get { return m_selection.LastSelected; }
        }

        /// <summary>
        /// Gets the last selected item of the given type; this may not be the same
        /// as the LastSelected item</summary>
        /// <typeparam name="T">Desired item type</typeparam>
        /// <returns>Last selected item of the given type</returns>
        public T GetLastSelected<T>() where T : class
        {
            return m_selection.GetLastSelected<T>();
        }

        /// <summary>
        /// Returns whether the selection contains the given item</summary>
        /// <param name="item">Item</param>
        /// <returns>True iff the selection contains the given item</returns>
        /// <remarks>Override to customize how items are compared for equality, e.g., for
        /// tree views, the selection might be adaptable paths, in which case the override
        /// could compare the item to the last elements of the selected paths.</remarks>
        public bool SelectionContains(object item)
        {
            return m_selection.Contains(item);
        }

        /// <summary>
        /// Gets the number of items in the current selection</summary>
        public int SelectionCount
        {
            get { return m_selection.Count; }
        }

        /// <summary>
        /// Event that is raised before the selection changes</summary>
        public event EventHandler SelectionChanging;

        /// <summary>
        /// Event that is raised after the selection changes</summary>
        public event EventHandler SelectionChanged;

        #endregion


        private void TheSelectionChanging(object sender, EventArgs e)
        {
            SelectionChanging.Raise(this, EventArgs.Empty);
        }

        private void TheSelectionChanged(object sender, EventArgs e)
        {
            SelectionChanged.Raise(this, EventArgs.Empty);
        }

        private void root_AttributeChanged(object sender, AttributeEventArgs e)
        {
            ItemChanged.Raise(this, new ItemChangedEventArgs<object>(e.DomNode));

            // because references use the name of the referenced item as their label, we should
            //  update all references to this DomNode. Fortunately, we can use the ReferenceValidator
            //  which is attached to this (root) node to get all the references.
            ReferenceValidator validator = this.As<ReferenceValidator>();
            if(validator != null)
            {
                foreach (Pair<DomNode, AttributeInfo> reference in validator.GetReferences(e.DomNode))
                {
                    ItemChanged.Raise(this, new ItemChangedEventArgs<object>(reference.First));
                }
            }
        }

        private void root_ChildInserted(object sender, ChildEventArgs e)
        {
            ItemInserted.Raise(this, new ItemInsertedEventArgs<object>(-1, e.Child, e.Parent));
        }

        private void root_ChildRemoved(object sender, ChildEventArgs e)
        {
            ItemRemoved.Raise(this, new ItemRemovedEventArgs<object>(-1, e.Child, e.Parent));
        }

        private int GetChildIndex(object child, object parent)
        {
            // get child index by re-constructing what we'd give the tree control
            System.Collections.IEnumerable treeChildren = GetChildren(parent);
            int i = 0;
            foreach (object treeChild in treeChildren)
            {
                if (treeChild.Equals(child))
                    return i;
                i++;
            }
            return -1;
        }

        /// <summary>
        /// Add a child
        /// </summary>
        /// <param name="child"></param>
        public void AddChild(DomNode child)
        {
            var childList = DomNode.GetChildList(ChildListInfo);
            childList.Add(child);
        }

        /// <summary>
        /// Clear children
        /// </summary>
        public void ClearChildren()
        {
            var childList = DomNode.GetChildList(ChildListInfo);
            childList.Clear();
        }

        private static int s_dataImageIndex = -1;
        private static int s_folderImageIndex = -1;
        private readonly Selection<object> m_selection = new Selection<object>();

    }
}
