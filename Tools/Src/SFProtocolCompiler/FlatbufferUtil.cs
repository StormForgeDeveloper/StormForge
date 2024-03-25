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
    public class FlatbufferUtil
    {

        static public string ToFlatVariableName(string nameString)
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

        static public string ToFlatCSharpVariableName(string nameString)
        {
            var sb = new StringBuilder();
            sb.Capacity = nameString.Length * 2;
            bool bPrevCap = false;
            foreach (char c in nameString)
            {
                if (c >= 'A' && c <= 'Z')
                {
                    if (bPrevCap)
                        sb.Append(char.ToLower(c));
                    else
                        sb.Append(c);

                    bPrevCap = true;
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
        static string ConvertTypes(string typeName, ref string required)
        {
            switch (typeName)
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

                case "StringCrc64":
                case "AuthTicket":
                case "PartyUID":
                case "UGCID":
                    return "uint64";

                case "LogEntryID":
                case "StringCrc32":
                    return "uint32";

                // bypass types
                case "AccountID":
                case "PlayerID":
                    return "AccountID";

                case "GameInsUID":
                    return "GameInstanceUID";

                case "Result":
                case "GameInstanceUID":
                case "EntityUID":
                case "CharacterID":
                case "TransactionID":
                case "Guid":
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

            return typeName;
        }

        public static string ToFlatType(Parameter parameter)
        {
            string flatTypeName = string.Empty;

            var typeInfo = SystemTypeInfo.GetParameterInfo(parameter);

            string required = string.Empty;

            flatTypeName = ConvertTypes(parameter.TypeName, ref required);

            // We need to control per parameter basis. disabling for now
            required = string.Empty;

            if (parameter.IsArray && !flatTypeName.StartsWith('['))
            {
                return $"[{flatTypeName}]{required}";
            }
            else
            {
                return flatTypeName + required;
            }
        }

        public static bool IsScalar(string flatType)
        {
            switch(flatType)
            {
                case "int8":
                case "uint8":
                case "bool":
                case "int16":
                case "uint16":
                case "short":
                case "ushort":
                case "int":
                case "uint":
                case "int32":
                case "uint32":
                case "float":
                case "float32":
                case "long":
                case "ulong":
                case "int64":
                case "uint64":
                case "double":
                case "float64":
                    return true;
            }

            return false;
        }

    }

}
