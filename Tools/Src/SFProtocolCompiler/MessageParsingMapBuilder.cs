////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Message parsing builder
//
////////////////////////////////////////////////////////////////////////////////

using System;
using System.Collections.Generic;
using System.Text;
using ProtocolXml;
using SF.Tool;

namespace ProtocolCompiler
{
    class MessageParsingMapBuilder : Builder
    {

        // constructor
        public MessageParsingMapBuilder(string strBasePath)
            : base(strBasePath+"Message")
        {
        }

        public string BuilderNamespace
        {
            get { return "Message"; }
        }

        public string OutputHeaderName()
        {
            return Group.Name + "MsgParsing.h";
        }
        public string OutputCPPName()
        {
            return Group.Name + "MsgParsing.cpp";
        }

        void BuildHPrefix()
        {
            OutStream.WriteLine("////////////////////////////////////////////////////////////////////////////////");
            OutStream.WriteLine("// ");
            OutStream.WriteLine("// CopyRight (c) 2017 Kyungkun Ko");
            OutStream.WriteLine("// ");
            OutStream.WriteLine("// Author : Generated");
            OutStream.WriteLine("// ");
            OutStream.WriteLine("// Description : {0} Message parsing definitions", Group.Name);
            OutStream.WriteLine("// ");
            OutStream.WriteLine("////////////////////////////////////////////////////////////////////////////////");
            OutStream.WriteLine("");
            OutStream.WriteLine("#pragma once");
            OutStream.WriteLine("");
            OutStream.WriteLine("#include \"SFTypedefs.h\"");
            OutStream.WriteLine("#include \"Protocol/SFProtocol.h\"");
            OutStream.WriteLine("#include \"Net/SFNetDef.h\"");
            OutStream.WriteLine("#include \"Protocol/{0}MsgClass.h\"", Group.Name);
            NewLine(3);

            // namespace definition
            OpenSection("namespace", PrjPrefix);
            OpenSection("namespace", "Protocol");
        }


        void BuildCPPPrefix()
        {
            OutStream.WriteLine("////////////////////////////////////////////////////////////////////////////////");
            OutStream.WriteLine("// ");
            OutStream.WriteLine("// CopyRight (c) 2017 Kyungkun Ko");
            OutStream.WriteLine("// ");
            OutStream.WriteLine("// Author : Generated");
            OutStream.WriteLine("// ");
            OutStream.WriteLine("// Description : {0} Message parsing implementations", Group.Name);
            OutStream.WriteLine("// ");
            OutStream.WriteLine("////////////////////////////////////////////////////////////////////////////////");
            OutStream.WriteLine("");
            OutStream.WriteLine("");
            OutStream.WriteLine("#include \"{0}\"", PreCompiledHeader);
            OutStream.WriteLine("#include \"SFTypedefs.h\"");
            OutStream.WriteLine("#include \"Protocol/SFProtocol.h\"");
            OutStream.WriteLine("#include \"Net/SFNetDef.h\"");
            OutStream.WriteLine("#include \"Protocol/{0}\"", OutputHeaderName());
            OutStream.WriteLine("#include \"Protocol/{0}MsgClass.h\"", Group.Name);
            NewLine(3);

            // namespace definition
            OpenSection("namespace", PrjPrefix);
            OpenSection("namespace", "Protocol");
        }

        void BuildIMessageDebugH()
        {
            NewLine();
            MatchIndent(); OutStream.WriteLine("///////////////////////////////////////////////////////////////");
            MatchIndent(); OutStream.WriteLine("// {0} parsing register function ", Group.Name);
            NewLine();
            MatchIndent(); OutStream.WriteLine("void RegisterParser{0}();", Group.Name);
            NewLine();
        }

        string MappingTableName()
        {
            return "MessageParseToVariableMap";
        }
        string MappingToMessageBaseName()
        {
            return "MessageParseToMessageBaseMap";
        }

        void BuildMsgMap(MsgType type, string typeString, string Name, Parameter[] inparam)
        {
            Parameter[] newparams;

            newparams = MakeParameters(type, inparam);
            string strMsgClass = string.Format("{0}::{1}", Group.Name, MsgClassName(Name, typeString));
            string strKey = string.Format("Message::{0}::MID.IDSeq.MsgID", strMsgClass);
            string strFunction = string.Format("Message::{0}::ParseMessageTo", strMsgClass);

            if (AppConfig.GetValue("VariableMapParser", false))
            {
                MatchIndent(); OutStream.WriteLine("{0}.insert(std::make_pair({1},&{2}));", MappingTableName(), strKey, strFunction);
            }
            MatchIndent(); OutStream.WriteLine("{0}.insert(std::make_pair({1},&{2}MessageBase));", MappingToMessageBaseName(), strKey, strFunction);
        }
        
        void BuildMsgMapImpl()
        {
            NewLine();

            if (AppConfig.GetValue("VariableMapParser", false))
            {
                MatchIndent(); OutStream.WriteLine("extern std::unordered_map<uint32_t,HandleParseMessageTo> {0};", MappingTableName());
            }
            MatchIndent(); OutStream.WriteLine("extern std::unordered_map<uint32_t,HandleParseMessageToMessageBase> {0};", MappingToMessageBaseName());

            NewLine();
            OpenSection("void", string.Format("RegisterParser{0}()", Group.Name));

            foreach (MessageBase baseMsg in Group.Items)
            {
                if (baseMsg is ProtocolsProtocolGroupCommand)
                {
                    MatchIndent(); OutStream.WriteLine("// Cmd: " + baseMsg.Desc);
                    ProtocolsProtocolGroupCommand msg = baseMsg as ProtocolsProtocolGroupCommand;

                    BuildMsgMap(MsgType.Cmd, "Cmd", msg.Name, msg.Cmd);
                    BuildMsgMap(MsgType.Res, "Res", msg.Name, msg.Res);
                }

                if (baseMsg is ProtocolsProtocolGroupC2SEvent)
                {
                    MatchIndent(); OutStream.WriteLine("// C2S: " + baseMsg.Desc);
                    ProtocolsProtocolGroupC2SEvent msg = baseMsg as ProtocolsProtocolGroupC2SEvent;

                    BuildMsgMap(MsgType.Evt, "C2SEvt", msg.Name, msg.Params);
                }

                if (baseMsg is ProtocolsProtocolGroupS2CEvent)
                {
                    MatchIndent(); OutStream.WriteLine("// S2C: " + baseMsg.Desc);
                    ProtocolsProtocolGroupS2CEvent msg = baseMsg as ProtocolsProtocolGroupS2CEvent;

                    BuildMsgMap(MsgType.Evt, "S2CEvt", msg.Name, msg.Params);
                }
            }

            CloseSection();
        }
        

        void BuildH()
        {
            // build IParser
            OpenOutFile(OutputHeaderName());

            BuildHPrefix();

            BuildIMessageDebugH();
            NewLine(2);

            NewLine(2);
            CloseOutFile();
        }

        void BuildCPP()
        {
            OpenOutFile(OutputCPPName());

            BuildCPPPrefix();

            NewLine();

            MatchIndent(); OutStream.WriteLine("///////////////////////////////////////////////////////////////");
            MatchIndent(); OutStream.WriteLine("// {0} message parser mapping", Group.Name);
            BuildMsgMapImpl();

            NewLine(2);

            CloseOutFile();
        }

        public override void Build()
        {
            BuildH();
            BuildCPP();
        }

    }
}
