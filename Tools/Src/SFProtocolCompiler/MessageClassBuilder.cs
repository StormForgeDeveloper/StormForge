////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Message parser builder
//
////////////////////////////////////////////////////////////////////////////////

using System;
using System.Collections.Generic;
using System.Linq;
using ProtocolXml;
using SF;
using SF.Tool;

namespace ProtocolCompiler
{
    class MessageClassBuilder : CppBuilder
    {
        // Msg type string
        static string[] MsgTypeString = new string[] {
                    "EMessageType::NetCtrl",
                    "EMessageType::Command",
                    "EMessageType::Result",
                    "EMessageType::Event",
                };

        // Message guaranteed level string
        static string[] MsgReliablityString = new string[]{
                "MSGTYPE_NONE",
                "MSGTYPE_RELIABLE",
            };

        // Message broadcast mode string
        static string[] MsgBroadcastString = new string[]{
                "MSGTYPE_NONE",
                "MSGTYPE_BROADCAST",
            };


        // Message code generation serial
        int m_MessageCodeIndex;

        string LogFunctionPrefix;

        // constructor
        public MessageClassBuilder(Dictionary<string, string> settings)
            : base(settings)
        {
            IsCPPOut = true;
            LogFunctionPrefix = AppConfig.GetValueString("LogFuncPrefix", "SFLog(Net,");
        }

        public string BuilderNamespace
        {
            get { return "Message"; }
        }

        public string OutputClassHeaderName()
        {
            return Group.Name + "MsgClass.h";
        }

        public string OutputClassCPPName()
        {
            return Group.Name + "MsgClass.cpp";
        }

        void BuildHPrefix()
        {
            OutStream.WriteLine("////////////////////////////////////////////////////////////////////////////////");
            OutStream.WriteLine("// ");
            OutStream.WriteLine("// CopyRight (c) StormForge");
            OutStream.WriteLine("// ");
            OutStream.WriteLine("// Author : Generated");
            OutStream.WriteLine("// ");
            OutStream.WriteLine("// Description : {0} Message parser definitions", Group.Name);
            OutStream.WriteLine("// ");
            OutStream.WriteLine("////////////////////////////////////////////////////////////////////////////////");
            OutStream.WriteLine("");
            OutStream.WriteLine("#pragma once");
            OutStream.WriteLine("");
            OutStream.WriteLine("#include \"SFProtocol.h\"");
            OutStream.WriteLine("#include \"Net/SFMessage.h\"");
            OutStream.WriteLine("#include \"Types/SFEngineTypedefs.h\"");
            OutStream.WriteLine("#include \"Variable/SFVariableTable.h\"");
            OutStream.WriteLine("#include \"Container/SFArray.h\"");
            OutStream.WriteLine("#include \"Actor/Movement/SFActorMovement.h\"");
            if (AppConfig.GetValue("VariableMapParser", false))
            {
                OutStream.WriteLine("#include \"Variable/SFVariableMapBuilder.h\"");
            }

            foreach (var itCppInclude in SystemTypeInfo.CppTypeIncludes)
            {
                OutStream.WriteLine("#include \"{0}\"", itCppInclude);
            }

            OutStream.WriteLine($"#include \"Protocol/{Group.Name}MessageID.h\"");
            NewLine(3);

            // namespace definition
            OpenSection("namespace", PrjPrefix );
            OpenSection("namespace", BuilderNamespace);
            OpenSection("namespace", Group.Name);
        }

        void BuildCPPPrefix( string HeaderName )
        {
            OutStream.WriteLine("////////////////////////////////////////////////////////////////////////////////");
            OutStream.WriteLine("// ");
            OutStream.WriteLine("// CopyRight (c) StormForge");
            OutStream.WriteLine("// ");
            OutStream.WriteLine("// Author : Generated");
            OutStream.WriteLine("// ");
            OutStream.WriteLine("// Description : {0} Message parser implementations", Group.Name);
            OutStream.WriteLine("// ");
            OutStream.WriteLine("////////////////////////////////////////////////////////////////////////////////");
            OutStream.WriteLine("");
            OutStream.WriteLine("");
            OutStream.WriteLine("#include \"{0}\"", PreCompiledHeader );
            OutStream.WriteLine("#include \"SFProtocol.h\"");
            OutStream.WriteLine("#include \"Util/SFToString.h\"");
            OutStream.WriteLine("#include \"Net/SFNetToString.h\"");
            OutStream.WriteLine("#include \"Container/SFArray.h\"");
            OutStream.WriteLine("#include \"SFProtocolHelper.h\"");
            OutStream.WriteLine("#include \"Protocol/{0}\"", HeaderName);

            NewLine(3);

            // namespace definition
            OpenSection("namespace", PrjPrefix);
            OpenSection("namespace", BuilderNamespace);
            OpenSection("namespace", Group.Name);
        }


