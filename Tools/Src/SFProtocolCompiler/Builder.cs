////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Builder base
//
////////////////////////////////////////////////////////////////////////////////

using System;
using System.Collections.Generic;
using System.Text;
using System.IO;
using ProtocolXml;
using SF;
using SF.Tool;

namespace ProtocolCompiler
{


    public abstract class Builder
    {

        public enum MsgType
        {
            NetCtrl,
            Cmd,
            Res,
            Evt
        };


        // Output file stream
        FileStream m_OutFile;
        StreamWriter m_OutStream;

        // Tab indent count
        int m_iIndent;

        // Section stack
        Stack<string> m_SectionStack;

        // settings for build
        Dictionary<string, string> m_SettingsOrg; // Originally pass
        Dictionary<string, string> m_Settings = new Dictionary<string, string>(); // modified during operation
        string GetSetting(string key, string defaultValue = "")
        {
            if (m_Settings.ContainsKey(key))
                return m_Settings[key];

            if (m_SettingsOrg.ContainsKey(key))
                return m_SettingsOrg[key];

            return defaultValue;
        }
        void SetSetting(string key, string newValue)
        {
            m_Settings[key] = newValue;
        }

        public string BuildYear
        {
            get { return "" + DateTime.Now.Year; }
        }


        // Out file base path
        //private string m_strBasePath;
        // Output file path
        public string BasePath
        {
            get { return GetSetting("BasePath"); }
            set { SetSetting("BasePath", value); }
        }


        // Project name prefix
        public string PrjPrefix
        {
            get { return AppConfig.GetValueString("namesapce", "SF"); }
        }

        // Pre-compiled header for cpp
        public string PreCompiledHeader
        {
            get { return AppConfig.GetValueString("pch", "SFProtocolPCH.h"); }
        }

        // array size type
        virtual public string ArrayLenType
        {
            get { return "uint16_t"; }
        }

        // parameter for context parameter
        private Parameter m_ParamContext;
        public Parameter ParamContext
        {
            get { return m_ParamContext; }
        }

        // parameter for context parameter
        private Parameter m_ParamResult;
        public Parameter ParamResult
        {
            get { return m_ParamResult; }
        }

        private Parameter m_ParamRouteContext;
        protected Parameter ParamRouteContext
        {
            get { return m_ParamRouteContext; }
            set { m_ParamRouteContext = value; }
        }

        private Parameter m_ParamRouteHopCount;
        protected Parameter ParamRouteHopCount
        {
            get { return m_ParamRouteHopCount; }
        }


        protected bool m_GenParameterRouteHopCount;

        private ProtocolsProtocolGroup m_group;
        public ProtocolsProtocolGroup Group
        {
            get { return m_group; }
            set { m_group = value; }
        }

        // Generate parameter route hop count
        public bool GenParameterRouteHopCount
        {
            get { return m_group.GenParameterRouteHopCount && m_GenParameterRouteHopCount; }
            set { m_GenParameterRouteHopCount = value; }
        }

        public bool IsCSharpNative { get; set; }

        public bool IsCPPOut { get; set; }
        //////////////////////////////////////////////////////////////////
        //
        // Parameter generation options
        //




        // Constructor
        public Builder(Dictionary<string, string> settings)
        {
            IsCPPOut = true;
            IsCSharpNative = false;
            m_iIndent = 0;
            m_SectionStack = new Stack<string>();

            // default turned off so that it will not generate route hop parameter if the group option is off
            m_GenParameterRouteHopCount = true;

            m_SettingsOrg = settings;


            m_ParamContext = new Parameter();
            m_ParamContext.IsArray = false;
            m_ParamContext.IsArraySpecified = false;
            m_ParamContext.Name = "TransactionID";
            m_ParamContext.TypeName = "TransactionID";

            m_ParamResult = new Parameter();
            m_ParamResult.IsArray = false;
            m_ParamResult.IsArraySpecified = false;
            m_ParamResult.Name = "Result";
            m_ParamResult.TypeName = "Result";

            m_ParamRouteContext = new Parameter();
            m_ParamRouteContext.IsArray = false;
            m_ParamRouteContext.IsArraySpecified = false;
            m_ParamRouteContext.Name = "RouteContext";
            m_ParamRouteContext.TypeName = "RouteContext";

            m_ParamRouteHopCount = new Parameter();
            m_ParamRouteHopCount.IsArray = false;
            m_ParamRouteHopCount.IsArraySpecified = false;
            m_ParamRouteHopCount.Name = "RouteHopCount";
            m_ParamRouteHopCount.TypeName = "uint16";

        }

