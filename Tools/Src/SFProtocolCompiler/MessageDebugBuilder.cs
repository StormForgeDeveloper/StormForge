////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Debug builder
//
////////////////////////////////////////////////////////////////////////////////

using System;
using System.Collections.Generic;
using System.Text;
using ProtocolXml;

namespace ProtocolCompiler
{
    class MessageDebugBuilder : CppBuilder
    {

        // constructor
        public MessageDebugBuilder(Dictionary<string, string> settings)
            : base(settings)
        {
        }

        public string BuilderNamespace
        {
            get { return "Debug"; }
        }

        public string OutputHeaderName()
        {
            return Group.Name + "MsgDebug.h";
        }
        public string OutputCPPName()
        {
            return Group.Name + "MsgDebug.cpp";
        }

        void BuildHPrefix()
        {
            OutStream.WriteLine("////////////////////////////////////////////////////////////////////////////////");
            OutStream.WriteLine("// ");
            OutStream.WriteLine("// CopyRight (c) 2016 Kyungkun Ko");
            OutStream.WriteLine("// ");
            OutStream.WriteLine("// Author : Generated");
            OutStream.WriteLine("// ");
            OutStream.WriteLine("// Description : {0} Message debug definitions", Group.Name);
            OutStream.WriteLine("// ");
            OutStream.WriteLine("////////////////////////////////////////////////////////////////////////////////");
            OutStream.WriteLine("");
            OutStream.WriteLine("#pragma once");
            OutStream.WriteLine("");
            OutStream.WriteLine("#include \"SFTypedefs.h\"");
            OutStream.WriteLine("#include \"SFProtocol.h\"");
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
            OutStream.WriteLine("// CopyRight (c) 2016 Kyungkun Ko");
            OutStream.WriteLine("// ");
            OutStream.WriteLine("// Author : Generated");
            OutStream.WriteLine("// ");
            OutStream.WriteLine("// Description : {0} Message debug implementations", Group.Name);
            OutStream.WriteLine("// ");
            OutStream.WriteLine("////////////////////////////////////////////////////////////////////////////////");
            OutStream.WriteLine("");
            OutStream.WriteLine("");
            OutStream.WriteLine("#include \"{0}\"", PreCompiledHeader);
            OutStream.WriteLine("#include \"SFTypedefs.h\"");
            OutStream.WriteLine("#include \"SFProtocol.h\"");
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
            MatchIndent(); OutStream.WriteLine("// {0} Debug output function ", Group.Name);
            NewLine();
            MatchIndent(); OutStream.WriteLine("void RegisterDebugTrace{0}();", Group.Name);
            NewLine();
        }

        string MappingTableName()
        {
            return "MessageDebugTraceMap";
        }

        void BuildMsgMap(MsgType type, string typeString, string Name, Parameter[] inparam)
        {
            Parameter[] newparams;

            newparams = MakeParameters(type, inparam);
            string strMsgClass = string.Format("{0}::{1}", Group.Name, MsgClassName(Name, typeString));
            string strKey = string.Format("Message::{0}::MID.IDSeq.MsgID", strMsgClass);
            string strFunction = string.Format("Message::{0}::TraceOut", strMsgClass);

            MatchIndent(); OutStream.WriteLine("{0}.insert(std::make_pair({1},&{2}));", MappingTableName(), strKey, strFunction);
        }
        
        void BuildMsgMapImpl()
        {
            MatchIndent(); OutStream.WriteLine("extern std::unordered_map<uint32_t,MessageHandlingFunction> {0};", MappingTableName());
            NewLine();

            OpenSection("void", string.Format("RegisterDebugTrace{0}()", Group.Name));

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

            MatchIndent(); OutStream.WriteLine("///////////////////////////////////////////////////////////////");
            MatchIndent(); OutStream.WriteLine("// {0} Debug trace mapping", Group.Name);
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
