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
using ProtocolXml;
using SF;
using SF.Tool;

namespace ProtocolCompiler
{
    class MessageClassBuilder : Builder
    {
        // Msg type string
        static string[] MsgTypeString = new string[] {
                    "MSGTYPE_NETCONTROL",
                    "MSGTYPE_COMMAND",
                    "MSGTYPE_RESULT",
                    "MSGTYPE_EVENT",
                };

        // Message guaranteed level string
        static string[] MsgReliablityString = new string[]{
                "MSGTYPE_NONE",
                "MSGTYPE_RELIABLE",
            };

        // Message guaranteed level string
        static string[] MsgMobilityString = new string[]{
                "MSGTYPE_NONE",
                "MSGTYPE_MOBILE",
            };


        // Message code generation serial
        int m_MessageCodeIndex;

        string LogFunctionPrefix;

        // constructor
        public MessageClassBuilder(string strBasePath)
            : base(strBasePath + "Message")
        {
            GenParameterRouteHopCount = true;
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
            OutStream.WriteLine("// CopyRight (c) 2016 Kyungkun Ko");
            OutStream.WriteLine("// ");
            OutStream.WriteLine("// Author : Generated");
            OutStream.WriteLine("// ");
            OutStream.WriteLine("// Description : {0} Message parser definitions", Group.Name);
            OutStream.WriteLine("// ");
            OutStream.WriteLine("////////////////////////////////////////////////////////////////////////////////");
            OutStream.WriteLine("");
            OutStream.WriteLine("#pragma once");
            OutStream.WriteLine("");
            OutStream.WriteLine("#include \"Protocol/SFProtocol.h\"");
            OutStream.WriteLine("#include \"Net/SFMessage.h\"");
            OutStream.WriteLine("#include \"Types/SFEngineTypedefs.h\"");
            if (AppConfig.GetValue("VariableMapParser", false))
            {
                OutStream.WriteLine("#include \"Variable/SFVariableMapBuilder.h\"");
            }
            if (Group.IsServer)
                OutStream.WriteLine("#include \"Protocol/SvrProtocol.h\"");
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
            OutStream.WriteLine("// CopyRight (c) 2016 Kyungkun Ko");
            OutStream.WriteLine("// ");
            OutStream.WriteLine("// Author : Generated");
            OutStream.WriteLine("// ");
            OutStream.WriteLine("// Description : {0} Message parser implementations", Group.Name);
            OutStream.WriteLine("// ");
            OutStream.WriteLine("////////////////////////////////////////////////////////////////////////////////");
            OutStream.WriteLine("");
            OutStream.WriteLine("");
            OutStream.WriteLine("#include \"{0}\"", PreCompiledHeader );
            OutStream.WriteLine("#include \"Protocol/SFProtocol.h\"");
            OutStream.WriteLine("#include \"String/SFToString.h\"");
            OutStream.WriteLine("#include \"Net/SFNetToString.h\"");
            OutStream.WriteLine("#include \"Container/SFArray.h\"");
            OutStream.WriteLine("#include \"Protocol/SFProtocolHelper.h\"");
            OutStream.WriteLine("#include \"Protocol/Message/{0}\"", HeaderName);
            if (Group.IsServer)
                OutStream.WriteLine("#include \"Protocol/SvrProtocol.h\"");

            NewLine(3);

            // namespace definition
            OpenSection("namespace", PrjPrefix);
            OpenSection("namespace", BuilderNamespace);
            OpenSection("namespace", Group.Name);
        }