        // virtual interface for build
        public abstract void Build();


        // output file management
        public StreamWriter OutStream
        {
            get { return m_OutStream; }
        }

        protected void OpenOutFile( string OutputFileName )
        {
            string strFilePath = BasePath;
            if( !strFilePath.EndsWith( "/" ) 
                && !strFilePath.EndsWith( "\\" ) )
            {
                strFilePath += "/";
            }
            Directory.CreateDirectory(strFilePath);

            strFilePath += OutputFileName;

            m_OutFile = new FileStream( strFilePath, FileMode.Create, FileAccess.Write, FileShare.Read );
            m_OutStream = new StreamWriter( m_OutFile, Encoding.UTF8 );

            IndentReset();
        }

        protected void CloseOutFile()
        {
            // Close all section
            CloseAllSection();
            NewLine(2);

            // close stream
            m_OutStream.Close();
            m_OutFile.Close();

            m_OutStream = null;
            m_OutFile = null;
        }


        // Build utility methods
        public void IndentInc( bool bSync = true )
        {
            m_iIndent++;
            if( bSync )
                m_OutStream.Write(" ");
        }

        public void IndentDec()
        {
            m_iIndent--;
        }

        public void IndentReset()
        {
            m_iIndent = 0;
        }

        public void NewLine( int iNumNewLine = 1)
        {
            for( int iNew = 0; iNew < iNumNewLine; iNew++ )
                m_OutStream.WriteLine();
        }

        // Sections
        public void OpenSection(string sectionType, string sectionName, bool bUseTerminator = true)
        {
            string strSection = sectionType + " " + sectionName;
            MatchIndent(); m_OutStream.Write(strSection);
            NewLine();
            MatchIndent(); m_OutStream.Write("{");
            NewLine();

            if (bUseTerminator)
            {
                m_SectionStack.Push("}; // " + strSection);
            }
            else
            {
                m_SectionStack.Push("} // " + strSection);
            }

            IndentInc();
        }

        public void OpenSection()
        {
            MatchIndent(); m_OutStream.Write("{");
            NewLine();

            m_SectionStack.Push("}");

            IndentInc();
        }

        public void CloseSection()
        {
            string strSection = m_SectionStack.Pop();

            IndentDec();

            MatchIndent(); m_OutStream.Write(strSection);
            NewLine();
        }

        public void CloseSection(string strSectionClose)
        {
            string strSection = m_SectionStack.Pop();

            IndentDec();

            MatchIndent(); m_OutStream.Write(strSectionClose);
            NewLine();
        }

        public void CloseAllSection()
        {
            while (m_SectionStack.Count > 0)
                CloseSection();
        }

        public void DefaultHRESULT()
        {
            MatchIndent();
            OutStream.WriteLine("Result hr;");
        }

        public void ReturnHR()
        {
            MatchIndent();
            OutStream.WriteLine("return hr;");
        }

        public void MatchIndent( int iDiff = 0)
        {
            for (int iIndent = 0; iIndent < (m_iIndent + iDiff); iIndent++)
            {
                m_OutStream.Write("\t");
            }
        }

        // Make Parameter string
        public bool IsStrType(Parameter param)
        {
            return param.TypeName == "String";
        }

        public string ArrayLenName(string Name)
        {
            return "uiSizeOf" + Name;
        }

