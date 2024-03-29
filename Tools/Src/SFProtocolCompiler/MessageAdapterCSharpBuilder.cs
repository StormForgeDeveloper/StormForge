////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) Kyungkun Ko.
// 
// Author : KyungKun Ko
//
// Description : CSharp network policy interface builder
//
////////////////////////////////////////////////////////////////////////////////

using System;
using System.Collections.Generic;
using System.Linq;
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
        public MessageAdapterCSharpBuilder(Dictionary<string, string> settings)
            : base(settings)
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
            OutStream.WriteLine("// CopyRight (c) StromForge");
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
            OutStream.WriteLine("#nullable enable");

            NewLine(3);

            // namespace definition
            OpenSection("namespace", PrjPrefix + "." + BuilderNamespace, false);
        }

        void BuildCSPostfix()
        {
            CloseAllSection();

            OutStream.WriteLine("#nullable restore");
        }

        void BuildCPPPrefix()
        {
            OutStream.WriteLine("////////////////////////////////////////////////////////////////////////////////");
            OutStream.WriteLine("// ");
            OutStream.WriteLine("// CopyRight (c) StromForge");
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
            OutStream.WriteLine("#include \"Protocol/{0}MsgClass.h\"", Group.Name);
            OutStream.WriteLine("#include \"Interfaces/Sharp/SFCSUtil.h\"");
            NewLine(3);


            OutStream.WriteLine("using namespace SF;");
        }



    TypeUsage m_ParameterMode = TypeUsage.CPP;
        TypeUsage ParameterMode { get { return m_ParameterMode; } set { m_ParameterMode = value; } }

        // target type for output
        public override string ToTargetTypeName(Parameter param)
        {
            return SystemTypeInfo.TypeNameFor(ParameterMode, param);
        }

        Parameter m_ArraySizeParam = new Parameter()
        {
            Name = "_sizeof",
            TypeName = "uint16",
        };

        string ParamInStringNative(Parameter[] parameter)
        {
            var newParameters = new List<Parameter>(parameter);
            newParameters.Insert(0, new Parameter()
            {
                Name = "NativeConnectionHandle",
                TypeName = "intptr",
            });
            return ParamInStringNative("", newParameters.ToArray());
        }

        string CallNativeParameterStringWithNativeHandle(Parameter[] parameter)
        {
            if(parameter == null || parameter.Length == 0)
                return "m_Connection.NativeHandle";
            else
                return "m_Connection.NativeHandle" + CallNativeParameterString(parameter);
        }


        // Builder parameter string
        public string ParamInString(string strPrefix, Parameter[] parameter)
        {
            string strParams = "", strComma = "";

            if (parameter == null)
                return strParams;

            foreach (Parameter param in parameter)
            {
                strParams += strComma;
                if (strComma.Length == 0)
                    strComma = ", ";

                var typeName = ToTargetTypeName(param);
                var typeInfo = SystemTypeInfo.GetParameterInfo(param);
                //Type csharpType = SystemTypeInfo.ToCSharpType(param.Type);
                bool bIsStruct = typeInfo.IsCSharpStruct;
                bool IsArray = param.IsArray;
                if (typeInfo.IsCSharpArray)
                {
                    IsArray = true;
                    if (ParameterMode == TypeUsage.CPPForSharp)
                        typeName = typeInfo.CPPTypeName + "*";
                }

                if (IsStrType(param)) // string type
                {
                    strParams += string.Format("{0} {1}{2}", typeName, strPrefix, InParamName(param.Name));
                }
                else if (IsArray) // array
                {
                    if (ParameterMode == TypeUsage.CSharpNative || ParameterMode == TypeUsage.CPPForSharp)
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
        public string ParamInStringNative( string strPrefix, Parameter[] parameter)
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
                var typeInfo = SystemTypeInfo.GetParameterInfo(param);
                //Type csharpType = SystemTypeInfo.ToCSharpType(param.Type);
                bool bIsStruct = typeInfo.IsCSharpStruct;
                bool IsArray = param.IsArray;

                if (IsArray) // array
                {
                    if (IsStrType(param)) // string type
                    {
                        strParams += string.Format("{0} {1}{2}", typeName, strPrefix, InParamName(param.Name));
                    }
                    else if (IsVariableSizeType(param))
                    {
                        if (ParameterMode == TypeUsage.CPPForSharp)
                            typeName = "uint8_t*";
                        else
                            typeName = "IntPtr";

                        if (ParameterMode == TypeUsage.CSharpNative || ParameterMode == TypeUsage.CPPForSharp)
                        {
                            strParams += string.Format("{0} {1}_sizeOf{2},", ToTargetTypeName(m_ArraySizeParam), strPrefix, InParamName(param.Name));
                        }
                        strParams += string.Format("{0} {1}{2}", typeName, strPrefix, InParamName(param.Name));
                    }
                    else
                    {
                        if (ParameterMode == TypeUsage.CSharpNative || ParameterMode == TypeUsage.CPPForSharp)
                        {
                            strParams += string.Format("{0} {1}_sizeOf{2},", ToTargetTypeName(m_ArraySizeParam), strPrefix, InParamName(param.Name));
                        }
                        strParams += string.Format("{0} {1}{2}", typeName, strPrefix, InParamName(param.Name));
                    }
                }
                else if (IsStrType(param)) // string type
                {
                    strParams += string.Format("{0} {1}{2}", typeName, strPrefix, InParamName(param.Name));
                }
                else if (IsVariableSizeType(param))
                {
                    if (ParameterMode == TypeUsage.CPPForSharp)
                        typeName = "uint8_t*";
                    else
                        typeName = "IntPtr";

                    if (ParameterMode == TypeUsage.CSharpNative || ParameterMode == TypeUsage.CPPForSharp)
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

        public void PrepareCallNative(Parameter[] parameter)
        {
            string strPrefix = "";

            if (parameter == null)
                return ;


            // 1. Prepare local variables;
            foreach (Parameter param in parameter)
            {
                var typeInfo = SystemTypeInfo.GetParameterInfo(param);
                //Type csharpType = SystemTypeInfo.ToCSharpType(param.Type);

                bool IsArray = param.IsArray | typeInfo.IsCSharpArray;

                if (IsArray) // array
                {
                    // Nothing for now
                    if (IsStrType(param))
                    {

                    }
                    else if (IsVariableSizeType(param))
                    {
                        MatchIndent(); OutStream.WriteLine("var {0}{1}_ = {0}{1}.ToByteArray();", strPrefix, InParamName(param.Name));
                    }

                }
                else if (IsStrType(param)) // string type
                {
                    // Nothing for now
                }
                else if (IsVariableSizeType(param))
                {
                    MatchIndent(); OutStream.WriteLine("var {0}{1}_ = {0}{1}.ToByteArray();", strPrefix, InParamName(param.Name));
                }
            }

            //2. Prepare pinned variables or something with using statement
            foreach (Parameter param in parameter)
            {
                var typeInfo = SystemTypeInfo.GetParameterInfo(param);
                //Type csharpType = SystemTypeInfo.ToCSharpType(param.Type);

                bool IsArray = param.IsArray | typeInfo.IsCSharpArray;

                if (IsArray) // array
                {
                    if (IsStrType(param)) // string type
                    {
                        MatchIndent(); OutStream.WriteLine("using (var {0}{1}Array = new ArrayObjectString({0}{1}))", strPrefix, InParamName(param.Name));
                    }
                    else if (IsVariableSizeType(param))
                    {
                        MatchIndent(); OutStream.WriteLine("using (var {0}{1}_PinnedPtr_ = new PinnedByteBuffer({0}{1}_))", strPrefix, InParamName(param.Name));
                    }
                }
                else if (IsStrType(param)) // string type
                {
                    // Nothing for now
                }
                else if (IsVariableSizeType(param))
                {
                    MatchIndent(); OutStream.WriteLine("using (var {0}{1}_PinnedPtr_ = new PinnedByteBuffer({0}{1}_))", strPrefix, InParamName(param.Name));
                }
            }
        }

        public string CallNativeParameterString(Parameter[] parameter)
        {
            TypeUsage from = TypeUsage.CSharp;
            TypeUsage to = ParameterMode;
            StringBuilder strParams = new StringBuilder(512);
            string strComma = ",";
            string strPrefix = "";

            if (parameter == null)
                return strParams.ToString();

            foreach (Parameter param in parameter)
            {
                strParams.Append(strComma);

                string paramElementTypeName = SystemTypeInfo.ElementTypeNameFor(from, param);
                string paramTypeNameOnly = SystemTypeInfo.TypeNameOnlyFor(from, param);
                string paramTypeFrom = SystemTypeInfo.TypeNameFor(from, param);
                string paramTypeTo = SystemTypeInfo.TypeNameFor(to, param);
                var typeInfo = SystemTypeInfo.GetParameterInfo(param);
                //Type csharpType = SystemTypeInfo.ToCSharpType(param.Type);
                bool paramTypeEquality = paramTypeFrom == paramTypeTo;

                bool IsArray = param.IsArray | typeInfo.IsCSharpArray;
                bool bIsStruct = typeInfo.IsCSharpStruct;

                if (IsArray) // array
                {
                    if (IsStrType(param)) // string type
                    {
                        strParams.AppendFormat("{0}{1}Array.NativeHandle", strPrefix, InParamName(param.Name));
                    }
                    else if (IsVariableSizeType(param))
                    {
                        strParams.AppendFormat("(ushort){0}{1}_.Length, ", strPrefix, InParamName(param.Name));
                        strParams.AppendFormat("{0}{1}_PinnedPtr_.Ptr", strPrefix, InParamName(param.Name));
                    }
                    else
                    {
                        strParams.AppendFormat("(ushort){0}{1}.Length, ", strPrefix, InParamName(param.Name));

                        if (typeInfo.IsEnum)
                            strParams.AppendFormat("GameTypes.ToIntArray({0}{1})", strPrefix, InParamName(param.Name));
                        else
                            strParams.AppendFormat("{0}{1}", strPrefix, InParamName(param.Name));
                    }
                }
                else if (IsStrType(param)) // string type
                {
                    strParams.AppendFormat("System.Text.Encoding.UTF8.GetBytes({0}{1} + \"\\0\")", strPrefix, InParamName(param.Name));
                }
                else if (IsVariableSizeType(param))
                {
                    strParams.AppendFormat("(ushort){0}{1}_.Length, ", strPrefix, InParamName(param.Name));
                    strParams.AppendFormat("{0}{1}_PinnedPtr_.Ptr", strPrefix, InParamName(param.Name));
                }
                else // generic type
                {
                    if (bIsStruct)
                    {
                        if (ParameterMode == TypeUsage.CSharp || ParameterMode == TypeUsage.CSharpNative)
                            strParams.AppendFormat("ref {0}{1}", strPrefix, InParamName(param.Name));
                        else
                            strParams.AppendFormat("{0}{1}", strPrefix, InParamName(param.Name));
                    }
                    else
                    {
                        if (paramTypeEquality)
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
        public string CallCreateNativeParameterString(TypeUsage from, string strPrefix, Parameter[] parameter)
        {
            TypeUsage to = ParameterMode;
            StringBuilder strParams = new StringBuilder(512);
            string strComma = ",";

            if (parameter == null)
                return strParams.ToString();

            bool bFirst = true;
            foreach (Parameter param in parameter)
            {
                if (!bFirst)
                    strParams.Append(strComma);
                bFirst = false;

                string paramElementTypeName = SystemTypeInfo.ElementTypeNameFor(from, param);
                string paramTypeNameOnly = SystemTypeInfo.TypeNameOnlyFor(from, param);
                string paramTypeFrom = SystemTypeInfo.TypeNameFor(from, param);
                string paramTypeTo = SystemTypeInfo.TypeNameFor(to, param);
                bool paramTypeEquality = paramTypeFrom == paramTypeTo;
                var typeInfo = SystemTypeInfo.GetParameterInfo(param);

                bool bIsStruct = typeInfo.IsCSharpStruct;

                if (param.IsArray) // array
                {
                    if (IsStrType(param)) // string type
                    {
                        strParams.AppendFormat("{0}{1}Array_", strPrefix, InParamName(param.Name));
                    }
                    else if (IsVariableSizeType(param))
                    {
                        strParams.AppendFormat("{0}{1}Array_", strPrefix, InParamName(param.Name));
                        //strParams.AppendFormat("SF::ArrayView<uint8_t>({0}_sizeOf{1}, {0}_sizeOf{1}, {0}{1})", strPrefix, InParamName(param.Name), paramElementTypeName, paramTypeNameOnly);
                    }
                    else
                    {
                        strParams.AppendFormat("SF::ArrayView<{2}>({0}_sizeOf{1}, {0}_sizeOf{1}, const_cast<{3}>({0}{1}))", strPrefix, InParamName(param.Name), paramElementTypeName, paramTypeNameOnly);
                    }
                }
                else if (IsStrType(param)) // string type
                {
                    strParams.AppendFormat("{0}{1}", strPrefix, InParamName(param.Name));
                }
                else if (IsVariableSizeType(param))
                {
                    strParams.AppendFormat("SF::ArrayView<uint8_t>({0}_sizeOf{1}, {0}_sizeOf{1}, {0}{1})", strPrefix, InParamName(param.Name), paramElementTypeName, paramTypeNameOnly);
                }
                else // generic type
                {
                    if (bIsStruct)
                    {
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
        public void PrepareSendFunctionParametersCPP(string strPrefix, Parameter[] parameter)
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
                var typeInfo = SystemTypeInfo.GetParameterInfo(param);
                //Type scharpType = SystemTypeInfo.ToCSharpType(param.Type);
                bool paramTypeEquality = paramTypeFrom == paramTypeTo;

                //bool bIsStruct = IsStruct(param.Type);

                // Disable native conversion
                if (param.IsArray) // string type
                {
                    if (IsStrType(param))
                    {
                        string varName = string.Format("{0}{1}", strPrefix, InParamName(param.Name));
                        MatchIndent(); OutStream.WriteLine("auto& {0}Array_ = *NativeToObject<SF::ArrayObject<const char*>>({0});", varName);
                    }
                    else if (IsVariableSizeType(param))
                    {
                        string varName = string.Format("{0}{1}", strPrefix, InParamName(param.Name));
                        MatchIndent(); OutStream.WriteLine("SF::DynamicArray<{0}> {1}Array_;", typeInfo.CPPTypeName, varName, InParamName(param.Name));
                        MatchIndent(); OutStream.WriteLine("SF::InputMemoryStream {0}Stream_(SF::ArrayView<uint8_t>(_sizeOf{0}, {0}));", InParamName(param.Name));
                        MatchIndent(); OutStream.WriteLine("{0}Stream_ >> {1}Array_;", InParamName(param.Name), varName);
                    }
                }
            }
        }

        public virtual string CallParamStringSharp(Parameter[] parameter)
        {
            string strParams = "";
            bool bIsFirst = true;

            if (parameter == null)
                return strParams;

            foreach (Parameter param in parameter)
            {
                if (bIsFirst)
                {
                    bIsFirst = false;
                }
                else
                {
                    strParams += ", ";
                }

                strParams += InParamName(param.Name);
            }

            return strParams;
        }  // 


        void BuildCmdAutoTransIdSendFunction(MessageBase baseMsg, Parameter[] parameters)
        {
            ParameterMode = TypeUsage.CSharp;
            string msgTypeName = "Cmd";

            List<Parameter> parameterWithoutTransactionId = new List<Parameter>();
            foreach (Parameter param in parameters)
            {
                if (param.Name == ParamContext.Name)
                    continue;

                parameterWithoutTransactionId.Add(param);
            }

            string paramInString = ParamInString("", parameterWithoutTransactionId.ToArray());
            if (parameterWithoutTransactionId.Count > 0)
                paramInString += ", ";
            paramInString += "Action<SFMessage>? callback = null";


            string paramCallString = CallParamStringSharp(parameters);
            if (parameters.Length > 0)
                paramCallString += ", ";
            paramCallString += "callback";

            OpenSection("public Result ",$"{SendFuncName(baseMsg, msgTypeName)}( {paramInString} )", false);

            MatchIndent(); OutStream.WriteLine("if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;");
            MatchIndent(); OutStream.WriteLine("TransactionID InTransactionID = NewTransactionID();");
            MatchIndent(); OutStream.WriteLine($"return {SendFuncName(baseMsg, msgTypeName)}({paramCallString});");

            CloseSection();
        }

        // Build parser class implementation
        void BuildSendFunction(MessageBase baseMsg, string msgTypeName, Parameter[] parameters)
        {
            ParameterMode = TypeUsage.CSharp;

            string paramInString = ParamInString("", parameters);
            bool bIsCmd = msgTypeName == "Cmd";
            if (bIsCmd)
            {
                paramInString += ", Action<SFMessage>? callback = null";
            }

            OpenSection("public Result ",
                $"{SendFuncName(baseMsg, msgTypeName)}( {paramInString} )",
                false);
            ParameterMode = TypeUsage.CSharpNative;

            MatchIndent(); OutStream.WriteLine("if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;");
            MatchIndent(); OutStream.WriteLine("Result result;");

            PrepareCallNative(parameters);

            MatchIndent(); OutStream.WriteLine("{");
            MatchIndent(); OutStream.WriteLine("result = new Result({0}({1}));", NativeFuncName(baseMsg, msgTypeName), CallNativeParameterStringWithNativeHandle(parameters));
            MatchIndent(); OutStream.WriteLine("}");

            string contextInParam = ", TransactionID.Empty";
            string callbackInParam = string.Empty;
            if (Group.GenParameterContext && bIsCmd)
            {
                contextInParam = ", InTransactionID";
                callbackInParam = ", callback";
            }

            MatchIndent(); OutStream.WriteLine($"m_Connection.HandleSentMessage(result{contextInParam}, MessageID{Group.Name}.{baseMsg.Name}{msgTypeName}{callbackInParam});");
            MatchIndent(); OutStream.WriteLine("return result;");

            CloseSection();
        }

        // Build parser class implementation
        void BuildSendFunctionNativeInterface(MessageBase baseMsg, string msgTypeName, Parameter[] parameters)
        {
            IsCSharpNative = true;
            ParameterMode = TypeUsage.CSharpNative;
            MatchIndent(); OutStream.WriteLine("[DllImport(NativeDLLName, EntryPoint = \"{0}\", CharSet = CharSet.Ansi)]", NativeFuncName(baseMsg, msgTypeName));
            MatchIndent(); OutStream.WriteLine("static extern int {0}({1} );", NativeFuncName(baseMsg, msgTypeName), ParamInStringNative(parameters));
            IsCSharpNative = false;
            NewLine();
        }


        // Build parser class implementation
        void BuildSendFunctionNativeImplementation(MessageBase baseMsg, string msgTypeName, Parameter[] parameters)
        {

            ParameterMode = TypeUsage.CPP;
            string createParamString = "";
            if (parameters.Length > 0)
                createParamString += CallCreateNativeParameterString(TypeUsage.CPPForSharp, "", parameters);


            ParameterMode = TypeUsage.CPPForSharp;

            OpenSection("SFDLL_EXPORT int ",
                string.Format("{0}( {1} )", NativeFuncName(baseMsg, msgTypeName), ParamInStringNative(parameters)),
                false);

            MatchIndent(); OutStream.WriteLine("auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);");
            MatchIndent(); OutStream.WriteLine("if(pConnection == nullptr) return (int)ResultCode::INVALID_POINTER;");

            PrepareSendFunctionParametersCPP("", parameters);

            MatchIndent(); OutStream.WriteLine($"size_t messageSize = SF::Message::{Group.Name}::{baseMsg.Name}{msgTypeName}::CalculateMessageSize({createParamString});");
            MatchIndent(); OutStream.WriteLine("SFNET_ALLOC_MESSAGE_FROM_STACK(pMessage,messageSize);");
            string combineString = parameters.Length > 0 ? ", " : "";
            MatchIndent(); OutStream.WriteLine($"Result hr = SF::Message::{Group.Name}::{baseMsg.Name}{msgTypeName}::Create(pMessage{combineString}{createParamString});");
            MatchIndent(); OutStream.WriteLine("if (hr) hr = pConnection->SendMsg(pMessage);");
            MatchIndent(); OutStream.WriteLine("return (int32_t)hr;");

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
            //MatchIndent(); OutStream.WriteLine("SF.SFConnection m_Connection;");
            //MatchIndent(); OutStream.WriteLine("public SF.SFConnection Connection { get { return m_Connection; } }");
            NewLine();
        }
        void BuildConstructor(string strClassName)
        {
            NewLine();
            OpenSection("public ", string.Format("{0}()", strClassName), false);
            CloseSection();
            OpenSection("public ", string.Format("{0}( SF.SFConnection connection ) : base(connection)", strClassName), false);
            CloseSection();
            NewLine();
        }


        void BuildMessageAdapterClassCSharp()
        {
            // Packer interface
            Parameter[] newparams;

            OpenSection("public class", String.Format("SendMessage{0} : SendMessage",Group.Name));

            BuildClassMember();
            BuildConstructor("SendMessage" + Group.Name);

            foreach (MessageBase baseMsg in Group.Items)
            {
                if (baseMsg is ProtocolsProtocolGroupCommand)
                {
                    MatchIndent(); OutStream.WriteLine("// Cmd: " + baseMsg.Desc);
                    ProtocolsProtocolGroupCommand msg = baseMsg as ProtocolsProtocolGroupCommand;

                    newparams = MakeParameters(MsgType.Cmd, msg.Cmd);
                    if (Group.GenParameterContext)
                    {
                        BuildCmdAutoTransIdSendFunction(msg, newparams);
                    }

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



            OpenSection("public class", String.Format("SendMessageSvr{0} : SendMessage", Group.Name));

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
            // Build C# policy class
            IsCPPOut = false;
            ParameterMode = TypeUsage.CSharp;
            OpenOutFile(OutputFileNameCS());

            BuildCSPrefix();
            NewLine(2);

            BuildMessageAdapterClassCSharp();
            NewLine(2);

            NewLine(2);
            BuildCSPostfix();
            CloseOutFile();
        }

    }
}