        void BuildMessageTrace(string Name, string typeName, string traceChannel, Parameter[] parameters)
        {
            string strClassName = MsgClassName(Name, typeName);
            OpenSection("Result", strClassName + "::TraceOut(const char* prefix, MessageDataPtr& pMsg)");

            string strTrace = string.Format("{0}, \"{1}:{{0}}:{{1}} ", traceChannel, Name, typeName);
            string strTraceMember = "prefix, pMsg->GetMessageHeader()->Length";
            int ParamCount = 2;

            MatchIndent(); OutStream.WriteLine("{0} parser;", strClassName);
            MatchIndent(); OutStream.WriteLine("parser.ParseMessage(*pMsg);");

            if (parameters != null)
            {
                foreach (Parameter param in parameters)
                {
                    var csharpType = SystemTypeInfo.ToCSharpType(param.Type);

                    switch (param.Type)
                    {
                        case ParameterType.String:
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
                            else if (param.Type == ParameterType.Result)
                            {
                                strTrace += string.Format(", {0}:{{{1}:X8}}", param.Name, ParamCount++);
                                strTraceMember += string.Format(", parser.Get{0}()", param.Name);
                            }
                            else if(csharpType.IsEnum)
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

        // build pointer initialize block
        void BuildParserClassInit( string strDelimiter, Parameter[] parameters)
        {
            if (parameters != null)
            {
                foreach (Parameter param in parameters)
                {
                    switch (param.Type)
                    {
                        case ParameterType.String:
                            MatchIndent(); OutStream.WriteLine(
                                string.Format("{0}m_{1}(nullptr)", strDelimiter, param.Name));
                            strDelimiter = ",";
                            break;
                        default:
                            //if (param.IsArray)
                            //{
                            //    MatchIndent(); OutStream.WriteLine(
                            //        string.Format("{0}m_{1}(0)", strDelimiter, ArrayLenName(param.Name)));
                            //    strDelimiter = ",";
                            //    MatchIndent(); OutStream.WriteLine(
                            //        string.Format("{0}m_{1}(NULL)", strDelimiter, param.Name));
                                
                            //}
                            break;
                    }
                }
            }
        }

        // Builder parameter string
        string BuilderParamString(Parameter[] parameter)
        {
            string param = ParamInString(parameter);
            if (param.Length > 0)
                return "IHeap& memHeap, " + param;
            else
                return "IHeap& memHeap";
        }

        // Make message ID macro string 
        string MakeMsgIDStr(MsgType type, bool reliablity, bool mobility, string MsgName)
        {
            string strRes = string.Format("MessageID({0}, {1}, {2}, PROTOCOLID_{3}, {4})",
                MsgTypeString[(int)type],
                MsgReliablityString[reliablity ? 1 : 0],
                MsgMobilityString[mobility ? 1 : 0],
                Group.Name.ToUpper(),
                m_MessageCodeIndex);
            return strRes;
        }

        static Parameter[] GenerateParameterTypeInfoList = new Parameter[]
        {
            new Parameter() { Name = "PlayerID", Type = ParameterType.uint64 },
            new Parameter() { Name = "TransactionID", Type = ParameterType.TransactionID },
            new Parameter() { Name = "RouteContext", Type = ParameterType.RouteContext },
            new Parameter() { Name = "RouteHopCount", Type = ParameterType.uint32 },
            new Parameter() { Name = "Sender", Type = ParameterType.uint64 },
        };

        // build parser class
        void BuildParserClass(ProtocolXml.MessageBase msg, MsgType msgType, string typeName, Parameter[] parameters)
        {
            string Name = msg.Name;
            string strClassName = MsgClassName(Name, typeName);
            OpenSection("class", strClassName + " : public MessageBase");
            MatchIndent(-1); OutStream.WriteLine("public:");

            MatchIndent(); OutStream.WriteLine("static const MessageID MID;");

            // Generate parameter Indicators for Template implementations
            MatchIndent(); OutStream.WriteLine("// Parameter type informations for template");
            var parameterNameMap = new Dictionary<string, Parameter>();
            if (parameters != null)
            {
                foreach (Parameter param in parameters)
                {
                    parameterNameMap.Add(param.Name, param);
                }
            }

            OpenSection("enum", "ParameterTypeInfo");
            foreach (var parameterName in GenerateParameterTypeInfoList)
            {
                MatchIndent(); OutStream.WriteLine("Has{0} = {1},", parameterName.Name, parameterNameMap.ContainsKey(parameterName.Name) ? 1 : 0);
            }
            CloseSection();

            // Add fake access functions
            MatchIndent(-1); OutStream.WriteLine("public:");
            foreach (var parameterName in GenerateParameterTypeInfoList)
            {
                if (parameterNameMap.ContainsKey(parameterName.Name)) continue;
                MatchIndent(); OutStream.WriteLine("{1} Get{0}() {{ return 0; }}", parameterName.Name, ToTargetTypeName(parameterName.Type));
            }


            // Generate parameter variables
            MatchIndent(-1); OutStream.WriteLine("private:");
            // member section
            if (parameters != null)
            {
                foreach (Parameter param in parameters)
                {
                    switch (param.Type)
                    {
                        case ParameterType.String:
                            MatchIndent(); OutStream.WriteLine(
                                string.Format("const {0} m_{1};", StrTypeString(param), param.Name));
                            break;
                        default:
                            if (param.IsArray)
                            {
                                MatchIndent(); OutStream.WriteLine(
                                    string.Format("ExternalBufferArray<{0}> m_{1};", ToTargetTypeName(param.Type), param.Name));
                            }
                            else
                            {
                                MatchIndent(); OutStream.WriteLine(
                                    string.Format("{0} m_{1};", ToTargetTypeName(param.Type), param.Name));
                            }
                            break;
                    }

                }
                
            }

            // Constructor
            MatchIndent(-1); OutStream.WriteLine("public:");
            MatchIndent(); OutStream.WriteLine(strClassName + "()");
            BuildParserClassInit(":", parameters);
            MatchIndent(1); OutStream.WriteLine("{}");
            NewLine();

            MatchIndent(); OutStream.WriteLine(strClassName + "( MessageDataPtr &pMsg )");
            MatchIndent(1); OutStream.WriteLine(":MessageBase(pMsg)");
            BuildParserClassInit(",", parameters);
            MatchIndent(1); OutStream.WriteLine("{}");
            NewLine();

            // Usage
            MatchIndent(1); OutStream.WriteLine("MessageUsage GetMessageUsage() {{ return MessageUsage_{0}; }}",msg.Usage.ToString());
            NewLine();

            // Generate Get functions
            if (parameters != null)
            {
                foreach (Parameter param in parameters)
                {
                    switch (param.Type)
                    {
                    case ParameterType.String:
                        MatchIndent(); OutStream.WriteLine(
                            string.Format("const {0} Get{1}() const\t{{ return m_{1}; }};", StrTypeString(param), param.Name));
                        break;
                    default:
                        if (param.IsArray)
                        {
                            MatchIndent(); OutStream.WriteLine(
                                string.Format("const Array<{0}>& Get{1}() const\t{{ return m_{1}; }};", ToTargetTypeName(param.Type), param.Name));
                            //MatchIndent(); OutStream.WriteLine(
                            //    string.Format("const {0}& Get{1}() const\t{{ return m_{1}; }};", ArrayLenType, ArrayLenName(param.Name)));
                            //MatchIndent(); OutStream.WriteLine(
                            //    string.Format("const {0}* Get{1}() const\t{{ return m_{1}; }};", param.Type.ToString(), param.Name));
                        }
                        else
                        {
                            MatchIndent(); OutStream.WriteLine(
                                string.Format("const {0}& Get{1}() const\t{{ return m_{1}; }};", ToTargetTypeName(param.Type), param.Name));
                        }
                        break;
                    }
                }
            }

            NewLine();
            // message trace function
            MatchIndent(); OutStream.WriteLine("static Result TraceOut(const char* prefix, MessageDataPtr& pMsg);");
            NewLine();

            // Parse function
            MatchIndent(); OutStream.WriteLine("virtual Result ParseMessage( MessageData* pIMsg );");
            if(AppConfig.GetValue("VariableMapParser", false))
            {
                MatchIndent(); OutStream.WriteLine("static Result ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder );");
            }

            MatchIndent(); OutStream.WriteLine("static Result ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr& pIMsg, MessageBase* &pMsgBase );");
            NewLine();

            // Build function
            MatchIndent(); OutStream.WriteLine("static MessageData* Create( {0} );", BuilderParamString(parameters));
            NewLine();

            // Override route context function
            if (Group.GenParameterRouteContext)
            {
                MatchIndent(); OutStream.WriteLine("Result OverrideRouteContextDestination( EntityUID to );");
                NewLine();
            }

            // Override route hop function
            if (Group.GenParameterRouteHopCount)
            {
                MatchIndent(); OutStream.WriteLine("Result OverrideRouteInformation( EntityUID to, unsigned hopCount );");
                NewLine();
            }

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

        void BuildMessageIDImpl(MessageBase msg, MsgType msgType, string typeName)
        {
            MatchIndent(); OutStream.WriteLine("const MessageID {0}::MID = {1};", MsgClassName(msg.Name, typeName), MakeMsgIDStr(msgType, msg.Reliable, Group.IsMobile, msg.Name));
        }
        
        // Build parser class implementation
        void BuildParserImpl(string Name, string typeName, Parameter[] parameters)
        {
            string strClassName = MsgClassName(Name, typeName);
            OpenSection("Result", strClassName + "::ParseMessage( MessageData* pIMsg )");

            DefaultHRESULT(); NewLine();

            bool bHasParameter = parameters != null && parameters.Length > 0;

            if (bHasParameter)
            {
                MatchIndent(); OutStream.WriteLine("int iMsgSize;");
                MatchIndent(); OutStream.WriteLine("uint8_t* pCur;");

                // define variable first
                foreach (Parameter param in parameters)
                {
                    switch (param.Type)
                    {
                        case ParameterType.String:
                            MatchIndent(); OutStream.WriteLine("{0} {1} = 0;", ArrayLenType, ArrayLenName(param.Name));
                            break;
                        default:
                            if (param.IsArray)
                            {
                                MatchIndent(); OutStream.WriteLine("{0} numberof{1} = 0; {2}* p{1} = nullptr;", ArrayLenType, param.Name, ToTargetTypeName(param.Type));
                            }
                            break;
                    }
                }
            }

            NewLine();
            MatchIndent(); OutStream.WriteLine("protocolChkPtr(pIMsg);");
            NewLine();

            if (bHasParameter)
            {
                // array len types
                if (Group.IsMobile)
                {
                    MatchIndent(); OutStream.WriteLine("iMsgSize = (int)((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));");
                }
                else
                {
                    MatchIndent(); OutStream.WriteLine("iMsgSize = (int)((size_t)pIMsg->GetMessageSize() - sizeof(MessageHeader));");
                }
                MatchIndent(); OutStream.WriteLine("pCur = pIMsg->GetMessageData();");
            }
            NewLine();

            if (parameters == null)
            {
                // nothing to process
                MatchIndent(); OutStream.WriteLine("goto Proc_End;");
            }
            else
            {

                foreach (Parameter param in parameters)
                {
                    switch (param.Type)
                    {
                        case ParameterType.String:
                            //MatchIndent(); OutStream.WriteLine("{0} {1} = 0;", ArrayLenType, ArrayLenName(param.Name));
                            MatchIndent(); OutStream.WriteLine("protocolChk( Protocol::StreamParamCopy( &{1}, pCur, iMsgSize, sizeof({0}) ) );", ArrayLenType, ArrayLenName(param.Name));
                            MatchIndent(); OutStream.WriteLine("protocolChk( Protocol::StreamParamLnk( m_{0}, pCur, iMsgSize, sizeof(char)*{1} ) );", param.Name, ArrayLenName(param.Name));
                            break;
                        default:
                            if (param.IsArray)
                            {
                                //MatchIndent(); OutStream.WriteLine("{0} numberof{1} = 0; {2}* p{1} = nullptr;", ArrayLenType, param.Name, param.Type.ToString());
                                MatchIndent(); OutStream.WriteLine("protocolChk( Protocol::StreamParamCopy( &numberof{1}, pCur, iMsgSize, sizeof({0}) ) );", ArrayLenType, param.Name);
                                MatchIndent(); OutStream.WriteLine("protocolChk( Protocol::StreamParamLnk( p{0}, pCur, iMsgSize, sizeof({1})*numberof{0} ) );", param.Name, ToTargetTypeName(param.Type));
                                MatchIndent(); OutStream.WriteLine("m_{0}.SetLinkedBuffer(numberof{0}, numberof{0}, p{0});", param.Name);
                            }
                            else
                            {
                                MatchIndent(); OutStream.WriteLine("protocolChk( Protocol::StreamParamCopy( &m_{0}, pCur, iMsgSize, sizeof({1}) ) );", param.Name, ToTargetTypeName(param.Type));
                            }
                            break;
                    }
                }
            }

            NewLine(2);

            ProcEnd(); NewLine();
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
            OpenSection("Result", strClassName + "::ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder )");

            DefaultHRESULT(); NewLine();

            bool bHasParameter = parameters != null && parameters.Length > 0;

            NewLine();
            MatchIndent(); OutStream.WriteLine("{0} parser;", strClassName);
            MatchIndent(); OutStream.WriteLine("protocolChk(parser.ParseMessage(*pIMsg));");
            NewLine();

            if (parameters != null)
            {
                foreach (Parameter param in parameters)
                {
                    var csharpType = SystemTypeInfo.ToCSharpType(param.Type);
                    

                    switch (param.Type)
                    {
                        default:
                            if (param.IsArray)
                            {
                                var cppTypeName = SystemTypeInfo.ElementTypeNameFor(TypeUsage.CPP, param);
                                //MatchIndent(); OutStream.WriteLine("variableBuilder.SetVariable(\"{0}\", (int)parser.Get{0}().size(), (const {1}*)parser.Get{0}().data());", param.Name, cppTypeName);
                                MatchIndent(); OutStream.WriteLine("variableBuilder.SetVariable(\"{0}\", parser.Get{0}());", param.Name, cppTypeName);
                            }
                            else if(csharpType.IsEnum)
                            {
                                MatchIndent(); OutStream.WriteLine("variableBuilder.SetVariable(\"{0}\", (int)parser.Get{0}());", param.Name);
                            }
                            else
                            {
                                MatchIndent(); OutStream.WriteLine("variableBuilder.SetVariable(\"{0}\", parser.Get{0}());", param.Name);
                            }
                            break;
                    }
                }
            }

            NewLine(2);

            ProcEnd(); NewLine();
            ReturnHR(); NewLine();

            CloseSection();
        }

        // Build parser class implementation
        void BuildParserToMessageBaseImpl(string Name, string typeName, Parameter[] parameters)
        {
            string strClassName = MsgClassName(Name, typeName);
            OpenSection("Result", strClassName + "::ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr& pIMsg, MessageBase* &pMessageBase )");

            DefaultHRESULT();

            bool bHasParameter = parameters != null && parameters.Length > 0;

            NewLine();
            MatchIndent(); OutStream.WriteLine("protocolMem(pMessageBase = new(memHeap) {0}(pIMsg));", strClassName);
            MatchIndent(); OutStream.WriteLine("protocolChk(pMessageBase->ParseMsg());", strClassName);
            NewLine();

            ProcEnd();
            ReturnHR(); NewLine();

            CloseSection();
        }


        // Build parser class implementation
        void BuildOverrideRouteContextImpl(string Name, string typeName, Parameter[] parameters)
        {
            if (!Group.GenParameterRouteContext)
                return;

            string strClassName = MsgClassName(Name, typeName);
            OpenSection("Result", strClassName + "::OverrideRouteContextDestination( EntityUID to )");

            DefaultHRESULT(); NewLine();

            MatchIndent(); OutStream.WriteLine("int iMsgSize;");
            MatchIndent(); OutStream.WriteLine("uint8_t* pCur;");
            MatchIndent(); OutStream.WriteLine("MessageData* pIMsg = GetMessage();");
            MatchIndent(); OutStream.WriteLine("RouteContext routeContext;");
            NewLine();
            MatchIndent(); OutStream.WriteLine("protocolChkPtr(pIMsg);");
            NewLine();

            // array len types
            if (Group.IsMobile)
            {
                MatchIndent(); OutStream.WriteLine("iMsgSize = (int)((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));");
            }
            else
            {
                MatchIndent(); OutStream.WriteLine("iMsgSize = (int)((size_t)pIMsg->GetMessageSize() - sizeof(MessageHeader));");
            }

            MatchIndent(); OutStream.WriteLine("pCur = pIMsg->GetMessageData();");
            NewLine();

            if (parameters == null)
            {
                // nothing to process
                MatchIndent(); OutStream.WriteLine("goto Proc_End;");
            }
            else
            {
                // Just follow the same process to parsing
                foreach (Parameter param in parameters)
                {
                    switch (param.Type)
                    {
                        case ParameterType.String:
                            MatchIndent(); OutStream.WriteLine("{0} {1} = 0;", ArrayLenType, ArrayLenName(param.Name));
                            MatchIndent(); OutStream.WriteLine("protocolChk( Protocol::StreamParamCopy( &{1}, pCur, iMsgSize, sizeof({0}) ) );", ArrayLenType, ArrayLenName(param.Name));
                            MatchIndent(); OutStream.WriteLine("pCur += sizeof(char)*{1}; iMsgSize -= sizeof(char)*{1};", ArrayLenName(param.Name));
                            break;
                        case ParameterType.RouteContext:
                            break;
                        default:
                            if (param.IsArray)
                            {
                                MatchIndent(); OutStream.WriteLine("pCur += sizeof({0}); iMsgSize -= sizeof({0});", ArrayLenType);
                                MatchIndent(); OutStream.WriteLine("pCur += sizeof({0})*m_{1}.size(); iMsgSize -= (INT)(sizeof({0})*m_{1}.size());", ToTargetTypeName(param.Type), param.Name);
                                //MatchIndent(); OutStream.WriteLine("pCur += sizeof({0})*m_{1}; iMsgSize -= sizeof({0})*m_{1};", param.Type.ToString(), ArrayLenName(param.Name));
                            }
                            else
                            {
                                MatchIndent(); OutStream.WriteLine("pCur += sizeof({0}); iMsgSize -= sizeof({0});", param.Type);
                            }
                            break;
                    }

                    // All other process is same
                    if (param.Type == ParameterType.RouteContext)
                    {
                        MatchIndent(); OutStream.WriteLine("Assert( iMsgSize >= (INT)sizeof(RouteContext) );");
                        MatchIndent(); OutStream.WriteLine("memcpy( &routeContext, pCur, sizeof(RouteContext) );");
                        MatchIndent(); OutStream.WriteLine("routeContext.Components.To = to;");
                        MatchIndent(); OutStream.WriteLine("memcpy( pCur, &routeContext, sizeof(RouteContext) );");
                        break;
                    }
                }
            }

            NewLine(2);

            ProcEnd(); NewLine();
            ReturnHR(); NewLine();

            CloseSection();
        }


        // Build override route hop count class implementation
        void BuildOverrideRouteHopCountImpl(string Name, string typeName, Parameter[] parameters)
        {
            if (!Group.GenParameterRouteHopCount)
                return;

            string strClassName = MsgClassName(Name, typeName);
            OpenSection("Result", strClassName + "::OverrideRouteInformation( EntityUID to, unsigned hopCount )");

            DefaultHRESULT(); NewLine();

            MatchIndent(); OutStream.WriteLine("int iMsgSize;");
            MatchIndent(); OutStream.WriteLine("uint8_t* pCur;");
            MatchIndent(); OutStream.WriteLine("MessageData* pIMsg = GetMessage();");
            MatchIndent(); OutStream.WriteLine("RouteContext routeContext;");
            NewLine();
            MatchIndent(); OutStream.WriteLine("protocolChkPtr(pIMsg);");
            NewLine();

            // array len types
            if (Group.IsMobile)
            {
                MatchIndent(); OutStream.WriteLine("iMsgSize = (int)((size_t)pIMsg->GetMessageSize() - sizeof(MobileMessageHeader));");
            }
            else
            {
                MatchIndent(); OutStream.WriteLine("iMsgSize = (int)((size_t)pIMsg->GetMessageSize() - sizeof(MessageHeader));");
            }

            MatchIndent(); OutStream.WriteLine("pCur = pIMsg->GetMessageData();");
            NewLine();

            if (parameters == null)
            {
                // nothing to process
                MatchIndent(); OutStream.WriteLine("goto Proc_End;");
            }
            else
            {
                // Just follow the same process to parsing
                foreach (Parameter param in parameters)
                {
                    switch (param.Type)
                    {
                        case ParameterType.String:
                            MatchIndent(); OutStream.WriteLine("{0} {1} = 0;", ArrayLenType, ArrayLenName(param.Name));
                            MatchIndent(); OutStream.WriteLine("protocolChk( Protocol::StreamParamCopy( &{1}, pCur, iMsgSize, sizeof({0}) ) );", ArrayLenType, ArrayLenName(param.Name));
                            MatchIndent(); OutStream.WriteLine("pCur += sizeof(char)*{1}; iMsgSize -= sizeof(char)*{1};", ArrayLenName(param.Name));
                            break;
                        default:
                            if (param.Type == ParameterType.RouteContext && param.Name == ParamRouteContext.Name)
                            {
                                MatchIndent(); OutStream.WriteLine("Assert( iMsgSize >= (INT)sizeof(RouteContext) );");
                                MatchIndent(); OutStream.WriteLine("memcpy( &routeContext, pCur, sizeof(RouteContext) );");
                                MatchIndent(); OutStream.WriteLine("routeContext.Components.To = to;");
                                MatchIndent(); OutStream.WriteLine("memcpy( pCur, &routeContext, sizeof(RouteContext) );");
                            }
                            else if (param.Name == ParamRouteHopCount.Name)
                            {
                                MatchIndent(); OutStream.WriteLine("Assert( iMsgSize >= (INT)sizeof({0}) );", ToTargetTypeName(ParamRouteHopCount.Type));
                                MatchIndent(); OutStream.WriteLine("*({0}*)pCur = hopCount;", ToTargetTypeName(ParamRouteHopCount.Type));
                            }

                            if (param.IsArray)
                            {
                                MatchIndent(); OutStream.WriteLine("pCur += sizeof({0}); iMsgSize -= sizeof({0});", ArrayLenType);
                                MatchIndent(); OutStream.WriteLine("pCur += sizeof({0})*m_{1}.size(); iMsgSize -= (INT)(sizeof({0})*m_{1}.size());", ToTargetTypeName(param.Type), param.Name);
                                //MatchIndent(); OutStream.WriteLine("pCur += sizeof({0})*m_{1}; iMsgSize -= sizeof({0})*m_{1};", param.Type.ToString(), ArrayLenName(param.Name));
                            }
                            else
                            {
                                MatchIndent(); OutStream.WriteLine("pCur += sizeof({0}); iMsgSize -= sizeof({0});", ToTargetTypeName(param.Type));
                            }
                            break;
                    }

                    // All other process is same
                    if (param.Name == ParamRouteHopCount.Name)
                    {
                        break;
                    }
                }
            }

            NewLine(2);

            ProcEnd(); NewLine();
            ReturnHR(); NewLine();

            CloseSection();
        }

        // Builder params size
        public void BuildBuilderMessageSize(Parameter[] parameters, string strSizeVarName)
        {
            // size calculation
            string strSize = "";
            if (parameters != null)
            {
                foreach (Parameter param in parameters)
                {
                    string strLenName;
                    switch (param.Type)
                    {
                        case ParameterType.String:
                            strLenName = string.Format("__ui{0}Length", InParamName(param.Name));
                            MatchIndent(); OutStream.WriteLine("{2} {0} = {1} ? ({2})(strlen({1})+1) : 1;", strLenName, InParamName(param.Name), ArrayLenType);
                            strSize += string.Format(" + sizeof(uint16_t) + {0}", strLenName);
                            break;
                    }
                }
            }

            MatchIndent();
            string strMessageHeader = Group.IsMobile ? "MobileMessageHeader" : "MessageHeader";

            if (strSize.Length > 0)
                OutStream.Write(string.Format("unsigned {0} = (unsigned)(sizeof({1}) + {2} ", strSizeVarName, strMessageHeader, strSize));
            else
                OutStream.Write(string.Format("unsigned {0} = (unsigned)(sizeof({1}) ", strSizeVarName, strMessageHeader));

            if (parameters != null)
            {
                foreach (Parameter param in parameters)
                {
                    switch (param.Type)
                    {
                        case ParameterType.String:
                            continue;
                    }

                    NewLine();
                    MatchIndent(1);
                    if (param.IsArray)
                    {
                        OutStream.Write("+ sizeof({0})*{1}.size() + sizeof({2})", ToTargetTypeName(param.Type), InParamName(param.Name), ArrayLenType);
                    }
                    else
                    {
                        OutStream.Write("+ sizeof({0})", ToTargetTypeName(param.Type));
                    }
                }
                OutStream.WriteLine(");");
            }
            else
                OutStream.WriteLine(");");
        }

        void BuildParamCpyPreamble(Parameter[] parameters)
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
                    MatchIndent(); OutStream.WriteLine("{1} numberOf{0} = ({1}){0}.size(); ", InParamName(param.Name), ArrayLenType);
                }
            }
        }

        void BuildParamCpy(Parameter[] parameters)
        {
            if (parameters == null)
                return;

            foreach (Parameter param in parameters)
            {
                string strLenName;
                if (IsStrType(param)) // string type
                {
                    strLenName = string.Format("__ui{0}Length", InParamName(param.Name));
                    MatchIndent(); OutStream.WriteLine("Protocol::PackParamCopy( pMsgData, &{0}, sizeof(uint16_t) );", strLenName);
                    MatchIndent(); OutStream.WriteLine("Protocol::PackParamCopy( pMsgData, {0} ? {0} : \"\", {1} );", InParamName(param.Name), strLenName);
                }
                else if (param.IsArray) // array
                {
                    MatchIndent(); OutStream.WriteLine("Protocol::PackParamCopy( pMsgData, &numberOf{0}, sizeof({1})); ", InParamName(param.Name), ArrayLenType);
                    MatchIndent(); OutStream.WriteLine("Protocol::PackParamCopy( pMsgData, {0}.data(), (INT)(sizeof({1})*{0}.size())); ", InParamName(param.Name), ToTargetTypeName(param.Type));
                }
                else // generic type
                {
                    MatchIndent(); OutStream.Write("Protocol::PackParamCopy( pMsgData, &{0}, sizeof({1}));", InParamName(param.Name), ToTargetTypeName(param.Type)); NewLine();
                }
            }
        }

        // Build parser class implementation
        void BuildBuilderImpl(string Name, string typeName, Parameter[] parameters)
        {
            string strClassName = MsgClassName(Name, typeName);
            bool bHasParameters = parameters != null && parameters.Length > 0;
            OpenSection("MessageData*", strClassName + string.Format("::Create( {0} )", BuilderParamString(parameters)));

            MatchIndent(); OutStream.WriteLine("MessageData *pNewMsg = nullptr;");
            DefaultHRESULT(); NewLine();


            if (bHasParameters)
            {
                MatchIndent(); OutStream.WriteLine("uint8_t *pMsgData = nullptr;");
                NewLine();
            }

            BuildBuilderMessageSize(parameters, "__uiMessageSize");
            NewLine();

            NewLine();

            BuildParamCpyPreamble(parameters);

            MatchIndent(); OutStream.WriteLine(
                string.Format("protocolMem( pNewMsg = MessageData::NewMessage( memHeap, {0}::{1}{2}::MID, __uiMessageSize ) );", Group.Name, Name, typeName));
            NewLine();

            if (bHasParameters)
            {
                MatchIndent(); OutStream.WriteLine("pMsgData = pNewMsg->GetMessageData();");
                NewLine();
            }

            BuildParamCpy(parameters);
            NewLine(2);

            ProcEnd(); NewLine();

            MatchIndent(); OutStream.WriteLine("if(!hr)");
            OpenSection();
            MatchIndent(); OutStream.WriteLine("if(pNewMsg != nullptr) delete pNewMsg;");
            MatchIndent(); OutStream.WriteLine("pNewMsg = nullptr;");
            CloseSection();

            MatchIndent(); OutStream.WriteLine("return pNewMsg;");
            NewLine();


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

                    BuildMessageIDImpl( msg, MsgType.Cmd, "Cmd" );
                    newparams = MakeParameters(MsgType.Cmd, msg.Cmd);
                    BuildParserImpl(msg.Name, "Cmd", newparams); NewLine();
                    BuildParserToVariableBuilderImpl(msg.Name, "Cmd", newparams); NewLine();
                    BuildParserToMessageBaseImpl(msg.Name, "Cmd", newparams); NewLine();
                    BuildBuilderImpl(msg.Name, "Cmd", newparams); NewLine();
                    BuildOverrideRouteContextImpl(msg.Name, "Cmd", newparams); NewLine();
                    BuildOverrideRouteHopCountImpl(msg.Name, "Cmd", newparams); NewLine();
                    BuildMessageTrace(msg.Name, "Cmd", msg.Trace.ToString(), newparams);

                    BuildMessageIDImpl( msg, MsgType.Res, "Res" );
                    newparams = MakeParameters(MsgType.Res, msg.Res);
                    BuildParserImpl(msg.Name, "Res", newparams); NewLine();
                    BuildParserToVariableBuilderImpl(msg.Name, "Res", newparams); NewLine();
                    BuildParserToMessageBaseImpl(msg.Name, "Res", newparams); NewLine();
                    BuildBuilderImpl(msg.Name, "Res", newparams); NewLine();
                    BuildOverrideRouteContextImpl(msg.Name, "Res", newparams); NewLine();
                    BuildOverrideRouteHopCountImpl(msg.Name, "Res", newparams); NewLine();
                    BuildMessageTrace(msg.Name, "Res", msg.Trace.ToString(), newparams);
                }

                if (baseMsg is ProtocolsProtocolGroupC2SEvent)
                {
                    MatchIndent(); OutStream.WriteLine("// C2S: " + baseMsg.Desc);
                    ProtocolsProtocolGroupC2SEvent msg = baseMsg as ProtocolsProtocolGroupC2SEvent;

                    BuildMessageIDImpl( msg, MsgType.Evt, "C2SEvt" );
                    newparams = MakeParameters(MsgType.Evt, msg.Params);
                    BuildParserImpl(msg.Name, "C2SEvt", newparams); NewLine();
                    BuildParserToVariableBuilderImpl(msg.Name, "C2SEvt", newparams); NewLine();
                    BuildParserToMessageBaseImpl(msg.Name, "C2SEvt", newparams); NewLine();
                    BuildBuilderImpl(msg.Name, "C2SEvt", newparams); NewLine();
                    BuildOverrideRouteContextImpl(msg.Name, "C2SEvt", newparams); NewLine();
                    BuildOverrideRouteHopCountImpl(msg.Name, "C2SEvt", newparams); NewLine();
                    BuildMessageTrace(msg.Name, "C2SEvt", msg.Trace.ToString(), newparams);
                }

                if (baseMsg is ProtocolsProtocolGroupS2CEvent)
                {
                    MatchIndent(); OutStream.WriteLine("// S2C: " + baseMsg.Desc);
                    ProtocolsProtocolGroupS2CEvent msg = baseMsg as ProtocolsProtocolGroupS2CEvent;

                    BuildMessageIDImpl(msg, MsgType.Evt, "S2CEvt");
                    newparams = MakeParameters(MsgType.Evt, msg.Params);
                    BuildParserImpl(msg.Name, "S2CEvt", newparams); NewLine();
                    BuildParserToVariableBuilderImpl(msg.Name, "S2CEvt", newparams); NewLine();
                    BuildParserToMessageBaseImpl(msg.Name, "S2CEvt", newparams); NewLine();
                    BuildBuilderImpl(msg.Name, "S2CEvt", newparams); NewLine();
                    BuildOverrideRouteContextImpl(msg.Name, "S2CEvt", newparams); NewLine();
                    BuildOverrideRouteHopCountImpl(msg.Name, "S2CEvt", newparams); NewLine();
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