        void BuildMessageTrace(string Name, string typeName, string traceChannel, Parameter[] parameters)
        {
            string strClassName = MsgClassName(Name, typeName);
            OpenSection("Result", strClassName + "::TraceOut(const char* prefix, const MessageHeader* pHeader)");


            string strTrace = $"{traceChannel}, \"{Group.Name}::{Name}, {{0}}:{{1}} ";
            string strTraceMember = "prefix, pHeader->Length";
            int ParamCount = 2;

            MatchIndent(); OutStream.WriteLine("{0} parser;", strClassName);
            MatchIndent(); OutStream.WriteLine("parser.ParseMessage(pHeader);");

            if (parameters != null)
            {
                foreach (Parameter param in parameters)
                {
                    var typeInfo = SystemTypeInfo.GetParameterInfo(param);
                    //var csharpType = SystemTypeInfo.ToCSharpType(param.Type);

                    switch (param.TypeName)
                    {
                        case "String":
                            {
                                strTrace += string.Format(", {0}:{{{1},60}}", param.Name, ParamCount++);
                                strTraceMember += string.Format(", parser.Get{0}()", param.Name);
                            } break;
                        default:
                            if (param.IsArray)
                            {
                                strTrace += string.Format(", {0}:{{{1},30}}", param.Name, ParamCount++);
                                strTraceMember += string.Format(", parser.Get{0}()", param.Name);
                            }
                            else if (param.TypeName == "Result")
                            {
                                strTrace += string.Format(", {0}:{{{1}:X8}}", param.Name, ParamCount++);
                                strTraceMember += string.Format(", parser.Get{0}()", param.Name);
                            }
                            else if(typeInfo.IsEnum)
                            {
                                strTrace += string.Format(", {0}:{{{1}}}", param.Name, ParamCount++);
                                strTraceMember += string.Format(", (int)parser.Get{0}()", param.Name);
                            }
                            else
                            {
                                strTrace += string.Format(", {0}:{{{1}}}", param.Name, ParamCount++);
                                strTraceMember += string.Format(", parser.Get{0}()", param.Name);
                            }
                            break;
                    }
                }
            }

            MatchIndent(); OutStream.WriteLine("{0} {1},", LogFunctionPrefix, strTrace + "\"");
            MatchIndent(1); OutStream.WriteLine("\t{0}); ", strTraceMember);

            MatchIndent(); OutStream.WriteLine("return ResultCode::SUCCESS;");

            CloseSection();

            NewLine();
        }

        // Builder parameter string
        string BuilderParamString(Parameter[] parameter, bool bUseOriginalType = false)
        {
            string param = ParamInString(parameter, bUseOriginalType);
            if (param.Length > 0)
                return "MessageHeader* messageBuffer, " + param;
            else
                return "MessageHeader* messageBuffer";
        }

        // Make message ID macro string 
        string MakeMsgIDStr(MsgType type, bool reliablity, bool broadcast, string MsgName)
        {
            return $"MessageID({MsgTypeString[(int)type]}, {MsgReliablityString[reliablity ? 1 : 0]}, {MsgBroadcastString[broadcast ? 1 : 0]}, MessageProtocol::{Group.Name}, {m_MessageCodeIndex})";
        }

        static Parameter[] GenerateParameterTypeInfoList = new Parameter[]
        {
            new Parameter() { Name = "TransactionID", TypeName = "TransactionID" },
            new Parameter() { Name = "RouteContext", TypeName = "RouteContext" },
        };

        bool HasInternalTypeOverride(Parameter[] parameters)
        {
            bool bHas = false;

            if (parameters == null)
                return bHas;

            foreach (Parameter param in parameters)
            {
                bHas |= !IsStrType(param) && !param.IsArray && IsVariableSizeType(param);
            }
            return bHas;
        }

