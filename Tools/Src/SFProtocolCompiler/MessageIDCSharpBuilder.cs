////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) Kyungkun Ko.
// 
// Author : KyungKun Ko
//
// Description : CSharp network message ID maps
//
////////////////////////////////////////////////////////////////////////////////

using System;
using System.Collections.Generic;
using System.Text;
using ProtocolXml;
using SF;

namespace ProtocolCompiler
{
    class MessageIDCSharpBuilder : Builder
    {
        // constructor
        public MessageIDCSharpBuilder(Dictionary<string, string> settings)
            : base(settings)
        {
            ProtocolNamespace = settings.GetValueOrDefault("CSharpProtocolNamespace", "SF.MessageProtocol");
        }

        public string BuilderNamespace
        {
            get { return "Net"; }
        }

        string ProtocolNamespace { get; set; }

        public string OutputFileNameCS()
        {
            return $"{Group.Name}MessageID.cs";
        }


        void BuildCSPrefix()
        {
            OutStream.WriteLine("////////////////////////////////////////////////////////////////////////////////");
            OutStream.WriteLine("// ");
            OutStream.WriteLine("// CopyRight (c) StromForge");
            OutStream.WriteLine("// ");
            OutStream.WriteLine("// Author : Generated");
            OutStream.WriteLine("// ");
            OutStream.WriteLine(string.Format("// Description : {0} Message IDs", Group.Name));
            OutStream.WriteLine("// ");
            OutStream.WriteLine("////////////////////////////////////////////////////////////////////////////////");
            OutStream.WriteLine("");
            OutStream.WriteLine("");
            OutStream.WriteLine("using System;");
            OutStream.WriteLine("using System.Diagnostics;");
            OutStream.WriteLine("using System.Runtime.InteropServices;");
            OutStream.WriteLine("using SF;");
            NewLine(2);

            // namespace definition
            OpenSection("namespace", PrjPrefix + "." + BuilderNamespace, false);
        }


        TypeUsage m_ParameterMode = TypeUsage.CSharp;
        TypeUsage ParameterMode { get { return m_ParameterMode; } set { m_ParameterMode = value; } }

        // target type for output
        public override string ToTargetTypeName(Parameter param)
        {
            return SystemTypeInfo.TypeNameFor(ParameterMode, param);
        }


        int m_iCode = 0;

        string AccessPropertyName(MessageBase baseMsg, string msgTypeName)
        {
            return string.Format("{0}{1}", baseMsg.Name, msgTypeName);
        }

        string MakeMessageID(MessageBase baseMsg, SF.MessageType messageType)
        {
            string typeString = messageType.ToString();
            int reliable = baseMsg.Reliable ? 1 : 0;
            return $"MessageID.MakeMessageID(MessageType.{typeString}, {reliable}, {ProtocolNamespace}.{Group.Name}, {m_iCode})";
        }

        void PrintMessageCode(MessageBase msg, string postfix, MessageType messageType)
        {
            MatchIndent(); OutStream.WriteLine($"public static const UInt32 _{AccessPropertyName(msg, postfix)} = {MakeMessageID(msg, messageType)};");
            MatchIndent(); OutStream.WriteLine($"public static readonly MessageID {AccessPropertyName(msg, postfix)} = {MakeMessageID(msg, messageType)};");
        }

        void BuildMessageIDClassCSharp()
        {
            // Packer interface
            OpenSection("public static class", "MessageID" + Group.Name);

            m_iCode = 0;

            foreach (MessageBase baseMsg in Group.Items)
            {
                if (baseMsg is ProtocolsProtocolGroupCommand)
                {
                    MatchIndent(); OutStream.WriteLine("// Cmd: " + baseMsg.Desc);
                    ProtocolsProtocolGroupCommand msg = baseMsg as ProtocolsProtocolGroupCommand;

                    MatchIndent(); OutStream.WriteLine($"public static readonly MessageID {AccessPropertyName(baseMsg, "Cmd")} = {MakeMessageID(baseMsg, MessageType.Command)};");
                    MatchIndent(); OutStream.WriteLine($"public static readonly MessageID {AccessPropertyName(baseMsg, "Res")} = {MakeMessageID(baseMsg, MessageType.Result)};");

                    m_iCode++;

                    NewLine();
                }

                if (baseMsg is ProtocolsProtocolGroupC2SEvent)
                {
                    MatchIndent(); OutStream.WriteLine("// C2S: " + baseMsg.Desc);
                    ProtocolsProtocolGroupC2SEvent msg = baseMsg as ProtocolsProtocolGroupC2SEvent;

                    MatchIndent(); OutStream.WriteLine($"public static readonly MessageID {AccessPropertyName(baseMsg, "C2SEvt")} = {MakeMessageID(baseMsg, MessageType.Event)};");

                    m_iCode++;
                }

                if (baseMsg is ProtocolsProtocolGroupS2CEvent)
                {
                    MatchIndent(); OutStream.WriteLine("// S2C: " + baseMsg.Desc);
                    var msg = baseMsg as ProtocolsProtocolGroupS2CEvent;

                    MatchIndent(); OutStream.WriteLine($"public static readonly MessageID {AccessPropertyName(baseMsg, "S2CEvt")} = {MakeMessageID(baseMsg, MessageType.Event)};");

                    m_iCode++;
                }
            }

            CloseSection();

        }


        public override void Build()
        {
            // Build C# policy class
            IsCPPOut = false;
            ParameterMode = TypeUsage.CSharp;
            OpenOutFile(OutputFileNameCS());

            BuildCSPrefix();
            NewLine(2);

            BuildMessageIDClassCSharp();
            NewLine(2);

            NewLine(2);
            CloseOutFile();
        }

    }
}
