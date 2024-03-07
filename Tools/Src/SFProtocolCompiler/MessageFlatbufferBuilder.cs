////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Protocol Flaxbuffer script builder
//
////////////////////////////////////////////////////////////////////////////////

using System;
using System.Collections.Generic;
using System.Text;
using System.Text.RegularExpressions;
using ProtocolXml;
using SF;
using SF.Tool;

namespace ProtocolCompiler
{
    class MessageFlatbufferBuilder: Builder
    {
        // constructor
        public MessageFlatbufferBuilder(Dictionary<string, string> settings)
            : base(settings)
        {
            GenParameterRouteHopCount = true;
            IsCPPOut = true;
        }

        public override bool GenParameterRouteHopCount => false;

        public override bool GenParameterRouteContext => false;
        public override bool GenParameterContext => false;

        public string OutputDocName()
        {
            return Group.Name + ".fbs";
        }

        void BuildPrefix()
        {
            OutStream.WriteLine("include \"LocalTypes.fbs\";");
            OutStream.WriteLine($"namespace SF.Flat.{Group.Name};");
            NewLine(1);
        }

        string m_RootTypeName = string.Empty;

        // build API doc class
        void BuildAPIStruct(ProtocolXml.MessageBase msg, MsgType msgType, string typeName, Parameter[] parameters)
        {
            string messageStructName = m_RootTypeName = $"{msg.Name}{typeName}";
            m_RootTypeName = messageStructName; // whatever last becomes root type

            OpenSection("table", messageStructName, false);

            if (parameters != null)
            {
                foreach(var parameter in parameters)
                {
                    MatchIndent(); OutStream.WriteLine($"{ToFlaxName(parameter.Name)}:{ToFlaxType(parameter)};");
                }
            }

            CloseSection();
            NewLine();
        }

        string ToFlaxName(string nameString)
        {
            var sb = new StringBuilder();
            sb.Capacity = nameString.Length * 2;
            bool bPrevCap = true;
            foreach (char c in nameString)
            {
                if (c >= 'A' && c <= 'Z')
                {
                    char curChar = char.ToLower(c);
                    if (!bPrevCap)
                        sb.Append('_');

                    bPrevCap = true;
                    sb.Append(curChar);
                }
                else
                {
                    bPrevCap = false;
                    sb.Append(c);
                }
            }

            return sb.ToString();

        }

        // convert special type for fbs
        string ConvertTypes(string flatType, ref string required)
        {
            //if (flatType.StartsWith("SF."))
            //    flatType = flatType.Substring(3);

            switch (flatType)
            {
                case "String":
                case "string":
                    required = "(required)";
                    return "string";
                case "Int64":
                case "int64":
                    return "int64";
                case "UInt64":
                case "uint64":
                    return "uint64";
                case "int":
                    return "int";
                case "Int32":
                case "int32":
                    return "int32";
                case "UInt32":
                case "uint32":
                    return "uint32";
                case "int16":
                case "Int16":
                    return "int16";
                case "uint16":
                case "UInt16":
                    return "uint16";
                case "int8":
                case "Int8":
                    return "int8";
                case "uint8":
                case "UInt8":
                    return "uint8";
                case "Byte":
                case "byte":
                    return "ubyte";
                case "SByte":
                case "sbyte":
                    return "byte";
                case "bool":
                    return "bool";

                case "VariableTable":
                    return "[ubyte]";

                case "TransactionID":
                case "AccountID":
                case "PlayerID":
                case "EntityUID":
                case "GameInsUID":
                case "StringCrc64":
                case "AuthTicket":
                case "PartyUID":
                case "UGCID":
                    return "uint64";

                case "Result":
                case "CharacterID":
                case "LogEntryID":
                case "StringCrc32":
                    return "uint32";

                // bypass types
                case "GameStateID":
                case "NamedVariable":
                    break;

                default:
                    required = "(required)";
                    break;

                //default:
                //    Console.Error.WriteLine($"Don't know how to convert:{flatType}.");
                //    break;
            }

            return flatType;
        }

        string ToFlaxType(Parameter parameter)
        {
            string flatTypeName = string.Empty;
            
            var typeInfo = SystemTypeInfo.GetParameterInfo(parameter);

            string required = string.Empty;// (typeInfo.IsString || typeInfo.IsCSharpStruct) ? "(required)" : string.Empty;

            flatTypeName = ConvertTypes(parameter.TypeName, ref required);
            //if (typeInfo.IsCSharpStruct || typeInfo.IsEnum)
            //{
            //    flatTypeName = ConvertTypes(parameter.TypeName);
            //}
            //else
            //{
            //    // Using csharp type because CSharp has non-c++ type style
            //    flatTypeName = ConvertTypes(parameter.TypeName);
            //}

            if (parameter.IsArray && !flatTypeName.StartsWith('['))
            {
                return $"[{flatTypeName}]{required}";
            }
            else
            {
                return flatTypeName + required;
            }
        }

        // build parser class header
        void BuildGroupAPI()
        {
            Parameter[] newparams;

            foreach (MessageBase baseMsg in Group.Items)
            {
                if (baseMsg is ProtocolsProtocolGroupCommand)
                {
                    ProtocolsProtocolGroupCommand msg = baseMsg as ProtocolsProtocolGroupCommand;

                    BuildAPIStruct(msg, MsgType.Cmd, "Cmd", MakeParameters(MsgType.Cmd, msg.Cmd));

                    BuildAPIStruct(msg, MsgType.Res, "Res", MakeParameters(MsgType.Res, msg.Res));
                }

                if (baseMsg is ProtocolsProtocolGroupC2SEvent)
                {
                    ProtocolsProtocolGroupC2SEvent msg = baseMsg as ProtocolsProtocolGroupC2SEvent;

                    newparams = MakeParameters(MsgType.Evt, msg.Params);
                    BuildAPIStruct(msg, MsgType.Evt, "C2SEvt", newparams);
                }

                if (baseMsg is ProtocolsProtocolGroupS2CEvent)
                {
                    ProtocolsProtocolGroupS2CEvent msg = baseMsg as ProtocolsProtocolGroupS2CEvent;

                    newparams = MakeParameters(MsgType.Evt, msg.Params);
                    BuildAPIStruct(msg, MsgType.Evt, "S2CEvt", newparams);
                }
            }

            MatchIndent(); OutStream.WriteLine($"root_type {m_RootTypeName};");
        }

        public override void Build()
        {
            // Build Parser class
            OpenOutFile(OutputDocName());

            BuildPrefix();
            BuildGroupAPI();

            NewLine(2);
            CloseOutFile();
        }

    }
}