        // build parser class
        void BuildParserClass(ProtocolXml.MessageBase msg, MsgType msgType, string typeName, Parameter[] parameters)
        {
            string Name = msg.Name;
            string strClassName = MsgClassName(Name, typeName);
            OpenSection("class", strClassName + " : public MessageBase");
            MatchIndent(-1); OutStream.WriteLine("public:");

            MatchIndent(); OutStream.WriteLine($"static constexpr MessageID MID = MID_{strClassName};");

            // Generate parameter Indicators for Template implementations
            MatchIndent(); OutStream.WriteLine("// Parameter type informations for template");
            var parameterNameMap = new Dictionary<string, Parameter>();
            if (parameters != null)
            {
                foreach (Parameter param in parameters)
                {
                    if (parameterNameMap.ContainsKey(param.Name))
                    {
                        Console.WriteLine("{0} is duplicated in {1}", param.Name, msg.Name);
                    }
                    parameterNameMap.Add(param.Name, param);
                }
            }

            if (GenerateParameterTypeInfoList.Count() > 0)
            {
                OpenSection("enum", "ParameterTypeInfo");
                foreach (var parameterName in GenerateParameterTypeInfoList)
                {
                    MatchIndent(); OutStream.WriteLine("Has{0} = {1},", parameterName.Name, parameterNameMap.ContainsKey(parameterName.Name) ? 1 : 0);
                }
                CloseSection();
            }

            // Add fake access functions
            MatchIndent(-1); OutStream.WriteLine("public:");
            foreach (var parameter in GenerateParameterTypeInfoList)
            {
                if (parameterNameMap.ContainsKey(parameter.Name)) continue;
                MatchIndent(); OutStream.WriteLine("{1} Get{0}() {{ return {1}{{}}; }}", parameter.Name, ToTargetTypeName(parameter));
            }

            bool bHasInternalTypeOverride = HasInternalTypeOverride(parameters);

            // Generate parameter variables
            MatchIndent(-1); OutStream.WriteLine("private:");
            // member section
            if (parameters != null)
            {
                foreach (Parameter param in parameters)
                {
                    var typeInfo = SystemTypeInfo.GetParameterInfo(param);

                    if (param.IsArray)
                    {
                        MatchIndent();
                        if (typeInfo.IsVariableSize)
                            OutStream.WriteLine("DynamicArray<{0}> m_{1};", ToTargetTypeName(param), param.Name);
                        else
                            OutStream.WriteLine("ArrayView<{0}> m_{1};", ToTargetTypeName(param), param.Name);
                    }
                    else if (!typeInfo.IsString && !typeInfo.IsCSharpStruct && typeInfo.IsVariableSize)
                    {
                        MatchIndent(); OutStream.WriteLine("ArrayView<uint8_t> m_{1}Raw;", ToTargetTypeName(param), param.Name);
                        MatchIndent(); OutStream.WriteLine("mutable bool m_{1}HasParsed = false;", ToTargetTypeName(param), param.Name);
                        MatchIndent(); OutStream.WriteLine("mutable {0} m_{1};", ToTargetTypeName(param), param.Name);
                    }
                    else
                    {
                        MatchIndent(); OutStream.WriteLine("{0} m_{1}{{}};", ToTargetTypeName(param), param.Name);
                    }

                }
            }

            MatchIndent(-1); OutStream.WriteLine("public:");

            // Constructors
            MatchIndent(); OutStream.WriteLine(strClassName + "()");
            MatchIndent(1); OutStream.WriteLine("{}");
            NewLine();

            MatchIndent(); OutStream.WriteLine(strClassName + "( const MessageDataPtr &pMsg )");
            MatchIndent(1); OutStream.WriteLine(": MessageBase(pMsg)");
            MatchIndent(1); OutStream.WriteLine("{}");
            NewLine();

            MatchIndent(); OutStream.WriteLine(strClassName + "( const MessageHeader* pHeader )");
            MatchIndent(1); OutStream.WriteLine(": MessageBase(pHeader)");
            MatchIndent(1); OutStream.WriteLine("{}");
            NewLine();

            // Generate Get functions
            if (parameters != null)
            {
                foreach (Parameter param in parameters)
                {
                    var typeInfo = SystemTypeInfo.GetParameterInfo(param);

                    if (param.IsArray)
                    {
                        MatchIndent(); OutStream.WriteLine("const Array<{0}>& Get{1}() const\t{{ return m_{1}; }};", ToTargetTypeName(param), param.Name);
                    }
                    else if (IsStrType(param))
                    {
                        MatchIndent(); OutStream.WriteLine("{0} Get{1}() const\t{{ return m_{1}; }};", ToTargetTypeName(param), param.Name);
                    }
                    else if (!typeInfo.IsCSharpStruct && typeInfo.IsVariableSize)
                    {
                        MatchIndent(); OutStream.WriteLine("const Array<uint8_t>& Get{1}Raw() const\t{{ return m_{1}Raw; }};", ToTargetTypeName(param), param.Name);
                        //MatchIndent(); OutStream.WriteLine("const {0}& Get{1}() const\t{{ return m_{1}; }};", ToTargetTypeName(param.Type), param.Name);
                        MatchIndent(); OutStream.WriteLine("const {0}& Get{1}() const;", ToTargetTypeName(param), param.Name);

                    }
                    else
                    {
                        MatchIndent(); OutStream.WriteLine("const {0}& Get{1}() const\t{{ return m_{1}; }};", ToTargetTypeName(param), param.Name);
                    }
                }
            }

            NewLine();
            // message trace function
            MatchIndent(); OutStream.WriteLine("static Result TraceOut(const char* prefix, const MessageHeader* pHeader);");
            NewLine();

            // Parse function
            MatchIndent(); OutStream.WriteLine("virtual Result ParseMessage(const MessageHeader* pHeader);");
            if(AppConfig.GetValue("VariableMapParser", false))
            {
                MatchIndent(); OutStream.WriteLine("static Result ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder );");
            }

            MatchIndent(); OutStream.WriteLine("static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMsgBase);");
            NewLine();

            MatchIndent(); OutStream.WriteLine("static size_t CalculateMessageSize( {0} );", ParamInString(parameters, bUseOriginalType: true));
            if (bHasInternalTypeOverride)
            {
                MatchIndent(); OutStream.WriteLine("static size_t CalculateMessageSize( {0} );", ParamInString(parameters, bUseOriginalType: false));
            }

            // Build function
            MatchIndent(); OutStream.WriteLine("static Result Create( {0} );", BuilderParamString(parameters));
            if (bHasInternalTypeOverride)
            {
                MatchIndent(); OutStream.WriteLine("static Result Create( {0} );", BuilderParamString(parameters, bUseOriginalType:true));
            }
            NewLine();

            CloseSection();
        }

        // build parser class header
        void BuildMessageParserClassH()
        {
            Parameter[] newparams;

            foreach (MessageBase baseMsg in Group.Items)
            {
                if (baseMsg is ProtocolsProtocolGroupCommand)
                {
                    MatchIndent(); OutStream.WriteLine("// Cmd: " + baseMsg.Desc);
                    ProtocolsProtocolGroupCommand msg = baseMsg as ProtocolsProtocolGroupCommand;

                    newparams = MakeParameters(MsgType.Cmd, msg.Cmd);
                    BuildParserClass(msg, MsgType.Cmd, "Cmd", newparams);
                    NewLine();

                    newparams = MakeParameters(MsgType.Res, msg.Res);
                    BuildParserClass(msg, MsgType.Res, "Res", newparams);
                    NewLine();
                }

                if (baseMsg is ProtocolsProtocolGroupC2SEvent)
                {
                    MatchIndent(); OutStream.WriteLine("// C2S: " + baseMsg.Desc);
                    ProtocolsProtocolGroupC2SEvent msg = baseMsg as ProtocolsProtocolGroupC2SEvent;

                    newparams = MakeParameters(MsgType.Evt, msg.Params);
                    BuildParserClass(msg, MsgType.Evt, "C2SEvt", newparams);
                    NewLine();
                }

                if (baseMsg is ProtocolsProtocolGroupS2CEvent)
                {
                    MatchIndent(); OutStream.WriteLine("// S2C: " + baseMsg.Desc);
                    ProtocolsProtocolGroupS2CEvent msg = baseMsg as ProtocolsProtocolGroupS2CEvent;

                    newparams = MakeParameters(MsgType.Evt, msg.Params);
                    BuildParserClass(msg, MsgType.Evt, "S2CEvt", newparams);
                    NewLine();
                }
            }
        }


