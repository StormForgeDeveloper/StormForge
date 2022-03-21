////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) Kyungkun Ko
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
    class MessageStringTableBuilder : CppBuilder
    {
        // constructor
        public MessageStringTableBuilder(Dictionary<string, string> settings)
            : base(settings)
        {
            IsCPPOut = true;
        }

        public string BuilderNamespace
        {
            get { return "Message"; }
        }

        public string OutputDocName()
        {
            return "string_" + Group.Name + ".txt";
        }

        void BuildPrefix()
        {
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
                OutStream.WriteLine("\t\t- Out{0}: {1} type. {2}", parameter.Name, parameter.TypeName, parameter.Desc);
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
                OutStream.WriteLine("\t\t- Out{0}: {1} type. {2}", parameter.Name, parameter.TypeName, parameter.Desc);
            }
            NewLine();
        }


        HashSet<string> StringSet = new HashSet<string>();

        void WriteStringSet()
        {
            foreach(var stringValue in StringSet)
            {
                OutStream.WriteLine("\"{0}\"", stringValue);
            }
        }

        // build parser class header
        void BuildGroupStrings()
        {
            StringSet.Add(Group.Name);

            foreach (MessageBase baseMsg in Group.Items)
            {
                if (baseMsg is ProtocolsProtocolGroupCommand)
                {
                    ProtocolsProtocolGroupCommand msg = baseMsg as ProtocolsProtocolGroupCommand;

                    StringSet.Add(msg.Name);
                    StringSet.Add(msg.Name + "Cmd");
                    StringSet.Add(msg.Name + "Res");

                    if (msg.Cmd != null)
                    {
                        foreach (var parameter in msg.Cmd)
                        {
                            StringSet.Add(parameter.Name);
                            StringSet.Add(parameter.TypeName);
                        }
                    }
                }

                if (baseMsg is ProtocolsProtocolGroupC2SEvent)
                {
                    ProtocolsProtocolGroupC2SEvent msg = baseMsg as ProtocolsProtocolGroupC2SEvent;

                    StringSet.Add(msg.Name);
                    StringSet.Add(msg.Name + "C2SEvt");

                    if (msg.Params != null)
                    {
                        foreach (var parameter in msg.Params)
                        {
                            StringSet.Add(parameter.Name);
                            StringSet.Add(parameter.TypeName);
                        }
                    }
                }

                if (baseMsg is ProtocolsProtocolGroupS2CEvent)
                {
                    ProtocolsProtocolGroupS2CEvent msg = baseMsg as ProtocolsProtocolGroupS2CEvent;

                    StringSet.Add(msg.Name);
                    StringSet.Add(msg.Name + "S2CEvt");

                    if (msg.Params != null)
                    {
                        foreach (var parameter in msg.Params)
                        {
                            StringSet.Add(parameter.Name);
                            StringSet.Add(parameter.TypeName);
                        }
                    }
                }
            }
        }



        void BuildDoc()
        {
            // Build Parser class
            OpenOutFile(OutputDocName());

            BuildGroupStrings();
            WriteStringSet();

            CloseOutFile();
        }

        public override void Build()
        {
            BuildDoc();
        }

    }
}
