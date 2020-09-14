////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2017 Kyungkun Ko.
// 
// Author : KyungKun Ko
//
// Description : CSharp network policy interface builder
//
////////////////////////////////////////////////////////////////////////////////

using System;
using System.Collections.Generic;
using System.Text;
using ProtocolXml;
using SF;

namespace ProtocolCompiler
{
    class MessageAdapterCSharpBuilder : Builder
    {
        const string DLL_NAME = "SFEngineDLL";


        string NativeFuncName(MessageBase baseMsg, string msgTypeName)
        {
            return string.Format("CSSFNetAdapter_{0}{1}{2}", Group.Name, baseMsg.Name, msgTypeName);
        }
        string SendFuncName(MessageBase baseMsg, string msgTypeName)
        {
            return string.Format("{0}{1}", baseMsg.Name, msgTypeName);
        }
        

        // constructor
        public MessageAdapterCSharpBuilder(string strBasePath)
            : base(strBasePath + "CSharp")
        {
        }

        public string BuilderNamespace
        {
            get { return "Net"; }
        }

        public string OutputFileNameCS()
        {
            return "SFNetSendMessage" + Group.Name + ".cs";
        }

        public string OutputFileNameCPP()
        {
            return "SFCSNetSendMessage" + Group.Name + ".cpp";
        }

        void BuildCSPrefix()
        {
            OutStream.WriteLine("////////////////////////////////////////////////////////////////////////////////");
            OutStream.WriteLine("// ");
            OutStream.WriteLine("// CopyRight (c) 2017 StromForge");
            OutStream.WriteLine("// ");
            OutStream.WriteLine("// Author : Generated");
            OutStream.WriteLine("// ");
            OutStream.WriteLine(string.Format("// Description : {0} Network Adapter", Group.Name));
            OutStream.WriteLine("// ");
            OutStream.WriteLine("////////////////////////////////////////////////////////////////////////////////");
            OutStream.WriteLine("");
            OutStream.WriteLine("");
            OutStream.WriteLine("using System;");
            OutStream.WriteLine("using System.Diagnostics;");
            OutStream.WriteLine("using System.Runtime.InteropServices;");
            OutStream.WriteLine("using SF;");
            NewLine(3);

            // namespace definition
            OpenSection("namespace", PrjPrefix + "." + BuilderNamespace, false);
        }

        void BuildCPPPrefix()
        {
            OutStream.WriteLine("////////////////////////////////////////////////////////////////////////////////");
            OutStream.WriteLine("// ");
            OutStream.WriteLine("// CopyRight (c) 2017 StromForge");
            OutStream.WriteLine("// ");
            OutStream.WriteLine("// Author : Generated");
            OutStream.WriteLine("// ");
            OutStream.WriteLine(string.Format("// Description : {0} Network Adapter", Group.Name));
            OutStream.WriteLine("// ");
            OutStream.WriteLine("////////////////////////////////////////////////////////////////////////////////");
            OutStream.WriteLine("");
            OutStream.WriteLine("");
            OutStream.WriteLine("#include \"SFEngineDLLPCH.h\"");
            OutStream.WriteLine("#include \"Net/SFConnection.h\"");
            OutStream.WriteLine("#include \"Protocol/Message/{0}MsgClass.h\"", Group.Name);
            OutStream.WriteLine("#include \"SFCSUtil.h\"");
            NewLine(3);


            OutStream.WriteLine("using namespace SF;");
        }



    TypeUsage m_ParameterMode = TypeUsage.CPP;
        TypeUsage ParameterMode { get { return m_ParameterMode; } set { m_ParameterMode = value; } }

       // target type for output
        public string ToTargetTypeName(Parameter param)
        {
            return SystemTypeInfo.TypeNameFor(ParameterMode, param);
        }

        Parameter m_ArraySizeParam = new Parameter()
        {
            Name = "_sizeof",
            Type = ParameterType.uint16,
            //IsArray = false,
            //IsArraySpecified = false,
        };



        string ParamInStringNative(Parameter[] parameter)
        {
            var newParameters = new List<Parameter>(parameter);
            newParameters.Insert(0, new Parameter()
            {
                Name = "NativeConnectionHandle",
                Type = ParameterType.intptr,
            });
            return ParamInString("", newParameters.ToArray());
        }
        string ParamInListStringNative(TypeUsage from, Parameter[] parameter)
        {
            if(parameter == null || parameter.Length == 0)
            {
                return "m_Connection.NativeHandle";
            }
            else
                return "m_Connection.NativeHandle" + ParamInListString(from, "", parameter);
        }