        void BuildGetFunctionImpl(string Name, string typeName, Parameter[] parameters)
        {
            string strClassName = MsgClassName(Name, typeName);

            foreach(var param in parameters)
            {
                if (IsStrType(param) || param.IsArray)
                    continue;

                if (IsVariableSizeType(param))
                {
                    OpenSection(string.Format("const {0}&", ToTargetTypeName(param)), string.Format("{0}::Get{1}() const", strClassName, param.Name), bUseTerminator: false);
                    OpenSection("if", string.Format("(!m_{0}HasParsed)", param.Name), bUseTerminator: false);
                    MatchIndent(); OutStream.WriteLine("m_{0}HasParsed = true;", param.Name);
                    MatchIndent(); OutStream.WriteLine("InputMemoryStream {0}_ReadStream(m_{0}Raw);", param.Name);
                    MatchIndent(); OutStream.WriteLine("*{0}_ReadStream.ToInputStream() >> m_{0};", param.Name);
                    CloseSection();
                    MatchIndent(); OutStream.WriteLine("return m_{0};", param.Name);
                    CloseSection();
                }
            }
        }

        // Build parser class implementation
        void BuildParserImpl(string Name, string typeName, Parameter[] parameters)
        {
            string strClassName = MsgClassName(Name, typeName);
            OpenSection("Result", strClassName + "::ParseMessage(const MessageHeader* pHeader)");

            DefaultHRESULT(); NewLine();

            bool bHasParameter = parameters != null && parameters.Length > 0;

            NewLine();
            MatchIndent(); OutStream.WriteLine("protocolCheckPtr(pHeader);");
            NewLine();

            if (bHasParameter)
            {
                // array len types
                MatchIndent(); OutStream.WriteLine("ArrayView<const uint8_t> bufferView(pHeader->GetPayload());");
                MatchIndent(); OutStream.WriteLine("InputMemoryStream inputStream(bufferView);");
                MatchIndent(); OutStream.WriteLine("auto* input = inputStream.ToInputStream();");
                MatchIndent(); OutStream.WriteLine("uint16_t ArrayLen = 0;(void)(ArrayLen);");
            }
            NewLine();

            if (parameters == null)
            {
                // nothing to process
                MatchIndent(); ReturnHR();
            }
            else
            {
                foreach (Parameter param in parameters)
                {
                    if(param.IsArray)
                    {
                        if (IsVariableSizeType(param))
                        {
                            if (IsStrType(param)) // TODO: add other linkable types
                            {
                                MatchIndent(); OutStream.WriteLine("protocolCheck(input->ReadArrayLink(m_{0}));", param.Name);
                            }
                            else
                            {
                                MatchIndent(); OutStream.WriteLine("protocolCheck(input->Read(m_{0}));", param.Name);
                            }
                        }
                        else
                        {
                            MatchIndent(); OutStream.WriteLine("protocolCheck(input->Read(ArrayLen));");
                            MatchIndent(); OutStream.WriteLine("{1}* {0}Ptr = nullptr;", param.Name, ToTargetTypeName(param));
                            MatchIndent(); OutStream.WriteLine("protocolCheck(input->ReadLink({0}Ptr, ArrayLen));", param.Name);
                            MatchIndent(); OutStream.WriteLine("m_{0}.SetLinkedBuffer(ArrayLen, {0}Ptr);", param.Name);
                        }
                    }
                    else if (IsStrType(param))
                    {
                        MatchIndent(); OutStream.WriteLine("protocolCheck(input->Read(ArrayLen));");
                        MatchIndent(); OutStream.WriteLine("protocolCheck(input->ReadLink(m_{0}, ArrayLen));", param.Name);
                    }
                    else if (IsVariableSizeType(param))
                    {
                        MatchIndent(); OutStream.WriteLine("protocolCheck(input->Read(ArrayLen));");
                        MatchIndent(); OutStream.WriteLine("uint8_t* {0}Ptr = nullptr;", param.Name, ToTargetTypeName(param));
                        MatchIndent(); OutStream.WriteLine("protocolCheck(input->ReadLink({0}Ptr, ArrayLen));", param.Name);
                        MatchIndent(); OutStream.WriteLine("m_{0}Raw.SetLinkedBuffer(ArrayLen, {0}Ptr);", param.Name);
                    }
                    else
                    {
                        MatchIndent(); OutStream.WriteLine("protocolCheck(*input >> m_{0});", param.Name);
                    }
                }
            }

            NewLine();

            ReturnHR(); NewLine();

            CloseSection();
        }

        // Build parser class implementation
        void BuildParserToVariableBuilderImpl(string Name, string typeName, Parameter[] parameters)
        {
            if (!AppConfig.GetValue("VariableMapParser", false))
            {
                return;
            }

            string strClassName = MsgClassName(Name, typeName);
            OpenSection("Result", strClassName + "::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )");

            DefaultHRESULT(); NewLine();

            bool bHasParameter = parameters != null && parameters.Length > 0;

            NewLine();
            MatchIndent(); OutStream.WriteLine("{0} parser;", strClassName);
            MatchIndent(); OutStream.WriteLine("protocolCheck(parser.ParseMessage(pHeader));");
            NewLine();

            if (parameters != null)
            {
                foreach (Parameter param in parameters)
                {
                    //var csharpType = SystemTypeInfo.ToCSharpType(param);
                    var typeInfo = SystemTypeInfo.GetParameterInfo(param);

                    if (typeInfo.UseGenericVariableBuilderInterface)
                    {
                        if (param.IsArray)
                        {
                            MatchIndent(); OutStream.WriteLine("variableBuilder.SetVariableArray(\"{0}\", \"{1}\", parser.Get{0}());", param.Name, param.TypeName);
                        }
                        else
                        {
                            MatchIndent(); OutStream.WriteLine("variableBuilder.SetVariable(\"{0}\", \"{1}\", parser.Get{0}());", param.Name, param.TypeName);
                        }
                    }
                    else if (param.IsArray || typeInfo.IsString)
                    {
                        MatchIndent(); OutStream.WriteLine("variableBuilder.SetVariable(\"{0}\", parser.Get{0}());", param.Name);
                    }
                    else if(typeInfo.IsEnum)
                    {
                        MatchIndent(); OutStream.WriteLine("variableBuilder.SetVariable(\"{0}\", (int)parser.Get{0}());", param.Name);
                    }
                    else if(!typeInfo.IsCSharpStruct && typeInfo.IsVariableSize)
                    {
                        MatchIndent(); OutStream.WriteLine("variableBuilder.SetVariableArray(\"{0}\", \"{1}\", parser.Get{0}Raw());", param.Name, param.TypeName);
                    }
                    else
                    {
                        MatchIndent();
                        var isStruct = SystemTypeInfo.IsStruct(param);
                        if (isStruct)
                            OutStream.WriteLine("variableBuilder.SetVariable(\"{0}\", \"{1}\", parser.Get{0}());", param.Name, param.TypeName);
                        else
                            OutStream.WriteLine("variableBuilder.SetVariable(\"{0}\", parser.Get{0}());", param.Name);
                    }
                }
            }

            NewLine();

            ReturnHR(); NewLine();

            CloseSection();
        }

