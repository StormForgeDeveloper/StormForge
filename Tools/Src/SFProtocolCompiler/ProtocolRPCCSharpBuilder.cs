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
    class ProtocolRPCCSharpBuilder : Builder
    {
        string SendFuncName(MessageBase baseMsg, string msgTypeName)
        {
            return $"{baseMsg.Name}{msgTypeName}";
        }
        

        // constructor
        public ProtocolRPCCSharpBuilder(Dictionary<string, string> settings)
            : base(settings)
        {
        }

        public string BuilderNamespace
        {
            get { return "Net"; }
        }

        public string OutputFileNameCS()
        {
            return Group.Name + "RPCSendAdapter.cs";
        }

        void BuildCSPrefix()
        {
            OutStream.WriteLine("////////////////////////////////////////////////////////////////////////////////");
            OutStream.WriteLine("// ");
            OutStream.WriteLine("// CopyRight (c) StromForge");
            OutStream.WriteLine("// ");
            OutStream.WriteLine("// Author : Generated");
            OutStream.WriteLine("// ");
            OutStream.WriteLine(string.Format("// Description : {0} Network RPC send adapter", Group.Name));
            OutStream.WriteLine("// ");
            OutStream.WriteLine("////////////////////////////////////////////////////////////////////////////////");
            OutStream.WriteLine("");
            OutStream.WriteLine("");
            OutStream.WriteLine("using System;");
            OutStream.WriteLine("using System.Diagnostics;");
            OutStream.WriteLine("using SF;");
            OutStream.WriteLine("using SF.Flat;");
            OutStream.WriteLine($"using SF.Flat.{Group.Name};");
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


        TypeUsage m_ParameterMode = TypeUsage.CSharp;
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
                    WriteLineWithIndent($"var {param.Name}Offset = builder.Create{param.TypeName}Vector({InParamName(param.Name)});");
                }
                else
                {
                    if (bIsScalar)
                    {
                        
                    }
                    else
                    {
                        WriteLineWithIndent($"var {param.Name}Offset = builder.Create{param.TypeName}({InParamName(param.Name)});");
                    }
                }

            }

            WriteLineWithIndent($"SF.Flat.{Group.Name}.{packetClassName}.Start{packetClassName}(builder);");

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

                // TransactionId included in message header
                string flatCsharpVariableName = FlatbufferUtil.ToFlatCSharpVariableName(param.Name);

                if (param.IsArray)
                {
                    WriteLineWithIndent($"SF.Flat.{Group.Name}.{packetClassName}.Add{flatCsharpVariableName}(builder, {param.Name}Offset);");
                }
                else
                {
                    if (bIsScalar)
                    {
                        WriteLineWithIndent($"SF.Flat.{Group.Name}.{packetClassName}.Add{flatCsharpVariableName}(builder, {InParamName(param.Name)});");
                    }
                    else
                    {
                        WriteLineWithIndent($"SF.Flat.{Group.Name}.{packetClassName}.Add{flatCsharpVariableName}(builder, {param.Name}Offset);");
                    }
                }

            }

            WriteLineWithIndent($"var packetOffset = SF.Flat.{Group.Name}.{packetClassName}.End{packetClassName}(builder);");
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

            WriteLineWithIndent("if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;");
            WriteLineWithIndent("TransactionID InTransactionID = NewTransactionID();");
            WriteLineWithIndent($"return {SendFuncName(baseMsg, msgTypeName)}({paramCallString});");

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
            //ParameterMode = TypeUsage.CSharpNative;

            WriteLineWithIndent("if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;");
            WriteLineWithIndent("Result result = ResultCode.SUCCESS;");
            WriteLineWithIndent("var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);");

            string packetClassName = $"{baseMsg.Name}{msgTypeName}";
            string messageIdName = $"MessageID{Group.Name}.{baseMsg.Name}{msgTypeName}";

            BuildFlatbufferPacket(packetClassName, parameters);

            string callbackParameter = GenParameterContext ? ", callback:callback" : "";

            if (bIsCmd)
            {
                WriteLineWithIndent($"result = SendMessage({messageIdName}, builder, packetOffset.Value, transactionId:InTransactionID {callbackParameter});");
            }
            else if (msgTypeName == "Res")
            {
                WriteLineWithIndent($"result = SendMessage({messageIdName}, builder, packetOffset.Value, transactionId:InTransactionID, result:InResult);");
            }
            else
            {
                WriteLineWithIndent($"result = SendMessage({messageIdName}, builder, packetOffset.Value);");
            }

            WriteLineWithIndent("return result;");

            CloseSection();
        }


        void BuildClassMember()
        {
            NewLine();
            NewLine();
        }

        void BuildConstructor(string strClassName)
        {
            NewLine();
            OpenSection("public ", string.Format("{0}()", strClassName), false);
            CloseSection();
            OpenSection("public ", string.Format("{0}( SF.IEndpoint endpoint ) : base(endpoint)", strClassName), false);
            CloseSection();
            NewLine();
        }


        void BuildMessageAdapterClassCSharp()
        {
            // Packer interface
            Parameter[] newparams;
            string className = $"{Group.Name}RPCSendAdapter";

            OpenSection("public class", $"{className} : RPCAdapter");

            BuildClassMember();
            BuildConstructor(className);

            foreach (MessageBase baseMsg in Group.Items)
            {
                if (baseMsg is ProtocolsProtocolGroupCommand)
                {
                    WriteLineWithIndent("// Cmd: " + baseMsg.Desc);
                    ProtocolsProtocolGroupCommand msg = baseMsg as ProtocolsProtocolGroupCommand;

                    newparams = MakeParameters(MsgType.Cmd, msg.Cmd);

                    // Remove interface without transitionId
                    //if (Group.GenParameterContext)
                    //{
                    //    BuildCmdAutoTransIdSendFunction(msg, newparams);
                    //}

                    newparams = MakeParameters(MsgType.Cmd, msg.Cmd);
                    BuildSendFunction(msg, "Cmd", newparams);
                    NewLine();
                }

                if (baseMsg is ProtocolsProtocolGroupC2SEvent)
                {
                    WriteLineWithIndent("// C2S: " + baseMsg.Desc);
                    ProtocolsProtocolGroupC2SEvent msg = baseMsg as ProtocolsProtocolGroupC2SEvent;

                    newparams = MakeParameters(MsgType.Evt, msg.Params);
                    BuildSendFunction(msg, "C2SEvt", newparams); NewLine();
                    NewLine();
                }
            }

            CloseSection();

            className = $"{Group.Name}SvrRPCSendAdapter";
            OpenSection("public class", $"{className} : RPCAdapter");

            BuildClassMember();
            BuildConstructor(className);

            foreach (MessageBase baseMsg in Group.Items)
            {
                if (baseMsg is ProtocolsProtocolGroupCommand)
                {
                    WriteLineWithIndent("// Cmd: " + baseMsg.Desc);
                    ProtocolsProtocolGroupCommand msg = baseMsg as ProtocolsProtocolGroupCommand;

                    newparams = MakeParameters(MsgType.Res, msg.Res);
                    BuildSendFunction(msg, "Res", newparams); NewLine();
                    NewLine();
                }

                if (baseMsg is ProtocolsProtocolGroupS2CEvent)
                {
                    WriteLineWithIndent("// S2C: " + baseMsg.Desc);
                    ProtocolsProtocolGroupS2CEvent msg = baseMsg as ProtocolsProtocolGroupS2CEvent;

                    newparams = MakeParameters(MsgType.Evt, msg.Params);
                    BuildSendFunction(msg, "S2CEvt", newparams); NewLine();
                    NewLine();
                }

            }

            CloseSection();

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