        // Builder parameter string
        public string ParamInString( string strPrefix, Parameter[] parameter)
        {
            string strParams = "", strComma = "";

            if (parameter == null)
                return strParams;

            foreach (Parameter param in parameter)
            {
                strParams += strComma;
                if( strComma.Length == 0 )
                    strComma = ", ";

                var typeName = ToTargetTypeName(param);
                bool bIsStruct = IsStruct(param.Type);

                if (IsStrType(param)) // string type
                {
                    strParams += string.Format("{0} {1}{2}", typeName, strPrefix, InParamName(param.Name));
                }
                else if (param.IsArray) // array
                {
                    if(ParameterMode == TypeUsage.CSharpNative || ParameterMode == TypeUsage.CPPForSharp)
                    {
                        strParams += string.Format("{0} {1}_sizeOf{2},", ToTargetTypeName(m_ArraySizeParam), strPrefix, InParamName(param.Name));
                    }
                    strParams += string.Format("{0} {1}{2}", typeName, strPrefix, InParamName(param.Name));
                }
                else // generic type
                {
                    strParams += string.Format("{0} {1}{2}", typeName, strPrefix, InParamName(param.Name));
                }
            }

            return strParams;
        }

        // Builder parameter string
        public string ParamInListString(TypeUsage from, string strPrefix, Parameter[] parameter)
        {
            TypeUsage to = ParameterMode;
            StringBuilder strParams = new StringBuilder(512);
            string strComma = ",";

            if (parameter == null)
                return strParams.ToString();

            foreach (Parameter param in parameter)
            {
                strParams.Append(strComma);

                string paramElementTypeName = SystemTypeInfo.ElementTypeNameFor(from, param);
                string paramTypeNameOnly = SystemTypeInfo.TypeNameOnlyFor(from, param);
                string paramTypeFrom = SystemTypeInfo.TypeNameFor(from, param);
                string paramTypeTo = SystemTypeInfo.TypeNameFor(to, param);
                Type scharpType = SystemTypeInfo.ToCSharpType(param.Type);
                bool paramTypeEquality = paramTypeFrom == paramTypeTo;

                bool bIsStruct = IsStruct(param.Type);

                if (IsStrType(param)) // string type
                {
                    if (from == TypeUsage.CSharp)
                        strParams.AppendFormat("System.Text.Encoding.UTF8.GetBytes({0}{1} + \"\\0\")", strPrefix, InParamName(param.Name));
                    else
                        strParams.AppendFormat("{0}{1}", strPrefix, InParamName(param.Name));
                }
                else if (param.IsArray) // array
                {
                    if (from == TypeUsage.CPPForSharp)
                    {
                        strParams.AppendFormat("SF::ArrayView<{2}>({0}_sizeOf{1}, {0}_sizeOf{1}, const_cast<{3}>({0}{1}))", strPrefix, InParamName(param.Name), paramElementTypeName, paramTypeNameOnly);
                    }
                    else
                    {
                        if (from == TypeUsage.CSharp)
                        {
                            strParams.AppendFormat("(ushort){0}{1}.Length, ", strPrefix, InParamName(param.Name));
                        }

                        if (from == TypeUsage.CSharp && scharpType.IsEnum)
                            strParams.AppendFormat("GameTypes.ToIntArray({0}{1})", strPrefix, InParamName(param.Name));
                        else
                            strParams.AppendFormat("{0}{1}", strPrefix, InParamName(param.Name));
                    }
                }
                else // generic type
                {
                    if (bIsStruct)
                    {
                        if(ParameterMode == TypeUsage.CSharp || ParameterMode == TypeUsage.CSharpNative)
                            strParams.AppendFormat("ref {0}{1}", strPrefix, InParamName(param.Name));
                        else
                            strParams.AppendFormat("{0}{1}", strPrefix, InParamName(param.Name));
                    }
                    else
                    {
                        if(paramTypeEquality)
                        {
                            strParams.AppendFormat(" {0}{1}", strPrefix, InParamName(param.Name));
                        }
                        else
                        {
                            strParams.AppendFormat("({2}) {0}{1}", strPrefix, InParamName(param.Name), paramTypeTo);
                        }
                    }
                }
            }

            return strParams.ToString();
        }