        // Build parser class implementation
        void BuildParserToMessageBaseImpl(string Name, string typeName, Parameter[] parameters)
        {
            string strClassName = MsgClassName(Name, typeName);
            OpenSection("Result", strClassName + "::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )");

            DefaultHRESULT();

            bool bHasParameter = parameters != null && parameters.Length > 0;

            NewLine();
            MatchIndent(); OutStream.WriteLine("protocolCheckMem(pMessageBase = new(memHeap) {0}(pHeader));", strClassName);
            MatchIndent(); OutStream.WriteLine("protocolCheck(pMessageBase->ParseMsg());", strClassName);
            NewLine();

            ReturnHR(); NewLine();

            CloseSection();
        }


        // Build parser class implementation
        void BuildOverrideRouteContextImpl(string Name, string typeName, Parameter[] parameters)
        {
            //if (!Group.GenParameterRouteContext)
            //    return;

            //string strClassName = MsgClassName(Name, typeName);
            //OpenSection("Result", strClassName + "::OverrideRouteContextDestination( EntityUID to )");

            //DefaultHRESULT(); NewLine();

            //MatchIndent(); OutStream.WriteLine("MessageData* pIMsg = GetMessage();");
            //MatchIndent(); OutStream.WriteLine("RouteContext routeContext;");
            //NewLine();
            //MatchIndent(); OutStream.WriteLine("protocolCheckPtr(pIMsg);");
            //NewLine();

            //// array len types
            //MatchIndent(); OutStream.WriteLine("size_t MsgDataSize = (int)((size_t)pIMsg->GetMessageSize() - sizeof(MessageHeader));");

            //MatchIndent(); OutStream.WriteLine("ArrayView<const uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());");
            //MatchIndent(); OutStream.WriteLine("InputMemoryStream inputStream(bufferView);");
            //MatchIndent(); OutStream.WriteLine("auto* input = inputStream.ToInputStream();");
            //MatchIndent(); OutStream.WriteLine("uint16_t ArrayLen = 0;(void)(ArrayLen);");
            //MatchIndent(); OutStream.WriteLine("const uint8_t* pCur = nullptr;(void)(pCur);");
            //NewLine();

            //if (parameters == null)
            //{
            //    // nothing to process
            //}
            //else
            //{
            //    // Just follow the same process to parsing
            //    foreach (Parameter param in parameters)
            //    {
            //        switch (param.TypeName)
            //        {
            //            case "String":
            //                MatchIndent(); OutStream.WriteLine("protocolCheck(input->Read(ArrayLen));");
            //                MatchIndent(); OutStream.WriteLine("protocolCheck(input->Skip(ArrayLen * sizeof(char));");
            //                break;
            //            case "RouteContext":
            //                break;
            //            default:
            //                if (param.IsArray)
            //                {
            //                    MatchIndent(); OutStream.WriteLine("protocolCheck(input->Read(ArrayLen));");
            //                    MatchIndent(); OutStream.WriteLine("protocolCheck(input->Skip(ArrayLen * sizeof({0}));", ToTargetTypeName(param));
            //                }
            //                else
            //                {
            //                    MatchIndent(); OutStream.WriteLine("protocolCheck(input->Skip(sizeof({0}));", ToTargetTypeName(param));
            //                }
            //                break;
            //        }

            //        // All other process is same
            //        if (param.TypeName == "RouteContext")
            //        {
            //            MatchIndent(); OutStream.WriteLine("pCur = input->GetBufferPtr() + input->GetPosition();");
            //            MatchIndent(); OutStream.WriteLine("Assert(input->GetRemainSize() >= sizeof(RouteContext));");
            //            MatchIndent(); OutStream.WriteLine("memcpy( &routeContext, pCur, sizeof(RouteContext) );");
            //            MatchIndent(); OutStream.WriteLine("routeContext.Components.To = to;");
            //            MatchIndent(); OutStream.WriteLine("memcpy( pCur, &routeContext, sizeof(RouteContext) );");
            //            break;
            //        }
            //    }
            //}

            //NewLine();
            //ReturnHR();
            //NewLine();

            //CloseSection();
        }


