////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) Kyungkun Ko
// 
// Author : Kyungkun Ko
//
// Description : Network policy builder
//
////////////////////////////////////////////////////////////////////////////////

using System;
using System.Collections.Generic;
using System.Xml.Linq;
using ProtocolXml;
using SF.Tool;

namespace ProtocolCompiler
{
    class ProtocolMessageLogCppBuilder : CppBuilder
    { 
        // constructor
        public ProtocolMessageLogCppBuilder(Dictionary<string, string> settings)
            : base(settings)
        {
        }

        public virtual string OutputHeaderName()
        {
            return $"{Group.Name}MessageLog.h";
        }

        public virtual string OutputCPPName()
        {
            return $"{Group.Name}MessageLog.cpp";
        }

        string LogClassName => $"{Group.Name}MessageLog";

        protected virtual void BuildHPrefix()
        {
            OutStream.WriteLine("////////////////////////////////////////////////////////////////////////////////");
            OutStream.WriteLine("// ");
            OutStream.WriteLine("// StormForge");
            OutStream.WriteLine("// ");
            OutStream.WriteLine("// Author : Generated");
            OutStream.WriteLine("// ");
            OutStream.WriteLine(string.Format("// Description : {0} MessageLog", Group.Name));
            OutStream.WriteLine("// ");
            OutStream.WriteLine("////////////////////////////////////////////////////////////////////////////////");
            OutStream.WriteLine("");
            OutStream.WriteLine("#pragma once");
            OutStream.WriteLine("");
            OutStream.WriteLine("#include \"SFTypedefs.h\"");
            OutStream.WriteLine("#include \"Types/SFEngineTypedefs.h\"");
            OutStream.WriteLine("#include \"SFProtocol.h\"");
            OutStream.WriteLine("#include \"Net/SFNetDef.h\"");
            OutStream.WriteLine($"#include \"Protocol/{Group.Name}MessageID.h\"");
            NewLine();

            var includeSet = AppConfig.GetValueSet("include");
            if (includeSet != null)
            {
                foreach (var include in includeSet)
                {
                    OutStream.WriteLine($"#include \"{include.Key}\"");
                }
            }

            NewLine(3);


            // namespace definition
            OpenSection("namespace", PrjPrefix);

            foreach(var itForward in SF.SystemTypeInfo.CppTypeForwards)
            {
                OutStream.WriteLine("   {0}", itForward);
            }

            NewLine(2);
        }


        void BuildCPPPrefix()
        {
            OutStream.WriteLine("////////////////////////////////////////////////////////////////////////////////");
            OutStream.WriteLine("// ");
            OutStream.WriteLine("// CopyRight (c) The Braves");
            OutStream.WriteLine("// ");
            OutStream.WriteLine("// Author : Generated");
            OutStream.WriteLine("// ");
            OutStream.WriteLine(string.Format("// Description : {0} Message log implementations", Group.Name));
            OutStream.WriteLine("// ");
            OutStream.WriteLine("////////////////////////////////////////////////////////////////////////////////");
            OutStream.WriteLine("");
            OutStream.WriteLine("");
            OutStream.WriteLine(string.Format("#include \"{0}\"", PreCompiledHeader));
            OutStream.WriteLine("#include \"SFTypedefs.h\"");
            OutStream.WriteLine("#include \"Net/SFNetDef.h\"");
            OutStream.WriteLine("#include \"Net/SFMessage.h\"");
            OutStream.WriteLine($"#include \"Protocol/{OutputHeaderName()}\"");
            OutStream.WriteLine($"#include \"Protocol/{Group.Name}_generated.h\"");
            OutStream.WriteLine("#ifdef ERROR");
            OutStream.WriteLine("#undef ERROR");
            OutStream.WriteLine("#endif");
            OutStream.WriteLine("#include \"flatbuffers/flatbuffers.h\"");
            OutStream.WriteLine("#include \"flatbuffers/idl.h\"");

            NewLine(3);

            // namespace definition
            OpenSection("namespace", PrjPrefix);
        }

        void BuildClassH()
        {
            OpenSection("class", LogClassName);

            WriteLineWithIndent("private:");
            WriteLineWithIndent($"static bool stm_IsInitialized;");
            WriteLineWithIndent($"static flatbuffers::Parser stm_Parser;");
            NewLine();
            WriteLineWithIndent("public:");


            WriteLineWithIndent("static Result Initialize();");
            NewLine();

            foreach (MessageBase baseMsg in Group.Items)
            {
                if (baseMsg is ProtocolsProtocolGroupCommand)
                {
                    ProtocolsProtocolGroupCommand msg = baseMsg as ProtocolsProtocolGroupCommand;

                    WriteLineWithIndent($"static Result {msg.Name}Cmd(const char* prefix, const MessageHeader* messageHeader);");
                    WriteLineWithIndent($"static Result {msg.Name}Res(const char* prefix, const MessageHeader* messageHeader);");
                }

                if (baseMsg is ProtocolsProtocolGroupC2SEvent)
                {
                    ProtocolsProtocolGroupC2SEvent msg = baseMsg as ProtocolsProtocolGroupC2SEvent;

                    WriteLineWithIndent($"static Result {msg.Name}C2SEvt(const char* prefix, const MessageHeader* messageHeader);");
                }

                if (baseMsg is ProtocolsProtocolGroupS2CEvent)
                {
                    var msg = baseMsg as ProtocolsProtocolGroupS2CEvent;

                    WriteLineWithIndent($"static Result {msg.Name}S2CEvt(const char* prefix, const MessageHeader* messageHeader);");
                }
            }

            NewLine();

            CloseSection();
        }