        public virtual string ToTargetTypeName(Parameter param)
        {
            var typeInfo = SystemTypeInfo.GetParameterInfo(param);

            if (IsCPPOut)
            {
                return typeInfo.CPPTypeName;// SystemTypeInfo.ToCPPType(type);
            }

            if (IsCSharpNative)
            {
                //if (csType == typeof(string))
                if (typeInfo.IsString)
                    return "byte[]";
                else if(typeInfo.IsCSharpStruct)
                    return "ref " + typeInfo.CSharpTypeName;
                else if (typeInfo.IsEnum)
                    return "int";
                else
                    return typeInfo.CSharpTypeName;
            }

            return typeInfo.CSharpTypeName;
        }

        public virtual bool IsVariableSizeType(Parameter param)
        {
            var typeInfo = SystemTypeInfo.GetParameterInfo(param);
            return typeInfo.IsVariableSize;
        }

        public bool IsStruct(Parameter param)
        {
            var typeInfo = SystemTypeInfo.GetParameterInfo(param);
            return typeInfo.IsCSharpStruct;
        }

        public string InArrayTypeName(Parameter param)
        {
            return string.Format("Array<{0}>", ToTargetTypeName(param));
        }


        public string InParamName(string Name)
        {
            return "In" + Name;
        }

        // Message parser class name
        public string MsgClassName(string Name, string typeName)
        {
            return string.Format("{0}{1}", Name, typeName);
        }



        virtual public Parameter[] MakeParameters(MsgType type, Parameter[] parameter)
        {
            int iParam = 0;
            int iNumOrg = parameter != null ? parameter.Length : 0;
            List<Parameter> newParams = new List<Parameter>();

            // Route context need to be the first
            if (m_group.GenParameterRouteContext && m_ParamRouteContext != null)
            {
                newParams.Add(m_ParamRouteContext);
            }

            if (MsgType.Cmd == type)
            {
                if (m_group.GenParameterContext)
                {
                    newParams.Add(m_ParamContext);
                }
            }
            else if (MsgType.Res == type)
            {
                if (m_group.GenParameterContext)
                {
                    newParams.Add(m_ParamContext);
                }
                newParams.Add(m_ParamResult);
            }

            if (Group.GenParameterRouteHopCount && type != MsgType.Res)
            {
                newParams.Add(m_ParamRouteHopCount);
            }

            for (int iOrgParam = 0; iOrgParam < iNumOrg; iParam++, iOrgParam++)
            {
                newParams.Add( parameter[iOrgParam] );
            }

            return newParams.ToArray();
        }


    }



    abstract class CppBuilder : Builder
    {
        public CppBuilder(Dictionary<string, string> settings)
            : base(settings)
        {

        }


        public virtual string PolicyClassName
        {
            get { return "NetPolicy" + Group.Name; }
        }

        public string StrTypeString(Parameter param)
        {
            switch (param.TypeName)
            {
                case "String":
                    return "char*";
                default:
                    return null;
            }
        }

        public virtual string ParamInString(Parameter[] parameter, bool bUseOriginalType = false)
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
                else if (!bUseOriginalType && IsVariableSizeType(param))
                {
                    strParams += string.Format("const Array<uint8_t>& {0}", InParamName(param.Name));
                }
                else // generic type
                {
                    strParams += string.Format("const {0} &{1}", ToTargetTypeName(param), InParamName(param.Name));
                }
            }

            return strParams;
        }


        public virtual string ParamArgument(Parameter[] parameter)
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

                if (IsStrType(param)) // string type
                {
                    strParams += string.Format("{0}", InParamName(param.Name));
                }
                else if (param.IsArray) // array
                {
                    strParams += string.Format("{0}", InParamName(param.Name));
                }
                else if (IsVariableSizeType(param))
                {
                    strParams += string.Format("{0}", InParamName(param.Name));
                }
                else // generic type
                {
                    strParams += string.Format("{0}", InParamName(param.Name));
                }
            }

            return strParams;
        }  // 


    }

}