        // Builder parameter string
        public void AddStringParamSwapCPP(string strPrefix, Parameter[] parameter)
        {
            TypeUsage from = TypeUsage.CPPForSharp;
            TypeUsage to = ParameterMode;

            if (parameter == null)
                return;

            foreach (Parameter param in parameter)
            {
                string paramElementTypeName = SystemTypeInfo.ElementTypeNameFor(from, param);
                string paramTypeNameOnly = SystemTypeInfo.TypeNameOnlyFor(from, param);
                string paramTypeFrom = SystemTypeInfo.TypeNameFor(from, param);
                string paramTypeTo = SystemTypeInfo.TypeNameFor(to, param);
                Type scharpType = SystemTypeInfo.ToCSharpType(param.Type);
                bool paramTypeEquality = paramTypeFrom == paramTypeTo;

                bool bIsStruct = IsStruct(param.Type);

                // Disable native conversion
                //if (IsStrType(param)) // string type
                //{
                //    string varName = string.Format("{0}{1}", strPrefix, InParamName(param.Name));
                //    string tempBuffName = string.Format("{0}{1}_TempEncodingBuff", strPrefix, InParamName(param.Name));

                //    MatchIndent(); OutStream.WriteLine("char {0}[Net::MAX_STRING_TEMP_BUFF_SIZE];", tempBuffName);
                //    MatchIndent(); OutStream.WriteLine("StrUtil::ANSIToUTF8({0}, {1}, (int)countof({1}));", varName, tempBuffName);
                //    MatchIndent(); OutStream.WriteLine("{0} = {1};", varName, tempBuffName);
                //}
            }
        }


        // Build parser class implementation
        void BuildSendFunction(MessageBase baseMsg, string msgTypeName, Parameter[] parameters)
        {
            ParameterMode = TypeUsage.CSharp;
            OpenSection("public int ",
                string.Format("{0}( {1} )", SendFuncName(baseMsg, msgTypeName), ParamInString("", parameters)),
                false);

            ParameterMode = TypeUsage.CSharpNative;
            MatchIndent(); OutStream.WriteLine("var result = {0}({1});", NativeFuncName(baseMsg, msgTypeName), ParamInListStringNative(TypeUsage.CSharp,parameters));
            MatchIndent(); OutStream.WriteLine("m_Connection.MessageRouter.HandleSentMessage(result, MessageID{0}.{1}{2});", Group.Name, baseMsg.Name, msgTypeName);
            MatchIndent(); OutStream.WriteLine("return result;");

            CloseSection();
        }

        // Build parser class implementation
        void BuildSendFunctionNativeInterface(MessageBase baseMsg, string msgTypeName, Parameter[] parameters)
        {
            IsCSharpNative = true;
            ParameterMode = TypeUsage.CSharpNative;
            MatchIndent(); OutStream.WriteLine("[DllImport(NativeDLLName, EntryPoint = \"{0}\", CharSet = CharSet.Ansi)]", NativeFuncName(baseMsg, msgTypeName));
            //MatchIndent(); OutStream.WriteLine("[return: MarshalAs(UnmanagedType.I1)]");
            MatchIndent(); OutStream.WriteLine("static extern int {0}({1} );", NativeFuncName(baseMsg, msgTypeName), ParamInStringNative(parameters));
            IsCSharpNative = false;
            NewLine();
        }


        // Build parser class implementation
        void BuildSendFunctionNativeImplementation(MessageBase baseMsg, string msgTypeName, Parameter[] parameters)
        {

            ParameterMode = TypeUsage.CPP;
            string createParamString = "pConnection->GetHeap()";
            if (parameters.Length > 0)
                createParamString += ParamInListString(TypeUsage.CPPForSharp, "", parameters);


            ParameterMode = TypeUsage.CPPForSharp;

            OpenSection("SFDLL_EXPORT int ",
                string.Format("{0}( {1} )", NativeFuncName(baseMsg, msgTypeName), ParamInStringNative(parameters)),
                false);

            MatchIndent(); OutStream.WriteLine("auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);");
            MatchIndent(); OutStream.WriteLine("if(pConnection == nullptr) return ResultCode::INVALID_POINTER;");

            AddStringParamSwapCPP("", parameters);

            MatchIndent(); OutStream.WriteLine("MessageDataPtr pMessage = SF::Message::{0}::{1}{2}::Create({3});", Group.Name, baseMsg.Name, msgTypeName, createParamString);
            MatchIndent(); OutStream.WriteLine("if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;");
            MatchIndent(); OutStream.WriteLine("auto res = pConnection->Send(pMessage);", SendFuncName(baseMsg, msgTypeName));
            MatchIndent(); OutStream.WriteLine("return (uint32_t)res;");

            CloseSection();

            NewLine();
        }