        // Build override route hop count class implementation
        void BuildOverrideRouteHopCountImpl(string Name, string typeName, Parameter[] parameters)
        {
            //if (!Group.GenParameterRouteHopCount)
            //    return;

            //string strClassName = MsgClassName(Name, typeName);
            //OpenSection("Result", strClassName + "::OverrideRouteInformation( EntityUID to, unsigned hopCount )");

            //DefaultHRESULT(); NewLine();

            //MatchIndent(); OutStream.WriteLine("MessageData* pIMsg = GetMessage();");
            //MatchIndent(); OutStream.WriteLine("RouteContext routeContext;");
            //NewLine();
            //MatchIndent(); OutStream.WriteLine("protocolCheckPtr(pIMsg);");
            //NewLine();

            //// array len types
            //if (Group.IsMobile)
            //{
            //    MatchIndent(); OutStream.WriteLine("size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - Message::MobileHeaderSize);");
            //}
            //else
            //{
            //    MatchIndent(); OutStream.WriteLine("size_t MsgDataSize = ((size_t)pIMsg->GetMessageSize() - sizeof(MessageHeader));");
            //}

            //MatchIndent(); OutStream.WriteLine("ArrayView<const uint8_t> bufferView(MsgDataSize, pIMsg->GetMessageData());");
            //MatchIndent(); OutStream.WriteLine("InputMemoryStream inputStream(bufferView);");
            //MatchIndent(); OutStream.WriteLine("auto* input = inputStream.ToInputStream();");
            //MatchIndent(); OutStream.WriteLine("uint16_t ArrayLen = 0;(void)(ArrayLen);");
            //MatchIndent(); OutStream.WriteLine("const uint8_t* pCur = nullptr;(void)(pCur);");
            //NewLine();

            //// Skip until we meet route context
            //if (parameters != null)
            //{
            //    foreach (Parameter param in parameters)
            //    {
            //        switch (param.Type)
            //        {
            //            case ParameterType.String:
            //                MatchIndent(); OutStream.WriteLine("protocolCheck(input->Read(ArrayLen));");
            //                MatchIndent(); OutStream.WriteLine("protocolCheck(input->Skip(ArrayLen * sizeof(char)));");
            //                break;
            //            default:
            //                if (param.Type == ParameterType.RouteContext && param.Name == ParamRouteContext.Name)
            //                {
            //                    MatchIndent(); OutStream.WriteLine("pCur = input->GetBufferPtr() + input->GetPosition();");
            //                    MatchIndent(); OutStream.WriteLine("Assert(input->GetRemainSize() >= sizeof(RouteContext));");
            //                    MatchIndent(); OutStream.WriteLine("memcpy( &routeContext, pCur, sizeof(RouteContext) );");
            //                    MatchIndent(); OutStream.WriteLine("routeContext.Components.To = to;");
            //                    MatchIndent(); OutStream.WriteLine("memcpy( pCur, &routeContext, sizeof(RouteContext) );");
            //                }
            //                else if (param.Name == ParamRouteHopCount.Name)
            //                {
            //                    MatchIndent(); OutStream.WriteLine("Assert(input->GetRemainSize() >= sizeof({0}));", ToTargetTypeName(ParamRouteHopCount.Type));
            //                    MatchIndent(); OutStream.WriteLine("pCur = input->GetBufferPtr() + input->GetPosition();");
            //                    MatchIndent(); OutStream.WriteLine("*({0}*)pCur = hopCount;", ToTargetTypeName(ParamRouteHopCount.Type));
            //                }

            //                if (param.IsArray)
            //                {
            //                    MatchIndent(); OutStream.WriteLine("protocolCheck(input->Read(ArrayLen));");
            //                    MatchIndent(); OutStream.WriteLine("protocolCheck(input->Skip(ArrayLen * sizeof({0})));", ToTargetTypeName(param.Type));
            //                }
            //                else
            //                {
            //                    MatchIndent(); OutStream.WriteLine("protocolCheck(input->Skip(sizeof({0})));", ToTargetTypeName(param.Type));
            //                }
            //                break;
            //        }

            //        // All other process is same
            //        if (param.Name == ParamRouteHopCount.Name)
            //        {
            //            break;
            //        }
            //    }
            //}

            //NewLine();

            //ReturnHR(); NewLine();

            //CloseSection();
        }

        void CalculateMessageSizePreamble(Parameter[] parameters)
        {
            if (parameters == null)
                return;

            foreach (Parameter param in parameters)
            {
                if (IsStrType(param)) // string type
                {
                }
                else if (param.IsArray) // array
                {
                }
                else if (IsVariableSizeType(param))
                {
                    MatchIndent(); OutStream.WriteLine("{1} serializedSizeOf{0} = static_cast<{1}>(SerializedSizeOf({0})); ", InParamName(param.Name), ArrayLenType);
                }
            }
        }

        void BuildCalculateMessageSizeImpl(string Name, string typeName, Parameter[] parameters, bool bUseOriginalType = false)
        {
            bool bHasInternalTypeOverride = HasInternalTypeOverride(parameters);
            if (!bUseOriginalType && !bHasInternalTypeOverride)
                return;

            string strClassName = MsgClassName(Name, typeName);
            //bool bHasParameters = parameters != null && parameters.Length > 0;
            OpenSection("size_t", strClassName + string.Format("::CalculateMessageSize( {0} )", ParamInString(parameters, bUseOriginalType: bUseOriginalType)));

            CalculateMessageSizePreamble(parameters);

            string strSizeVarName = "__uiMessageSize";
            string strMessageHeaderSize = "Message::HeaderSize";
            MatchIndent(); OutStream.WriteLine(string.Format("unsigned {0} = (unsigned)({1} ", strSizeVarName, strMessageHeaderSize));
            if (parameters != null)
            {
                foreach (Parameter param in parameters)
                {
                    if (!IsStrType(param) && !param.IsArray && IsVariableSizeType(param))
                    {
                        // Original type will use binary conversion, so has extra array length parameter
                        if (bUseOriginalType)
                        {
                            MatchIndent(1); OutStream.WriteLine("+ sizeof({0})", ArrayLenType);
                        }
                        MatchIndent(1); OutStream.WriteLine("+ serializedSizeOf{0}", InParamName(param.Name));
                    }
                    else
                    {
                        MatchIndent(1); OutStream.WriteLine("+ SerializedSizeOf({0})", InParamName(param.Name));
                    }
                }
            }

            MatchIndent(); OutStream.WriteLine(");");
            NewLine();

            MatchIndent(); OutStream.WriteLine($"return {strSizeVarName};");

            CloseSection();
        }

