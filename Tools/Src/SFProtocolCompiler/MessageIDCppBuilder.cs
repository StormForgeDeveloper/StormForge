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
using SF.Tool;

namespace ProtocolCompiler
{
    class MessageIDCppBuilder : Builder
    {
        // constructor
        public MessageIDCppBuilder(Dictionary<string, string> settings)
            : base(settings)
        {
        }

        public string BuilderNamespace
        {
            get { return "Message"; }
        }

        public string OutputFileName()
        {
            return Group.Name + "MessageID.h";
        }

        void BuildPrefix()
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
            OutStream.WriteLine("#pragma once");
            OutStream.WriteLine("#include \"Net/SFMessage.h\"");
            OutStream.WriteLine("#include \"SFProtocol.h\"");

            var includeSet = AppConfig.GetValueSet("include");
            if (includeSet != null)
            {
                foreach(var include in includeSet)
                {
                    OutStream.WriteLine($"#include \"{include.Value}\"");
                }
            }

            NewLine(2);

            // namespace definition
            OpenSection("namespace", PrjPrefix, false);
            OpenSection("namespace", "Message", false);
            OpenSection("namespace", Group.Name, false);
        }

        void BuildPostfix()
        {
            CloseAllSection();
        }

        int m_iCode = 0;

        string AccessPropertyName(MessageBase baseMsg, string msgTypeName)
        {
            return string.Format("MID_{0}{1}", baseMsg.Name, msgTypeName);
        }
        string MakeMessageID(MessageBase baseMsg, SF.MessageType messageType)
        {
            string typeString = messageType.ToString();
            int reliable = baseMsg.Reliable ? 1 : 0;
            return $"(MessageType::{typeString},{reliable},MessageProtocol::{Group.Name},{m_iCode})";
        }


        void BuildMessageIDClass()
        {
            m_iCode = 0;

            foreach (MessageBase baseMsg in Group.Items)
            {
                if (baseMsg is ProtocolsProtocolGroupCommand)
                {
                    MatchIndent(); OutStream.WriteLine("// Cmd: " + baseMsg.Desc);
                    ProtocolsProtocolGroupCommand msg = baseMsg as ProtocolsProtocolGroupCommand;

                    MatchIndent(); OutStream.WriteLine($"constexpr MessageID {AccessPropertyName(baseMsg, "Cmd")}{MakeMessageID(baseMsg, MessageType.Command)};");
                    MatchIndent(); OutStream.WriteLine($"constexpr MessageID {AccessPropertyName(baseMsg, "Res")}{MakeMessageID(baseMsg, MessageType.Result)};");

                    m_iCode++;

                    NewLine();
                }

                if (baseMsg is ProtocolsProtocolGroupC2SEvent)
                {
                    MatchIndent(); OutStream.WriteLine("// C2S: " + baseMsg.Desc);
                    ProtocolsProtocolGroupC2SEvent msg = baseMsg as ProtocolsProtocolGroupC2SEvent;

                    MatchIndent(); OutStream.WriteLine($"constexpr MessageID {AccessPropertyName(baseMsg, "C2SEvt")}{MakeMessageID(baseMsg, MessageType.Event)};");

                    m_iCode++;
                }

                if (baseMsg is ProtocolsProtocolGroupS2CEvent)
                {
                    MatchIndent(); OutStream.WriteLine("// S2C: " + baseMsg.Desc);
                    var msg = baseMsg as ProtocolsProtocolGroupS2CEvent;

                    MatchIndent(); OutStream.WriteLine($"constexpr MessageID {AccessPropertyName(baseMsg, "S2CEvt")}{MakeMessageID(baseMsg, MessageType.Event)};");

                    m_iCode++;
                }
            }
        }


        public override void Build()
        {
            IsCPPOut = true;
            OpenOutFile(OutputFileName());

            BuildPrefix();
            NewLine(2);

            BuildMessageIDClass();
            NewLine(2);

            BuildPostfix();
            NewLine();

            CloseOutFile();
        }

    }
}