        void BuildClassMember()
        {
            NewLine();
            MatchIndent(); OutStream.WriteLine("const string NativeDLLName = ");
            MatchIndent(); OutStream.WriteLine("#if UNITY_IOS");
            MatchIndent(); OutStream.WriteLine("    \"__Internal\";");
            MatchIndent(); OutStream.WriteLine("#else");
            MatchIndent(); OutStream.WriteLine("    \"{0}\";", DLL_NAME);
            MatchIndent(); OutStream.WriteLine("#endif");
            MatchIndent(); OutStream.WriteLine("SF.SFConnection m_Connection;");
            NewLine();
        }
        void BuildConstructor(string strClassName)
        {
            NewLine();
            OpenSection("public ", string.Format("{0}( SF.SFConnection connection )", strClassName), false);
            MatchIndent(); OutStream.WriteLine("m_Connection = connection;");
            CloseSection();
            NewLine();
        }


        void BuildMessageAdapterClassCSharp()
        {
            // Packer interface
            Parameter[] newparams;

            OpenSection("public class", "SendMessage"+Group.Name);

            BuildClassMember();
            BuildConstructor("SendMessage" + Group.Name);

            foreach (MessageBase baseMsg in Group.Items)
            {
                if (baseMsg is ProtocolsProtocolGroupCommand)
                {
                    MatchIndent(); OutStream.WriteLine("// Cmd: " + baseMsg.Desc);
                    ProtocolsProtocolGroupCommand msg = baseMsg as ProtocolsProtocolGroupCommand;

                    newparams = MakeParameters(MsgType.Cmd, msg.Cmd);
                    BuildSendFunction(msg, "Cmd", newparams);
                    NewLine();
                }

                if (baseMsg is ProtocolsProtocolGroupC2SEvent)
                {
                    MatchIndent(); OutStream.WriteLine("// C2S: " + baseMsg.Desc);
                    ProtocolsProtocolGroupC2SEvent msg = baseMsg as ProtocolsProtocolGroupC2SEvent;

                    newparams = MakeParameters(MsgType.Evt, msg.Params);
                    BuildSendFunction(msg, "C2SEvt", newparams); NewLine();
                    NewLine();
                }
            }

            MatchIndent(); OutStream.WriteLine("#region Native Interfaces ");
            foreach (MessageBase baseMsg in Group.Items)
            {
                if (baseMsg is ProtocolsProtocolGroupCommand)
                {
                    MatchIndent(); OutStream.WriteLine("// Cmd: " + baseMsg.Desc);
                    ProtocolsProtocolGroupCommand msg = baseMsg as ProtocolsProtocolGroupCommand;

                    newparams = MakeParameters(MsgType.Cmd, msg.Cmd);
                    BuildSendFunctionNativeInterface(msg, "Cmd", newparams);
                    NewLine();
                }

                if (baseMsg is ProtocolsProtocolGroupC2SEvent)
                {
                    MatchIndent(); OutStream.WriteLine("// C2S: " + baseMsg.Desc);
                    ProtocolsProtocolGroupC2SEvent msg = baseMsg as ProtocolsProtocolGroupC2SEvent;

                    newparams = MakeParameters(MsgType.Evt, msg.Params);
                    BuildSendFunctionNativeInterface(msg, "C2SEvt", newparams); NewLine();
                    NewLine();
                }
            }
            MatchIndent(); OutStream.WriteLine("#endregion //Native Interfaces ");

            CloseSection();



            OpenSection("public class", "SendMessageSvr" + Group.Name);

            BuildClassMember();
            BuildConstructor("SendMessageSvr" + Group.Name);

            foreach (MessageBase baseMsg in Group.Items)
            {
                if (baseMsg is ProtocolsProtocolGroupCommand)
                {
                    MatchIndent(); OutStream.WriteLine("// Cmd: " + baseMsg.Desc);
                    ProtocolsProtocolGroupCommand msg = baseMsg as ProtocolsProtocolGroupCommand;

                    newparams = MakeParameters(MsgType.Res, msg.Res);
                    BuildSendFunction(msg, "Res", newparams); NewLine();
                    NewLine();
                }

                if (baseMsg is ProtocolsProtocolGroupS2CEvent)
                {
                    MatchIndent(); OutStream.WriteLine("// S2C: " + baseMsg.Desc);
                    ProtocolsProtocolGroupS2CEvent msg = baseMsg as ProtocolsProtocolGroupS2CEvent;

                    newparams = MakeParameters(MsgType.Evt, msg.Params);
                    BuildSendFunction(msg, "S2CEvt", newparams); NewLine();
                    NewLine();
                }

            }

            MatchIndent(); OutStream.WriteLine("#region Native Interfaces ");

            foreach (MessageBase baseMsg in Group.Items)
            {
                if (baseMsg is ProtocolsProtocolGroupCommand)
                {
                    MatchIndent(); OutStream.WriteLine("// Cmd: " + baseMsg.Desc);
                    ProtocolsProtocolGroupCommand msg = baseMsg as ProtocolsProtocolGroupCommand;

                    newparams = MakeParameters(MsgType.Res, msg.Res);
                    BuildSendFunctionNativeInterface(msg, "Res", newparams); NewLine();
                    NewLine();
                }

                if (baseMsg is ProtocolsProtocolGroupS2CEvent)
                {
                    MatchIndent(); OutStream.WriteLine("// S2C: " + baseMsg.Desc);
                    ProtocolsProtocolGroupS2CEvent msg = baseMsg as ProtocolsProtocolGroupS2CEvent;

                    newparams = MakeParameters(MsgType.Evt, msg.Params);
                    BuildSendFunctionNativeInterface(msg, "S2CEvt", newparams); NewLine();
                    NewLine();
                }
            }
            MatchIndent(); OutStream.WriteLine("#endregion //Native Interfaces ");

            CloseSection();

        }

