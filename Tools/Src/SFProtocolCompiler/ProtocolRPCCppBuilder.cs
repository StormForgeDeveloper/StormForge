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
using ProtocolXml;
using SF.Tool;

namespace ProtocolCompiler
{
    class ProtocolRPCCppBuilder : CppBuilder
    { 
        // constructor
        public ProtocolRPCCppBuilder(Dictionary<string, string> settings)
            : base(settings)
        {
        }

        public virtual string OutputHeaderName()
        {
            return $"{Group.Name}RPCSendAdapter.h";
        }

        public virtual string OutputCPPName()
        {
            return $"{Group.Name}RPCSendAdapter.cpp";
        }


        protected virtual void BuildHPrefix()
        {
            OutStream.WriteLine("////////////////////////////////////////////////////////////////////////////////");
            OutStream.WriteLine("// ");
            OutStream.WriteLine("// StormForge");
            OutStream.WriteLine("// ");
            OutStream.WriteLine("// Author : Generated");
            OutStream.WriteLine("// ");
            OutStream.WriteLine(string.Format("// Description : {0} RPC Send interface", Group.Name));
            OutStream.WriteLine("// ");
            OutStream.WriteLine("////////////////////////////////////////////////////////////////////////////////");
            OutStream.WriteLine("");
            OutStream.WriteLine("#pragma once");
            OutStream.WriteLine("");
            OutStream.WriteLine("#include \"SFTypedefs.h\"");
            OutStream.WriteLine("#include \"Types/SFEngineTypedefs.h\"");
            OutStream.WriteLine("#include \"SFProtocol.h\"");
            OutStream.WriteLine("#include \"Net/SFNetDef.h\"");
            OutStream.WriteLine("#include \"MessageBus/SFRPCSendAdapter.h\"");
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

            OutStream.WriteLine("   class MessageEndpoint;");
            OutStream.WriteLine("   class VariableTable;");
            OutStream.WriteLine("   struct ActorMovement;");

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
            OutStream.WriteLine(string.Format("// Description : {0} Message debug implementations", Group.Name));
            OutStream.WriteLine("// ");
            OutStream.WriteLine("////////////////////////////////////////////////////////////////////////////////");
            OutStream.WriteLine("");
            OutStream.WriteLine("");
            OutStream.WriteLine(string.Format("#include \"{0}\"", PreCompiledHeader));
            OutStream.WriteLine("#include \"SFTypedefs.h\"");
            OutStream.WriteLine("#include \"Net/SFNetDef.h\"");
            OutStream.WriteLine("#include \"Net/SFMessage.h\"");
            OutStream.WriteLine("#include \"Net/SFMessageEndpoint.h\"");
            OutStream.WriteLine("#include \"Actor/Movement/SFActorMovement.h\"");
            OutStream.WriteLine($"#include \"Protocol/{OutputHeaderName()}\"");
            OutStream.WriteLine($"#include \"Protocol/{Group.Name}MessageID.h\"");
            OutStream.WriteLine($"#include \"{Group.Name}_generated.h\"");


            NewLine(3);

            // namespace definition
            OpenSection("namespace", PrjPrefix);
        }

        public override string ParamInString(Parameter[] parameter, bool bUseOriginalType = false)
        {
            string strParams = "";

            if (parameter == null)
                return strParams;

            string Separator = "";
            foreach (Parameter param in parameter)
            {
                strParams += Separator;
                Separator = ", ";

                if (param.IsArray) // array
                {
                    strParams += string.Format("const {0}& {1}", InArrayTypeName(param), InParamName(param.Name));
                }
                else if (IsStrType(param)) // string type
                {
                    strParams += string.Format("const {0} {1}", StrTypeString(param), InParamName(param.Name));
                }
                else // generic type
                {
                    strParams += string.Format("const {0} &{1}", ToTargetTypeName(param), InParamName(param.Name));
                }
            }

            return strParams;
        }