        // Build parser class implementation
        void BuildMessageLogFunc(MessageBase baseMsg, string typeName)
        {
            OpenSection("Result", $"{LogClassName}::{baseMsg.Name}{typeName}(const char* prefix, const MessageHeader* messageHeader)");

            DefaultHRESULT(); NewLine();

            WriteLineWithIndent("protocolCheckPtr(messageHeader);");
            NewLine();

            string messageStructName = $"SF.Flat.{Group.Name}.{baseMsg.Name}{typeName}";
            WriteLineWithIndent("std::string packetString;");
            WriteLineWithIndent($"static const std::string tableName = \"{messageStructName}\";");
            WriteLineWithIndent($"if (stm_Parser.LookupStruct(tableName)) {{");
            WriteLineWithIndent("    flatbuffers::GenTextFromTable(stm_Parser, flatbuffers::GetRoot<flatbuffers::Table>(messageHeader->GetPayloadPtr()), tableName, &packetString);");
            WriteLineWithIndent("}");

            if (typeName == "Cmd")
            {
                WriteLineWithIndent($"SFLog(Net, {baseMsg.Trace}, \"{{0}} {Group.Name}:{baseMsg.Name}{typeName}: tid:{{1}}, sz:{{2}}: {{3}}\", prefix, messageHeader->TransactionId, messageHeader->MessageSize, packetString.length() > 0 ? packetString.c_str() : \"\");");
            }
            else if (typeName == "Res")
            {
                WriteLineWithIndent($"SFLog(Net, {baseMsg.Trace}, \"{{0}} {Group.Name}:{baseMsg.Name}{typeName}: tid:{{1}}, res:{{2}} sz:{{3}}: {{4}}\", prefix, messageHeader->TransactionId, messageHeader->GetTransactionResult(), messageHeader->MessageSize, packetString.length() > 0 ? packetString.c_str() : \"\");");
            }
            else
            {
                WriteLineWithIndent($"SFLog(Net, {baseMsg.Trace}, \"{{0}} {Group.Name}:{baseMsg.Name}{typeName}: sz:{{1}}: {{2}}\", prefix, messageHeader->MessageSize, packetString.length() > 0 ? packetString.c_str() : \"\");");
            }

            NewLine();

            WriteLineWithIndent("return hr;");


            CloseSection();
        }


        void BuildRegisterFunction(MessageBase baseMsg, string msgType)
        {
            string strLogFunction = $"{baseMsg.Name}{msgType}";
            string strMessageId = $"Message::{Group.Name}::MID_{baseMsg.Name}{msgType}";

            WriteLineWithIndent($"Protocol::MessageDebugTraceMap.insert(std::make_pair({strMessageId},&{strLogFunction}));");
        }

        void BuildMessageLogInitializeImpl()
        {
            OpenSection("Result", $"{LogClassName}::Initialize()");
            DefaultHRESULT(); NewLine();

            WriteLineWithIndent($"if (stm_IsInitialized) return hr;");

            foreach (MessageBase baseMsg in Group.Items)
            {
                if (baseMsg is ProtocolsProtocolGroupCommand)
                {
                    ProtocolsProtocolGroupCommand msg = baseMsg as ProtocolsProtocolGroupCommand;

                    BuildRegisterFunction(msg, "Cmd");
                    BuildRegisterFunction(msg, "Res");
                }

                if (baseMsg is ProtocolsProtocolGroupC2SEvent)
                {
                    ProtocolsProtocolGroupC2SEvent msg = baseMsg as ProtocolsProtocolGroupC2SEvent;

                    BuildRegisterFunction(msg, "C2SEvt");
                }

                if (baseMsg is ProtocolsProtocolGroupS2CEvent)
                {
                    var msg = baseMsg as ProtocolsProtocolGroupS2CEvent;

                    BuildRegisterFunction(msg, "S2CEvt");
                }
            }

            NewLine(2);

            WriteLineWithIndent($"Protocol::LoadFlatSchema(stm_Parser, \"{Group.Name}.fbs\");");
            WriteLineWithIndent($"stm_Parser.opts.indent_step = -1; // no new line");

            WriteLineWithIndent($"stm_IsInitialized = true;");
            NewLine();

            WriteLineWithIndent("return hr;");
            CloseSection();
        }

        void BuildMessageLogCPP()
        {
            WriteLineWithIndent($"bool {LogClassName}::stm_IsInitialized = false;");
            WriteLineWithIndent($"flatbuffers::Parser {LogClassName}::stm_Parser;");

            BuildMessageLogInitializeImpl();

            foreach (MessageBase baseMsg in Group.Items)
            {
                if (baseMsg is ProtocolsProtocolGroupCommand)
                {
                    ProtocolsProtocolGroupCommand msg = baseMsg as ProtocolsProtocolGroupCommand;

                    BuildMessageLogFunc(msg, "Cmd");
                    BuildMessageLogFunc(msg, "Res");
                }

                if (baseMsg is ProtocolsProtocolGroupC2SEvent)
                {
                    ProtocolsProtocolGroupC2SEvent msg = baseMsg as ProtocolsProtocolGroupC2SEvent;

                    BuildMessageLogFunc(msg, "C2SEvt");
                }

                if (baseMsg is ProtocolsProtocolGroupS2CEvent)
                {
                    var msg = baseMsg as ProtocolsProtocolGroupS2CEvent;

                    BuildMessageLogFunc(msg, "S2CEvt");
                }
            }
        }

        void BuildH()
        {
            // build IParser
            OpenOutFile(OutputHeaderName());

            BuildHPrefix();

            BuildClassH();
            NewLine(2);

            CloseOutFile();
        }

        void BuildCPP()
        {
            OpenOutFile(OutputCPPName());

            BuildCPPPrefix();

            BuildMessageLogCPP();
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
