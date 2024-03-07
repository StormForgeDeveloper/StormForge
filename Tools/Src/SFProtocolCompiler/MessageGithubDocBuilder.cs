////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2018 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Protocol github doc builder
//
////////////////////////////////////////////////////////////////////////////////

using System;
using System.Collections.Generic;
using ProtocolXml;
using SF;
using SF.Tool;

namespace ProtocolCompiler
{
    class MessageGithubDocBuilder : CppBuilder
    {
        // constructor
        public MessageGithubDocBuilder(Dictionary<string, string> settings)
            : base(settings)
        {
            BasePath = System.IO.Path.Combine(BasePath, "Doc");
            GenParameterRouteHopCount = true;
            IsCPPOut = true;
        }

        public string BuilderNamespace
        {
            get { return "Message"; }
        }

        public string OutputDocName()
        {
            return "ProtocolAPIDoc_" + Group.Name + ".md";
        }

        void BuildPrefix()
        {
            OutStream.WriteLine("***");
            OutStream.WriteLine(" ");
            OutStream.WriteLine(" CopyRight (c) {0} StormForge", BuildYear);
            OutStream.WriteLine(" ");
            OutStream.WriteLine(" Description : {0} Message Protocol API Document", Group.Name);
            OutStream.WriteLine("");
            OutStream.WriteLine("***");
            OutStream.WriteLine("");
            OutStream.WriteLine("");
            NewLine(1);

            OutStream.WriteLine("{0}", Group.Desc);
            OutStream.WriteLine("");

            // namespace definition
            OutStream.WriteLine("namespace {0}::{1}::{2}", PrjPrefix, BuilderNamespace, Group.Name);
            OutStream.WriteLine("");
            NewLine(1);
        }


        // build API doc class
        void BuildAPIDoc(ProtocolXml.MessageBase msg, MsgType msgType, string typeName, Parameter[] parameters)
        {
            string Name = msg.Name;

            OutStream.WriteLine("## {0}{1}", msg.Name, typeName);

            OutStream.WriteLine("{0}", msg.Desc);
            OutStream.WriteLine("");

            // Build function
            OutStream.WriteLine("        Result {0}{1}({2})", msg.Name, typeName, ParamInString(parameters));
            NewLine();

            // Parameter descriptions
            //OutStream.WriteLine("**Parameter descriptions**");
            foreach (var parameter in parameters)
            {
                OutStream.WriteLine("\t\t- Out{0}: {1} type. {2}", InParamName(parameter.Name), parameter.TypeName, parameter.Desc);
                NewLine();
            }
        }

        // Build API DOC for command/result message
        void BuildAPIDoc(ProtocolXml.MessageBase msg, Parameter[] cmdParameters, Parameter[] resultParameters)
        {
            string Name = msg.Name;

            OutStream.WriteLine("## {0} Request", msg.Name);

            OutStream.WriteLine("{0}", msg.Desc);
            OutStream.WriteLine("");

            // Build function
            OutStream.WriteLine("1. Command interface");
            OutStream.WriteLine("");
            OutStream.WriteLine("        Result {0}Cmd({1})", msg.Name, ParamInString(cmdParameters));
            NewLine();

            // Parameter descriptions
            foreach (var parameter in cmdParameters)
            {
                OutStream.WriteLine($"\t\t- {parameter.Name}: type:{parameter.TypeName}, {parameter.Desc}");
                NewLine();
            }


            // Build function
            OutStream.WriteLine("2. Result interface");
            NewLine(); 
            OutStream.WriteLine("C++: Cast message to {0}Res to access values", msg.Name); NewLine();
            NewLine();

            // Parameter descriptions
            foreach (var parameter in resultParameters)
            {
                OutStream.WriteLine($"\t\t- {parameter.Name}: type:{parameter.TypeName}, {parameter.Desc}");
            }
            NewLine();
        }

        // build parser class header
        void BuildGroupDoc()
        {
            Parameter[] newparams;
            string strClassName = string.Format("{0}", Group.Name);
            string policyClassName = PolicyClassName;

            MatchIndent(); OutStream.WriteLine("# Protocol interface class {0}", policyClassName);

            foreach (MessageBase baseMsg in Group.Items)
            {
                if (baseMsg is ProtocolsProtocolGroupCommand)
                {
                    ProtocolsProtocolGroupCommand msg = baseMsg as ProtocolsProtocolGroupCommand;

                    newparams = MakeParameters(MsgType.Cmd, msg.Cmd);
                    BuildAPIDoc(msg, MakeParameters(MsgType.Cmd, msg.Cmd), MakeParameters(MsgType.Res, msg.Res));
                    NewLine();
                }

                if (baseMsg is ProtocolsProtocolGroupC2SEvent)
                {
                    ProtocolsProtocolGroupC2SEvent msg = baseMsg as ProtocolsProtocolGroupC2SEvent;

                    newparams = MakeParameters(MsgType.Evt, msg.Params);
                    BuildAPIDoc(msg, MsgType.Evt, "C2SEvt", newparams);
                    NewLine();
                }

                if (baseMsg is ProtocolsProtocolGroupS2CEvent)
                {
                    ProtocolsProtocolGroupS2CEvent msg = baseMsg as ProtocolsProtocolGroupS2CEvent;

                    newparams = MakeParameters(MsgType.Evt, msg.Params);
                    BuildAPIDoc(msg, MsgType.Evt, "S2CEvt", newparams);
                    NewLine();
                }
            }
        }



        void BuildDoc()
        {
            // Build Parser class
            OpenOutFile(OutputDocName());

            BuildPrefix();

            BuildGroupDoc();
            NewLine(2);

            NewLine(2);
            CloseOutFile();
        }

        public override void Build()
        {
            BuildDoc();
        }

    }
}