        protected virtual void BuildServerPolicyH()
        {
            Parameter[] newparams;

            OpenSection("class", $"{SvrRPCSendAdapterClassName} : public RPCSendAdapter");
            WriteLineWithIndent("public:");
            WriteLineWithIndent("// Constructor");
            WriteLineWithIndent($"{SvrRPCSendAdapterClassName} (MessageEndpoint* pEndpoint, flatbuffers::FlatBufferBuilder* pBuilder = nullptr) : RPCSendAdapter(pEndpoint, pBuilder)");
            WriteLineWithIndent("{}");
            WriteLineWithIndent($"{SvrRPCSendAdapterClassName} (const SharedPointerT<MessageEndpoint>& pEndpoint) : RPCSendAdapter(pEndpoint.get())");
            WriteLineWithIndent("{}");
            NewLine();

            foreach (MessageBase baseMsg in Group.Items)
            {
                if (baseMsg is ProtocolsProtocolGroupCommand)
                {
                    WriteLineWithIndent("// Cmd: " + baseMsg.Desc);
                    ProtocolsProtocolGroupCommand msg = baseMsg as ProtocolsProtocolGroupCommand;

                    newparams = MakeParameters(MsgType.Res, msg.Res);
                    WriteLineWithIndent(
                        string.Format("Result {0}Res( {1} );", msg.Name, ParamInString(newparams)));
                }

                if (baseMsg is ProtocolsProtocolGroupS2CEvent)
                {
                    WriteLineWithIndent("// S2C: " + baseMsg.Desc);
                    ProtocolsProtocolGroupS2CEvent msg = baseMsg as ProtocolsProtocolGroupS2CEvent;

                    newparams = MakeParameters(MsgType.Evt, msg.Params);
                    WriteLineWithIndent(
                        string.Format("Result {0}S2CEvt( {1} );", msg.Name, ParamInString(newparams)));
                }
            }

            NewLine();

            CloseSection();
        }

        void BuildIClientPolicyH()
        {
            Parameter[] newparams;

            OpenSection("class", $"{RPCSendAdapterClassName} : public RPCSendAdapter");
            WriteLineWithIndent("public:");
            WriteLineWithIndent("// Constructor");
            WriteLineWithIndent($"{RPCSendAdapterClassName} (MessageEndpoint* pEndpoint, flatbuffers::FlatBufferBuilder* pBuilder = nullptr) : RPCSendAdapter(pEndpoint, pBuilder)");
            WriteLineWithIndent("{}");
            WriteLineWithIndent($"{RPCSendAdapterClassName} (const SharedPointerT<MessageEndpoint>& pEndpoint) : RPCSendAdapter(pEndpoint.get())");
            WriteLineWithIndent("{}");
            NewLine();

            foreach (MessageBase baseMsg in Group.Items)
            {
                if (baseMsg is ProtocolsProtocolGroupCommand)
                {
                    WriteLineWithIndent("// Cmd: " + baseMsg.Desc);
                    ProtocolsProtocolGroupCommand msg = baseMsg as ProtocolsProtocolGroupCommand;

                    newparams = MakeParameters(MsgType.Cmd, msg.Cmd);
                    WriteLineWithIndent(
                        string.Format("Result {0}Cmd( {1} );", msg.Name, ParamInString(newparams)));
                }

                if (baseMsg is ProtocolsProtocolGroupC2SEvent)
                {
                    WriteLineWithIndent("// C2S: " + baseMsg.Desc);
                    ProtocolsProtocolGroupC2SEvent msg = baseMsg as ProtocolsProtocolGroupC2SEvent;

                    newparams = MakeParameters(MsgType.Evt, msg.Params);
                    WriteLineWithIndent(
                        string.Format("Result {0}C2SEvt( {1} );", msg.Name, ParamInString(newparams)));
                }
            }

            NewLine();

            CloseSection();
        }

        public void BuildFlatbufferPacket(string packetClassName, Parameter[] parameter)
        {

            foreach (Parameter param in parameter)
            {
                if (param.Name == "TransactionID")
                    continue;

                if (param.Name == "Result")
                {
                    continue;
                }

                var flatTypeName = FlatbufferUtil.ToFlatType(param);
                bool bIsScalar = FlatbufferUtil.IsScalar(flatTypeName);
                if (param.IsArray)
                {
                    WriteLineWithIndent($"auto {param.Name}Offset = SF::Flat::Helper::Create{param.TypeName}Vector(fbb, {InParamName(param.Name)});");
                }
                else
                {
                    if (bIsScalar)
                    {
                    }
                    else
                    {
                        WriteLineWithIndent($"auto {param.Name}Offset = SF::Flat::Helper::Create{param.TypeName}(fbb, {InParamName(param.Name)});");
                    }
                }

            }

            WriteLineWithIndent($"SF::Flat::{Group.Name}::{packetClassName}Builder _builder(fbb);");

            foreach (Parameter param in parameter)
            {
                var flatTypeName = FlatbufferUtil.ToFlatType(param);
                bool bIsScalar = FlatbufferUtil.IsScalar(flatTypeName);

                // TransactionId included in message header
                if (param.Name == "TransactionID")
                    continue;

                if (param.Name == "Result")
                {
                    continue;
                }

                string flatVariableName = FlatbufferUtil.ToFlatVariableName(param.Name);

                if (param.IsArray)
                {
                    WriteLineWithIndent($"_builder.add_{flatVariableName}({param.Name}Offset);");
                }
                else
                {
                    if (bIsScalar)
                    {
                        if (param.TypeName == "Result")
                        {
                            WriteLineWithIndent($"_builder.add_{flatVariableName}((int){InParamName(param.Name)});");
                        }
                        else
                        {
                            WriteLineWithIndent($"_builder.add_{flatVariableName}({InParamName(param.Name)});");
                        }
                    }
                    else
                    {
                        WriteLineWithIndent($"_builder.add_{flatVariableName}({param.Name}Offset);");
                    }
                }

            }

            WriteLineWithIndent($"flatbuffers::Offset<SF::Flat::{Group.Name}::{packetClassName}> packetOffset = _builder.Finish();");
            WriteLineWithIndent($"fbb.Finish(packetOffset);");
        }