        // Build parser class implementation
        void BuildCreateImpl(string Name, string typeName, Parameter[] parameters, bool bUseOriginalType = false)
        {
            bool bHasInternalTypeOverride = HasInternalTypeOverride(parameters);
            if (!bUseOriginalType && !bHasInternalTypeOverride)
                return;

            string strClassName = MsgClassName(Name, typeName);
            bool bHasParameters = parameters != null && parameters.Length > 0;
            OpenSection("Result", strClassName + string.Format("::Create( {0} )", BuilderParamString(parameters, bUseOriginalType: bUseOriginalType)));

            MatchIndent(); OutStream.WriteLine("Result hr;");

            //OpenSection("ScopeContext", "hr([&](Result hr) -> MessageData*");
            //MatchIndent(); OutStream.WriteLine("if(!hr && pNewMsg != nullptr)");
            //    OpenSection();
            //    MatchIndent(); OutStream.WriteLine("IHeap::Delete(pNewMsg);");
            //MatchIndent(); OutStream.WriteLine("return nullptr;");
            //CloseSection();
            //MatchIndent(); OutStream.WriteLine("return pNewMsg;");
            //CloseSection("});");

            NewLine();

            if (bUseOriginalType)
            {
                CalculateMessageSizePreamble(parameters);

                string strSizeVarName = "__uiMessageSize";
                string strMessageHeaderSize = "Message::HeaderSize";
                MatchIndent(); OutStream.WriteLine(string.Format("unsigned {0} = (unsigned)({1} ", strSizeVarName, strMessageHeaderSize));
                if (parameters != null)
                {
                    foreach (Parameter param in parameters)
                    {
                        if (!IsStrType(param) && !param.IsArray && IsVariableSizeType(param))
                        {
                            // Original type will use binary conversion, so has extra array length parameter
                            if (bUseOriginalType)
                            {
                                MatchIndent(1); OutStream.WriteLine("+ sizeof({0})", ArrayLenType);
                            }
                            MatchIndent(1); OutStream.WriteLine("+ serializedSizeOf{0}", InParamName(param.Name));
                        }
                        else
                        {
                            MatchIndent(1); OutStream.WriteLine("+ SerializedSizeOf({0})", InParamName(param.Name));
                        }
                    }
                }

                MatchIndent(); OutStream.WriteLine(");");
                NewLine();
            }
            else
            {
                MatchIndent(); OutStream.WriteLine($"uint __uiMessageSize = (uint)CalculateMessageSize({ParamArgument(parameters)});");
                NewLine();
            }

            MatchIndent(); OutStream.WriteLine($"messageBuffer->MessageId = {strClassName}::MID;");
            MatchIndent(); OutStream.WriteLine("if (messageBuffer->Length < __uiMessageSize)");
            MatchIndent(1); OutStream.WriteLine("return ResultCode::UNEXPECTED;");
            MatchIndent(); OutStream.WriteLine("else");
            MatchIndent(1); OutStream.WriteLine("messageBuffer->Length = __uiMessageSize;");
            NewLine();

            if (bHasParameters)
            {
                MatchIndent(); OutStream.WriteLine("ArrayView<uint8_t> payloadView(size_t(messageBuffer->Length - sizeof(MessageHeader)), 0, reinterpret_cast<uint8_t*>(messageBuffer->GetDataPtr()));");
                MatchIndent(); OutStream.WriteLine("OutputMemoryStream outputStream(payloadView);");
                MatchIndent(); OutStream.WriteLine("IOutputStream* output = outputStream.ToOutputStream();");
                NewLine();

                foreach (Parameter param in parameters)
                {
                    // TODO: maybe avoid multiple strlen?
                    if (IsStrType(param)) // string type
                    {
                        MatchIndent(); OutStream.WriteLine("protocolCheck(*output << {0});", InParamName(param.Name));
                    }
                    //else if (param.IsArray) // array
                    //{
                    //    MatchIndent(); OutStream.WriteLine("Protocol::PackParamCopy( pMsgData, &numberOf{0}, sizeof({1})); ", InParamName(param.Name), ArrayLenType);
                    //    MatchIndent(); OutStream.WriteLine("Protocol::PackParamCopy( pMsgData, {0}.data(), (INT)(sizeof({1})*{0}.size())); ", InParamName(param.Name), ToTargetTypeName(param.Type));
                    //}
                    else if (!param.IsArray && IsVariableSizeType(param))
                    {
                        if (bUseOriginalType)
                        {
                            MatchIndent(); OutStream.WriteLine("protocolCheck(output->Write(serializedSizeOf{0}));", InParamName(param.Name));
                        }
                        MatchIndent(); OutStream.WriteLine("protocolCheck(*output << {0});", InParamName(param.Name));
                    }
                    else
                    {
                        MatchIndent(); OutStream.WriteLine("protocolCheck(*output << {0});", InParamName(param.Name));
                    }
                }
            }
            NewLine();

            MatchIndent(); OutStream.WriteLine("return hr;");

            CloseSection();
        }


