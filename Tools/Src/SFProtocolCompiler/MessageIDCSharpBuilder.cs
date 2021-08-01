////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) Kyungkun Ko.
// 
// Author : KyungKun Ko
//
// Description : CSharp network message ID maps
//
////////////////////////////////////////////////////////////////////////////////

using System;
using System.Collections.Generic;
using System.Text;
using ProtocolXml;
using SF;

namespace ProtocolCompiler
{
    class MessageIDCSharpBuilder : Builder
    {
        const string DLL_NAME = "SFEngineDLL";


        string AccessPropertyName(MessageBase baseMsg, string msgTypeName)
        {
            return string.Format("{0}{1}", baseMsg.Name, msgTypeName);
        }
        string NativeAccessPropertyName(MessageBase baseMsg, string msgTypeName)
        {
            return string.Format("CSSFNetMessageID_{0}{1}{2}", Group.Name, baseMsg.Name, msgTypeName);
        }
        string NativeMessagIDName(MessageBase baseMsg, string msgTypeName)
        {
            return string.Format("SF::Message::{0}::{1}{2}::MID.IDSeq.MsgID", Group.Name, baseMsg.Name, msgTypeName);
        }


        // constructor
        public MessageIDCSharpBuilder(Dictionary<string, string> settings)
            : base(settings)
        {
            BasePath = BasePath + "CSharp";
        }

        public string BuilderNamespace
        {
            get { return "Net"; }
        }

        public string OutputFileNameCS()
        {
            return "SFNetMessageID" + Group.Name + ".cs";
        }

        public string OutputFileNameCPP()
        {
            return "SFCSNetMessageID" + Group.Name + ".cpp";
        }

