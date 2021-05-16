////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2018 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Message Document builder
//
////////////////////////////////////////////////////////////////////////////////

using System;
using System.Collections.Generic;
using System.Text;
using ProtocolXml;
using SF;

namespace ProtocolCompiler
{
    class MessageDocBuilder : Builder
    {
        // constructor
        public MessageDocBuilder(Dictionary<string, string> settings)
            : base(settings)
        {
            BasePath = BasePath + "CSharp";
        }

        public string BuilderNamespace
        {
            get { return "Message"; }
        }

        public string OutputFileName()
        {
            return Group.Name + "MsgClass.md";
        }

        override public string ArrayLenType
        {
            get { return "UInt16"; }
        }

        void BuildPrefix()
        {
            //OutStream.WriteLine("////////////////////////////////////////////////////////////////////////////////");

            // namespace definition
            OpenSection("namespace", PrjPrefix + "." + BuilderNamespace, false);
            OpenSection("namespace", Group.Name, false);
        }

        void BuildMessageClass(MessageBase msg, string typeStr, Parameter[] newparams)
        {

        }

        void BuildMessageParserClassCSharp()
        {
            // Packer interface
            Parameter[] newparams;

            foreach (MessageBase baseMsg in Group.Items)
            {
                if (baseMsg is ProtocolsProtocolGroupCommand)
                {
                    MatchIndent(); OutStream.WriteLine("// Cmd: " + baseMsg.Desc);
                    ProtocolsProtocolGroupCommand msg = baseMsg as ProtocolsProtocolGroupCommand;

                    newparams = MakeParameters(MsgType.Cmd, msg.Cmd);
                    BuildMessageClass(msg, "Cmd", newparams);

                    newparams = MakeParameters(MsgType.Res, msg.Res);
                    BuildMessageClass(msg, "Res", newparams); NewLine();
                }

                if (baseMsg is ProtocolsProtocolGroupC2SEvent)
                {
                    MatchIndent(); OutStream.WriteLine("// C2S: " + baseMsg.Desc);
                    ProtocolsProtocolGroupC2SEvent msg = baseMsg as ProtocolsProtocolGroupC2SEvent;

                    newparams = MakeParameters(MsgType.Evt, msg.Params);
                    BuildMessageClass(msg, "C2SEvt", newparams); NewLine();
                }

                if (baseMsg is ProtocolsProtocolGroupS2CEvent)
                {
                    MatchIndent(); OutStream.WriteLine("// S2C: " + baseMsg.Desc);
                    ProtocolsProtocolGroupS2CEvent msg = baseMsg as ProtocolsProtocolGroupS2CEvent;

                    newparams = MakeParameters(MsgType.Evt, msg.Params);
                    BuildMessageClass(msg, "S2CEvt", newparams); NewLine();
                }
            }
        }


        public override void Build()
        {
            // Build Parser class
            OpenOutFile(OutputFileName());

            BuildPrefix();
            NewLine(2);


            BuildMessageParserClassCSharp();
            NewLine(2);

            NewLine(2);
            CloseOutFile();
        }

    }
}