        void BuildMessageParserClassCPP()
        {
            // Packer interface
            Parameter[] newparams;
            m_MessageCodeIndex = 0;
            foreach (MessageBase baseMsg in Group.Items)
            {
                if (baseMsg is ProtocolsProtocolGroupCommand)
                {
                    MatchIndent(); OutStream.WriteLine("// Cmd: " + baseMsg.Desc);
                    ProtocolsProtocolGroupCommand msg = baseMsg as ProtocolsProtocolGroupCommand;

                    newparams = MakeParameters(MsgType.Cmd, msg.Cmd);
                    BuildGetFunctionImpl(msg.Name, "Cmd", newparams);
                    BuildParserImpl(msg.Name, "Cmd", newparams); NewLine();
                    BuildParserToVariableBuilderImpl(msg.Name, "Cmd", newparams); NewLine();
                    BuildParserToMessageBaseImpl(msg.Name, "Cmd", newparams); NewLine();
                    BuildCalculateMessageSizeImpl(msg.Name, "Cmd", newparams, bUseOriginalType: false); NewLine();
                    BuildCalculateMessageSizeImpl(msg.Name, "Cmd", newparams, bUseOriginalType: true); NewLine();
                    BuildCreateImpl(msg.Name, "Cmd", newparams); NewLine();
                    BuildCreateImpl(msg.Name, "Cmd", newparams, bUseOriginalType:true); NewLine();
                    //BuildOverrideRouteContextImpl(msg.Name, "Cmd", newparams); NewLine();
                    //BuildOverrideRouteHopCountImpl(msg.Name, "Cmd", newparams); NewLine();
                    BuildMessageTrace(msg.Name, "Cmd", msg.Trace.ToString(), newparams);

                    newparams = MakeParameters(MsgType.Res, msg.Res);
                    BuildGetFunctionImpl(msg.Name, "Res", newparams);
                    BuildParserImpl(msg.Name, "Res", newparams); NewLine();
                    BuildParserToVariableBuilderImpl(msg.Name, "Res", newparams); NewLine();
                    BuildParserToMessageBaseImpl(msg.Name, "Res", newparams); NewLine();
                    BuildCalculateMessageSizeImpl(msg.Name, "Res", newparams, bUseOriginalType: false); NewLine();
                    BuildCalculateMessageSizeImpl(msg.Name, "Res", newparams, bUseOriginalType: true); NewLine();

                    BuildCreateImpl(msg.Name, "Res", newparams); NewLine();
                    BuildCreateImpl(msg.Name, "Res", newparams, bUseOriginalType: true); NewLine();
                    //BuildOverrideRouteContextImpl(msg.Name, "Res", newparams); NewLine();
                    //BuildOverrideRouteHopCountImpl(msg.Name, "Res", newparams); NewLine();
                    BuildMessageTrace(msg.Name, "Res", msg.Trace.ToString(), newparams);
                }

                if (baseMsg is ProtocolsProtocolGroupC2SEvent)
                {
                    MatchIndent(); OutStream.WriteLine("// C2S: " + baseMsg.Desc);
                    ProtocolsProtocolGroupC2SEvent msg = baseMsg as ProtocolsProtocolGroupC2SEvent;

                    newparams = MakeParameters(MsgType.Evt, msg.Params);
                    BuildGetFunctionImpl(msg.Name, "C2SEvt", newparams);
                    BuildParserImpl(msg.Name, "C2SEvt", newparams); NewLine();
                    BuildParserToVariableBuilderImpl(msg.Name, "C2SEvt", newparams); NewLine();
                    BuildParserToMessageBaseImpl(msg.Name, "C2SEvt", newparams); NewLine();
                    BuildCalculateMessageSizeImpl(msg.Name, "C2SEvt", newparams, bUseOriginalType: false); NewLine();
                    BuildCalculateMessageSizeImpl(msg.Name, "C2SEvt", newparams, bUseOriginalType: true); NewLine();
                    BuildCreateImpl(msg.Name, "C2SEvt", newparams); NewLine();
                    BuildCreateImpl(msg.Name, "C2SEvt", newparams, bUseOriginalType: true); NewLine();
                    //BuildOverrideRouteContextImpl(msg.Name, "C2SEvt", newparams); NewLine();
                    //BuildOverrideRouteHopCountImpl(msg.Name, "C2SEvt", newparams); NewLine();
                    BuildMessageTrace(msg.Name, "C2SEvt", msg.Trace.ToString(), newparams);
                }

                if (baseMsg is ProtocolsProtocolGroupS2CEvent)
                {
                    MatchIndent(); OutStream.WriteLine("// S2C: " + baseMsg.Desc);
                    ProtocolsProtocolGroupS2CEvent msg = baseMsg as ProtocolsProtocolGroupS2CEvent;

                    newparams = MakeParameters(MsgType.Evt, msg.Params);
                    BuildGetFunctionImpl(msg.Name, "S2CEvt", newparams);
                    BuildParserImpl(msg.Name, "S2CEvt", newparams); NewLine();
                    BuildParserToVariableBuilderImpl(msg.Name, "S2CEvt", newparams); NewLine();
                    BuildParserToMessageBaseImpl(msg.Name, "S2CEvt", newparams); NewLine();
                    BuildCalculateMessageSizeImpl(msg.Name, "S2CEvt", newparams, bUseOriginalType: false); NewLine();
                    BuildCalculateMessageSizeImpl(msg.Name, "S2CEvt", newparams, bUseOriginalType: true); NewLine();
                    BuildCreateImpl(msg.Name, "S2CEvt", newparams); NewLine();
                    BuildCreateImpl(msg.Name, "S2CEvt", newparams, bUseOriginalType: true); NewLine();
                    //BuildOverrideRouteContextImpl(msg.Name, "S2CEvt", newparams); NewLine();
                    //BuildOverrideRouteHopCountImpl(msg.Name, "S2CEvt", newparams); NewLine();
                    BuildMessageTrace(msg.Name, "S2CEvt", msg.Trace.ToString(), newparams);
                }
                m_MessageCodeIndex++;
            }
        }


        void BuildH()
        {
            // Build Parser class
            OpenOutFile(OutputClassHeaderName());

            BuildHPrefix();

            BuildMessageParserClassH();
            NewLine(2);

            NewLine(2);
            CloseOutFile();
        }

        void BuildCPP()
        {
            // write parser class cpp
            OpenOutFile(OutputClassCPPName());

            BuildCPPPrefix(OutputClassHeaderName());

            BuildMessageParserClassCPP();
            NewLine(2);


            CloseOutFile();
        }

        // Source timestamp file for make file
        void BuildTimeStamp()
        {
            // write parser class cpp
            OpenOutFile("Protocol"+Group.Name+".h");

            OutStream.WriteLine("Build:"+ DateTime.Now);

            CloseOutFile();
        }

        public override void Build()
        {
            BuildH();
            BuildCPP();
            BuildTimeStamp();
        }

    }
}