        void BuildCSPrefix()
        {
            OutStream.WriteLine("////////////////////////////////////////////////////////////////////////////////");
            OutStream.WriteLine("// ");
            OutStream.WriteLine("// CopyRight (c) 2017 StromForge");
            OutStream.WriteLine("// ");
            OutStream.WriteLine("// Author : Generated");
            OutStream.WriteLine("// ");
            OutStream.WriteLine(string.Format("// Description : {0} Message IDs", Group.Name));
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
            OutStream.WriteLine(string.Format("// Description : {0} Message IDs", Group.Name));
            OutStream.WriteLine("// ");
            OutStream.WriteLine("////////////////////////////////////////////////////////////////////////////////");
            OutStream.WriteLine("");
            OutStream.WriteLine("");
            OutStream.WriteLine("#include \"SFEngineDLLPCH.h\"");
            OutStream.WriteLine("#include \"Net/SFConnection.h\"");
            OutStream.WriteLine("#include \"Protocol/{0}MsgClass.h\"", Group.Name);
            OutStream.WriteLine("#include \"SharpCPP/SFCSUtil.h\"");
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
            return ParamInString("", newParameters.ToArray());
        }
        string ParamInListStringNative(TypeUsage from, Parameter[] parameter)
        {
            if (parameter == null || parameter.Length == 0)
            {
                return "m_Connection.NativeHandle";
            }
            else
                return "m_Connection.NativeHandle" + ParamInListString(from, "", parameter);
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
                bool bIsStruct = IsStruct(param);

                if (IsStrType(param)) // string type
                {
                    strParams += string.Format("{0} {1}{2}", typeName, strPrefix, InParamName(param.Name));
                }
                else if (param.IsArray) // array
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
                var typeInfo = SystemTypeInfo.GetParameterInfo(param);
                //Type scharpType = SystemTypeInfo.ToCSharpType(param.Type);
                bool paramTypeEquality = paramTypeFrom == paramTypeTo;

                if (IsStrType(param)) // string type
                {
                    strParams.AppendFormat("{0}{1}", strPrefix, InParamName(param.Name));
                }
                else if (param.IsArray) // array
                {
                    if (from == TypeUsage.CPPForSharp)
                    {
                        strParams.AppendFormat("SF::ArrayView<const {2}>({0}_sizeOf{1}, {0}_sizeOf{1}, const_cast<{3}>({0}{1}))", strPrefix, InParamName(param.Name), paramElementTypeName, paramTypeNameOnly);
                    }
                    else
                    {
                        if (from == TypeUsage.CSharp)
                        {
                            strParams.AppendFormat("(ushort){0}{1}.Length, ", strPrefix, InParamName(param.Name));
                        }

                        if (from == TypeUsage.CSharp && typeInfo.IsEnum)
                            strParams.AppendFormat("GameTypes.ToIntArray({0}{1})", strPrefix, InParamName(param.Name));
                        else
                            strParams.AppendFormat("{0}{1}", strPrefix, InParamName(param.Name));
                    }
                }
                else // generic type
                {
                    if (typeInfo.IsCSharpStruct)
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


        // Build parser class implementation
        void BuildAccessProperty(MessageBase baseMsg, string msgTypeName)
        {
            MatchIndent(); OutStream.WriteLine("public static int {0} {{ get {{ return {1}(); }} }}", AccessPropertyName(baseMsg, msgTypeName), NativeAccessPropertyName(baseMsg, msgTypeName));
        }

        // Build parser class implementation
        void BuildAccessPropertyNativeInterface(MessageBase baseMsg, string msgTypeName)
        {
            MatchIndent(); OutStream.WriteLine("[DllImport(NativeDLLName, EntryPoint = \"{0}\", CharSet = CharSet.Auto)]", NativeAccessPropertyName(baseMsg, msgTypeName));
            MatchIndent(); OutStream.WriteLine("static extern int {0}();", NativeAccessPropertyName(baseMsg, msgTypeName));

            NewLine();
        }


        // Build parser class implementation
        void BuildAccessPropertyNativeImplementation(MessageBase baseMsg, string msgTypeName)
        {
            OpenSection("SFDLL_EXPORT int ",
                string.Format("{0}()", NativeAccessPropertyName(baseMsg, msgTypeName)),
                false);

            MatchIndent(); OutStream.WriteLine("return {0};", NativeMessagIDName(baseMsg,msgTypeName));

            CloseSection();

            NewLine();
        }

        

        void BuildMessageIDClassCSharp()
        {
            // Packer interface
            OpenSection("public partial class", "MessageID" + Group.Name);


            MatchIndent(); OutStream.WriteLine("const string NativeDLLName = ");
            MatchIndent(); OutStream.WriteLine("#if UNITY_IOS");
            MatchIndent(); OutStream.WriteLine("    \"__Internal\";");
            MatchIndent(); OutStream.WriteLine("#else");
            MatchIndent(); OutStream.WriteLine("    \"{0}\";", DLL_NAME);
            MatchIndent(); OutStream.WriteLine("#endif");



            foreach (MessageBase baseMsg in Group.Items)
            {
                if (baseMsg is ProtocolsProtocolGroupCommand)
                {
                    MatchIndent(); OutStream.WriteLine("// Cmd: " + baseMsg.Desc);
                    ProtocolsProtocolGroupCommand msg = baseMsg as ProtocolsProtocolGroupCommand;

                    BuildAccessProperty(msg, "Cmd"); NewLine();
                    BuildAccessProperty(msg, "Res"); NewLine();
                    NewLine();
                }

                if (baseMsg is ProtocolsProtocolGroupC2SEvent)
                {
                    MatchIndent(); OutStream.WriteLine("// C2S: " + baseMsg.Desc);
                    ProtocolsProtocolGroupC2SEvent msg = baseMsg as ProtocolsProtocolGroupC2SEvent;

                    BuildAccessProperty(msg, "C2SEvt"); NewLine();
                }

                if (baseMsg is ProtocolsProtocolGroupS2CEvent)
                {
                    MatchIndent(); OutStream.WriteLine("// S2C: " + baseMsg.Desc);
                    var msg = baseMsg as ProtocolsProtocolGroupS2CEvent;

                    BuildAccessProperty(msg, "S2CEvt"); NewLine();
                }
            }

            MatchIndent(); OutStream.WriteLine("#region Native Interfaces ");
            foreach (MessageBase baseMsg in Group.Items)
            {
                if (baseMsg is ProtocolsProtocolGroupCommand)
                {
                    MatchIndent(); OutStream.WriteLine("// Cmd: " + baseMsg.Desc);
                    ProtocolsProtocolGroupCommand msg = baseMsg as ProtocolsProtocolGroupCommand;

                    BuildAccessPropertyNativeInterface(msg, "Cmd"); NewLine();
                    BuildAccessPropertyNativeInterface(msg, "Res"); NewLine();
                    NewLine();
                }

                if (baseMsg is ProtocolsProtocolGroupC2SEvent)
                {
                    MatchIndent(); OutStream.WriteLine("// C2S: " + baseMsg.Desc);
                    ProtocolsProtocolGroupC2SEvent msg = baseMsg as ProtocolsProtocolGroupC2SEvent;

                    BuildAccessPropertyNativeInterface(msg, "C2SEvt"); NewLine();
                }

                if (baseMsg is ProtocolsProtocolGroupS2CEvent)
                {
                    MatchIndent(); OutStream.WriteLine("// S2C: " + baseMsg.Desc);
                    var msg = baseMsg as ProtocolsProtocolGroupS2CEvent;

                    BuildAccessPropertyNativeInterface(msg, "S2CEvt"); NewLine();
                }
            }
            MatchIndent(); OutStream.WriteLine("#endregion //Native Interfaces ");

            
            CloseSection();

        }

        void BuildMessageIDAccessCPP()
        {
            // Packer interface
            foreach (MessageBase baseMsg in Group.Items)
            {
                if (baseMsg is ProtocolsProtocolGroupCommand)
                {
                    MatchIndent(); OutStream.WriteLine("// Cmd: " + baseMsg.Desc);
                    ProtocolsProtocolGroupCommand msg = baseMsg as ProtocolsProtocolGroupCommand;

                    BuildAccessPropertyNativeImplementation(msg, "Cmd"); NewLine();
                    BuildAccessPropertyNativeImplementation(msg, "Res"); NewLine();
                }

                if (baseMsg is ProtocolsProtocolGroupC2SEvent)
                {
                    MatchIndent(); OutStream.WriteLine("// C2S: " + baseMsg.Desc);
                    ProtocolsProtocolGroupC2SEvent msg = baseMsg as ProtocolsProtocolGroupC2SEvent;

                    BuildAccessPropertyNativeImplementation(msg, "C2SEvt"); NewLine();
                }

                if (baseMsg is ProtocolsProtocolGroupS2CEvent)
                {
                    MatchIndent(); OutStream.WriteLine("// S2C: " + baseMsg.Desc);
                    var msg = baseMsg as ProtocolsProtocolGroupS2CEvent;

                    BuildAccessPropertyNativeImplementation(msg, "S2CEvt"); NewLine();
                }
            }

            NewLine();
            NewLine();
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

            BuildMessageIDClassCSharp();
            NewLine(2);

            NewLine(2);
            CloseOutFile();


            // Build C++ native policy class
            IsCPPOut = true;
            ParameterMode = TypeUsage.CPPForSharp;
            OpenOutFile(OutputFileNameCPP());

            BuildCPPPrefix();
            NewLine(2);

            BuildMessageIDAccessCPP();
            NewLine(2);

            NewLine(2);
            CloseOutFile();
        }

    }
}