        void BuildSendAdapterCPP()
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
                    BuildSendFunctionNativeImplementation(msg, "Cmd", newparams);
                    NewLine();
                }

                if (baseMsg is ProtocolsProtocolGroupC2SEvent)
                {
                    MatchIndent(); OutStream.WriteLine("// C2S: " + baseMsg.Desc);
                    ProtocolsProtocolGroupC2SEvent msg = baseMsg as ProtocolsProtocolGroupC2SEvent;

                    newparams = MakeParameters(MsgType.Evt, msg.Params);
                    BuildSendFunctionNativeImplementation(msg, "C2SEvt", newparams); NewLine();
                    NewLine();
                }
            }

            NewLine();
            NewLine();
            NewLine();

            foreach (MessageBase baseMsg in Group.Items)
            {
                if (baseMsg is ProtocolsProtocolGroupCommand)
                {
                    MatchIndent(); OutStream.WriteLine("// Cmd: " + baseMsg.Desc);
                    ProtocolsProtocolGroupCommand msg = baseMsg as ProtocolsProtocolGroupCommand;

                    newparams = MakeParameters(MsgType.Res, msg.Res);
                    BuildSendFunctionNativeImplementation(msg, "Res", newparams); NewLine();
                    NewLine();
                }

                if (baseMsg is ProtocolsProtocolGroupS2CEvent)
                {
                    MatchIndent(); OutStream.WriteLine("// S2C: " + baseMsg.Desc);
                    ProtocolsProtocolGroupS2CEvent msg = baseMsg as ProtocolsProtocolGroupS2CEvent;

                    newparams = MakeParameters(MsgType.Evt, msg.Params);
                    BuildSendFunctionNativeImplementation(msg, "S2CEvt", newparams); NewLine();
                    NewLine();
                }

            }
        }


        public override void Build()
        {
            if (!Group.GenCSharp)
                return;

            // Build C# policy class
            IsCPPOut = false;
            ParameterMode = TypeUsage.CSharp;
            OpenOutFile(OutputFileNameCS());

            BuildCSPrefix();
            NewLine(2);

            BuildMessageAdapterClassCSharp();
            NewLine(2);

            NewLine(2);
            CloseOutFile();


            // Build C++ native policy class
            IsCPPOut = true;
            OpenOutFile(OutputFileNameCPP());

            BuildCPPPrefix();
            NewLine(2);

            BuildSendAdapterCPP();
            NewLine(2);

            NewLine(2);
            CloseOutFile();
        }

    }
}
