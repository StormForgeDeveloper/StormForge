////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2018 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Grouping command
//
////////////////////////////////////////////////////////////////////////////////


using System.ComponentModel.Composition;

using Sce.Atf.Applications;
using Sce.Atf.Dom;
using SF.Tong;
using Sce.Atf.Controls.Adaptable.Graphs.CircuitBasicSchema;


namespace SF.Tong.Editor
{
    /// <summary>
    /// Component that defines circuit-specific commands for group and ungroup. Grouping takes
    /// modules and the connections between them and turns those into a single element that is equivalent.</summary>
    [Export(typeof(GroupingCommands))]
    public class GroupingCommands : Sce.Atf.Controls.Adaptable.Graphs.GroupingCommands
    {
        /// <summary>
        /// Constructor</summary>
        /// <param name="commandService">Command service</param>
        /// <param name="contextRegistry">Context registry</param>
        [ImportingConstructor]
        public GroupingCommands(ICommandService commandService, IContextRegistry contextRegistry) 
            : base(commandService, contextRegistry)           
        {
            CreationOptions = GroupCreationOptions.HideUnconnectedPins;
        }

        // provide required DomNodeType
        /// <summary>
        /// Gets type for Group</summary>
        protected override DomNodeType GroupType
        {
            get { return groupType.Type; }
        }

        public override void DoCommand(object commandTag)
        {
            base.DoCommand(commandTag);

            // If the Create Group command was run, add in the default dynamic properties.
            if (commandTag is StandardCommand &&
                StandardCommand.EditGroup.Equals(commandTag))
            {
                var selectionContext = ContextRegistry.GetActiveContext<ISelectionContext>();
                var newGroup = selectionContext.GetLastSelected<ScriptGroup>();
                if (newGroup != null)
                {
                    // The "Emitter Vector" dynamic property.
                    var customAttrNode = new DomNode(dynamicPropertyType.Type, moduleType.dynamicPropertyChild);
                    customAttrNode.SetAttribute(dynamicPropertyType.nameAttribute,
                        "Emitter Vector");
                    customAttrNode.SetAttribute(dynamicPropertyType.categoryAttribute,
                        "Custom Properties");
                    customAttrNode.SetAttribute(dynamicPropertyType.descriptionAttribute,
                        "The speed and the direction that the emitter travels when it is created");
                    customAttrNode.SetAttribute(dynamicPropertyType.converterAttribute,
                        "Sce.Atf.Controls.PropertyEditing.FloatArrayConverter, Atf.Gui");
                    customAttrNode.SetAttribute(dynamicPropertyType.editorAttribute,
                        "Sce.Atf.Controls.PropertyEditing.NumericTupleEditor, Atf.Gui.WinForms:System.Single,x,y,z");
                    customAttrNode.SetAttribute(dynamicPropertyType.valueTypeAttribute, "vector3Value");
                    customAttrNode.SetAttribute(dynamicPropertyType.vector3ValueAttribute,
                        new [] {0.0f, 0.0f, 0.0f});
                    newGroup.DomNode.GetChildList(moduleType.dynamicPropertyChild).Add(customAttrNode);

                    // The "Debug Mode" dynamic property.
                    customAttrNode = new DomNode(dynamicPropertyType.Type, moduleType.dynamicPropertyChild);
                    customAttrNode.SetAttribute(dynamicPropertyType.nameAttribute,
                        "Debug Mode");
                    customAttrNode.SetAttribute(dynamicPropertyType.categoryAttribute,
                        "Custom Properties");
                    customAttrNode.SetAttribute(dynamicPropertyType.descriptionAttribute,
                        "Whether or not debug mode visualizations should be used");
                    customAttrNode.SetAttribute(dynamicPropertyType.editorAttribute,
                        "Sce.Atf.Controls.PropertyEditing.BoolEditor, Atf.Gui.WinForms");
                    customAttrNode.SetAttribute(dynamicPropertyType.valueTypeAttribute, "boolValue");
                    customAttrNode.SetAttribute(dynamicPropertyType.boolValueAttribute, false);
                    newGroup.DomNode.GetChildList(moduleType.dynamicPropertyChild).Add(customAttrNode);

                    // The "Tester Name" dynamic property.
                    customAttrNode = new DomNode(dynamicPropertyType.Type, moduleType.dynamicPropertyChild);
                    customAttrNode.SetAttribute(dynamicPropertyType.nameAttribute,
                        "Tester Name");
                    customAttrNode.SetAttribute(dynamicPropertyType.categoryAttribute,
                        "Custom Properties");
                    customAttrNode.SetAttribute(dynamicPropertyType.descriptionAttribute,
                        "The name of the person who is testing this particle effect object");
                    customAttrNode.SetAttribute(dynamicPropertyType.valueTypeAttribute, "stringValue");
                    newGroup.DomNode.GetChildList(moduleType.dynamicPropertyChild).Add(customAttrNode);

                    // The "# of Emitters" dynamic property.
                    customAttrNode = new DomNode(dynamicPropertyType.Type, moduleType.dynamicPropertyChild);
                    customAttrNode.SetAttribute(dynamicPropertyType.nameAttribute,
                        "# of Emitters");
                    customAttrNode.SetAttribute(dynamicPropertyType.categoryAttribute,
                        "Custom Properties");
                    customAttrNode.SetAttribute(dynamicPropertyType.descriptionAttribute,
                        "The number of emitter objects spawned by this emitter");
                    customAttrNode.SetAttribute(dynamicPropertyType.valueTypeAttribute, "intValue");
                    newGroup.DomNode.GetChildList(moduleType.dynamicPropertyChild).Add(customAttrNode);
                }
            }
        }
    }
}