        // Build parser class implementation
        void BuildNetPolicyClassParserImpl( string Name, string typeName, Parameter[] parameters)
        {
            if((typeName == "Cmd") || (typeName == "C2SEvt"))
                OpenSection("Result", $"{RPCSendAdapterClassName}::{Name}{typeName}( {ParamInString(parameters)} )");
            else
                OpenSection("Result", $"{SvrRPCSendAdapterClassName}::{Name}{typeName}( {ParamInString(parameters)} )" );

            DefaultHRESULT(); NewLine();

            WriteLineWithIndent("protocolCheckPtr(m_Endpoint);");
            NewLine();
            WriteLineWithIndent($"flatbuffers::FlatBufferBuilder& fbb = GetBuilderForNew();");

            string packetClassName = $"{Name}{typeName}";

            BuildFlatbufferPacket(packetClassName, parameters);

            NewLine();

            if (typeName == "Cmd")
            {
                WriteLineWithIndent($"protocolCheck(Send(InTransactionID, ResultCode::SUCCESS, Message::{Group.Name}::MID_{packetClassName}, fbb));\n");
            }
            else if (typeName == "Res")
            {
                WriteLineWithIndent($"protocolCheck(Send(InTransactionID, InResult, Message::{Group.Name}::MID_{packetClassName}, fbb));\n");
            }
            else
            {
                WriteLineWithIndent($"protocolCheck(Send(TransactionID(), ResultCode::SUCCESS, Message::{Group.Name}::MID_{packetClassName}, fbb));\n");
            }

            NewLine();

            WriteLineWithIndent("return hr;");


            CloseSection();
        }

        void BuildSvrPolicyCPP()
        {
            Parameter[] newparams;

            foreach (MessageBase baseMsg in Group.Items)
            {
                if (baseMsg is ProtocolsProtocolGroupCommand)
                {
                    WriteLineWithIndent("// Cmd: " + baseMsg.Desc);
                    ProtocolsProtocolGroupCommand msg = baseMsg as ProtocolsProtocolGroupCommand;

                    newparams = MakeParameters(MsgType.Res, msg.Res);
                    BuildNetPolicyClassParserImpl(msg.Name, "Res", newparams);
                }

                if (baseMsg is ProtocolsProtocolGroupS2CEvent)
                {
                    WriteLineWithIndent("// S2C: " + baseMsg.Desc);
                    ProtocolsProtocolGroupS2CEvent msg = baseMsg as ProtocolsProtocolGroupS2CEvent;

                    newparams = MakeParameters(MsgType.Evt, msg.Params);
                    BuildNetPolicyClassParserImpl(msg.Name, "S2CEvt", newparams);
                }
            }

        }

        void BuildClientPolicyCPP()
        {
            Parameter[] newparams;

            foreach (MessageBase baseMsg in Group.Items)
            {
                if (baseMsg is ProtocolsProtocolGroupCommand)
                {
                    WriteLineWithIndent("// Cmd: " + baseMsg.Desc);
                    ProtocolsProtocolGroupCommand msg = baseMsg as ProtocolsProtocolGroupCommand;

                    newparams = MakeParameters(MsgType.Cmd, msg.Cmd);
                    BuildNetPolicyClassParserImpl(msg.Name, "Cmd", newparams);
                }

                if (baseMsg is ProtocolsProtocolGroupC2SEvent)
                {
                    WriteLineWithIndent("// C2S: " + baseMsg.Desc);
                    ProtocolsProtocolGroupC2SEvent msg = baseMsg as ProtocolsProtocolGroupC2SEvent;

                    newparams = MakeParameters(MsgType.Evt, msg.Params);
                    BuildNetPolicyClassParserImpl(msg.Name, "C2SEvt", newparams);
                }
            }
        }

        void BuildH()
        {
            // build IParser
            OpenOutFile(OutputHeaderName());

            BuildHPrefix();

            BuildIClientPolicyH();
            NewLine(2);

            BuildServerPolicyH();
            NewLine(2);

            CloseOutFile();
        }

        void BuildCPP()
        {
            OpenOutFile(OutputCPPName());

            BuildCPPPrefix();

            BuildClientPolicyCPP();
            NewLine(2);

            BuildSvrPolicyCPP();
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
