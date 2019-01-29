using System;
using System.Collections.Generic;
using System.Text;
using xmldata;

namespace ProtocolBuilder
{
    class MessageNetPolicyBuilder : Builder
    {
        
        // constructor
        public MessageNetPolicyBuilder(ProtocolsProtocolGroup group, string strBasePath)
            : base(group,strBasePath)
        {
        }

        public string BuilderNamespace
        {
            get { return "Net"; }
        }

        public string OutputHeaderName()
        {
            return Group.Name + "NetPolicy.h";
        }
        public string OutputCPPName()
        {
            return Group.Name + "NetPolicy.cpp";
        }

        void BuildHPrefix()
        {
            OutStream.WriteLine("////////////////////////////////////////////////////////////////////////////////");
            OutStream.WriteLine("// ");
            OutStream.WriteLine("// CopyRight (c) 2010 MadK.");
            OutStream.WriteLine("// ");
            OutStream.WriteLine("// Author : MadK");
            OutStream.WriteLine("// ");
            OutStream.WriteLine(string.Format("// Description : {0} Message debug definitions", Group.Name));
            OutStream.WriteLine("// ");
            OutStream.WriteLine("////////////////////////////////////////////////////////////////////////////////");
            OutStream.WriteLine("");
            OutStream.WriteLine("#pragma once");
            OutStream.WriteLine("");
            OutStream.WriteLine("#include \"Common/Typedefs.h\"");
            OutStream.WriteLine("#include \"Common/PolicyDef.h\"");
            OutStream.WriteLine("#include \"Net/Netdefs.h\"");
            NewLine(3);


            // namespace definition
            OpenSection("namespace", PrjPrefix);
            OpenSection("namespace", "Policy");
            OpenSection("namespace", BuilderNamespace);


        }


        void BuildCPPPrefix()
        {
            OutStream.WriteLine("////////////////////////////////////////////////////////////////////////////////");
            OutStream.WriteLine("// ");
            OutStream.WriteLine("// CopyRight (c) 2010 MadK.");
            OutStream.WriteLine("// ");
            OutStream.WriteLine("// Author : MadK");
            OutStream.WriteLine("// ");
            OutStream.WriteLine(string.Format("// Description : {0} Message debug implementations", Group.Name));
            OutStream.WriteLine("// ");
            OutStream.WriteLine("////////////////////////////////////////////////////////////////////////////////");
            OutStream.WriteLine("");
            OutStream.WriteLine("");
            OutStream.WriteLine(string.Format("#include \"{0}\"", PreCompiledHeader));
            OutStream.WriteLine("#include \"Common/Typedefs.h\"");
            OutStream.WriteLine("#include \"Common/PolicyDef.h\"");
            OutStream.WriteLine("#include \"Net/Netdefs.h\"");
            OutStream.WriteLine("#include \"Net/Message.h\"");
            OutStream.WriteLine(string.Format("#include \"Policy/{0}\"", OutputHeaderName()));
            NewLine(3);

            // namespace definition
            OpenSection("namespace", PrjPrefix);
            OpenSection("namespace", "Policy");
            OpenSection("namespace", BuilderNamespace);
        }



        string ParamString(Parameter[] parameter)
        {
            return ParamInString(parameter);
        }

        void BuildPolicyH()
        {
            Parameter[] newparams;

            // Packer interface
            OpenSection("interface", "IMessageParser");
            if (Group.Command != null)
            {
                MatchIndent(); OutStream.WriteLine("// Command/Result ");
                foreach (ProtocolsProtocolGroupCommand msg in Group.Command)
                {
                    newparams = MakeParameters(MsgType.Cmd, msg.Cmd);
                    MatchIndent(); OutStream.WriteLine(
                        string.Format("HRESULT {0}Cmd( {1} ) = 0;", msg.Name, ParamString(newparams)));

                    newparams = MakeParameters(MsgType.Res, msg.Res);
                    MatchIndent(); OutStream.WriteLine(
                        string.Format("HRESULT {0}Res( {1} ) = 0;", msg.Name, ParamString(newparams)));
                }
            }

            if (Group.C2SEvent != null)
            {
                MatchIndent(); OutStream.WriteLine("// Client to Server ");
                foreach (ProtocolsProtocolGroupC2SEvent msg in Group.C2SEvent)
                {
                    newparams = MakeParameters(MsgType.Evt, msg.Params);
                    MatchIndent(); OutStream.WriteLine(
                        string.Format("HRESULT {0}C2SEvt( {1} ) = 0;", msg.Name, ParamString(newparams)));
                }
            }

            if (Group.S2CEvent != null)
            {
                MatchIndent(); OutStream.WriteLine("// Server to Client");
                foreach (ProtocolsProtocolGroupS2CEvent msg in Group.S2CEvent)
                {
                    newparams = MakeParameters(MsgType.Evt, msg.Params);
                    MatchIndent(); OutStream.WriteLine(
                        string.Format("HRESULT {0}S2CEvt( {1} ) = 0;", msg.Name, ParamString(newparams)));
                }
            }

            NewLine(2);

            MatchIndent(); OutStream.WriteLine("static IMessageParser& GetMessageParser();");

            NewLine();

            CloseSection();

        }

        void BuildPolicyCPP()
        {
            // Packer interface
            MatchIndent(); OutStream.WriteLine("MessageParser g_MessageParser;");

            OpenSection("interface", "IMessageParser");

            NewLine();

            MatchIndent(); OutStream.WriteLine("IMessageParser& GetMessageParser() { return g_MessageParser; }");

            NewLine();

            CloseSection();

        }

        void BuildH()
        {
            // build IParser
            OpenOutFile(OutputHeaderName());

            BuildHPrefix();

            BuildPolicyH();
            NewLine(2);


            NewLine(2);
            CloseOutFile();
        }

        void BuildCPP()
        {
            OpenOutFile(OutputCPPName());

            BuildCPPPrefix();

            BuildPolicyCPP();
            NewLine(2);


            CloseOutFile();
        }

        public void Build()
        {
            BuildH();
            BuildCPP();
        }

    }
}
