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


    abstract class Builder
    {

        public enum MsgType
        {
            NetCtrl,
            Cmd,
            Res,
            Evt
        };

        // Out file base path
        private string m_strBasePath;

        // Output file stream
        FileStream m_OutFile;
        StreamWriter m_OutStream;

        // Tab indent count
        int m_iIndent;

        // Section stack
        Stack<string> m_SectionStack;

        public string BuildYear
        {
            get { return "" + DateTime.Now.Year; }
        }


        // Output file path
        public string BasePath
        {
            get { return m_strBasePath; }
            set { m_strBasePath = value; }
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
        public Builder(string strBasePath)
        {
            IsCPPOut = true;
            IsCSharpNative = false;
            m_iIndent = 0;
            m_SectionStack = new Stack<string>();

            // default turned off so that it will not generate route hop parameter if the group option is off
            m_GenParameterRouteHopCount = true;

            m_strBasePath = strBasePath;


            m_ParamContext = new Parameter();
            m_ParamContext.IsArray = false;
            m_ParamContext.IsArraySpecified = false;
            m_ParamContext.Name = "TransactionID";
            m_ParamContext.Type = ParameterType.TransactionID;

            m_ParamResult = new Parameter();
            m_ParamResult.IsArray = false;
            m_ParamResult.IsArraySpecified = false;
            m_ParamResult.Name = "Result";
            m_ParamResult.Type = ParameterType.Result;

            m_ParamRouteContext = new Parameter();
            m_ParamRouteContext.IsArray = false;
            m_ParamRouteContext.IsArraySpecified = false;
            m_ParamRouteContext.Name = "RouteContext";
            m_ParamRouteContext.Type = ParameterType.RouteContext;

            m_ParamRouteHopCount = new Parameter();
            m_ParamRouteHopCount.IsArray = false;
            m_ParamRouteHopCount.IsArraySpecified = false;
            m_ParamRouteHopCount.Name = "RouteHopCount";
            m_ParamRouteHopCount.Type = ParameterType.uint16;

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

        public void ProcEnd()
        {
            MatchIndent(-1);
            OutStream.WriteLine("Proc_End:");
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
            return param.Type == ParameterType.String;
        }

        public string ArrayLenName(string Name)
        {
            return "uiSizeOf" + Name;
        }

        public virtual string ToTargetTypeName(ParameterType type)
        {
            Type csType = SystemTypeInfo.ToCSharpType(type);
            if (IsCPPOut)
            {
                return SystemTypeInfo.ToCPPType(type);
            }

            if (IsCSharpNative)
            {
                if (csType == typeof(string))
                    return "byte[]";
                else if(IsStruct(csType))
                    return "ref " + csType.ToString();
                else if (IsEnum(csType))
                    return "int";
                else
                    return csType.ToString();
            }

            return csType.ToString();
        }

        public bool IsEnum(Type csType)
        {
            return csType.IsEnum;
        }
        public bool IsStruct(ParameterType type)
        {
            Type csType = SystemTypeInfo.ToCSharpType(type);
            return IsStruct(csType);
        }

        public bool IsStruct(Type csType)
        {
            bool bIsStruct = false;
            foreach (Attribute attribute in Attribute.GetCustomAttributes(csType))
            {
                if (attribute.GetType() == typeof(StructAttribute))
                {
                    bIsStruct = true;
                    break;
                }
            }
            return bIsStruct;
        }

        public string InArrayTypeName(Parameter param)
        {
            return string.Format("Array<{0}>", ToTargetTypeName(param.Type));
        }
        public string OutArrayTypeName(Parameter param)
        {
            return string.Format("ExternalBufferArray<{0}>", ToTargetTypeName(param.Type));
        }


        public string InParamName(string Name)
        {
            return "In" + Name;
        }

        public virtual string PolicyClassName
        {
            get { return "NetPolicy" + Group.Name; }
        }

        // Message parser class name
        public string MsgClassName(string Name, string typeName)
        {
            return string.Format("{0}{1}", Name, typeName);
        }


        public string StrTypeString(Parameter param)
        {
            switch (param.Type)
            {
                case ParameterType.String:
                    return "char*";
                default:
                    return null;
            }
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

        public virtual string ParamInString(Parameter[] parameter)
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
                    strParams += string.Format("const {0} {1}", StrTypeString(param), InParamName(param.Name));
                }
                else if (param.IsArray) // array
                {
                    strParams += string.Format("const {0}& {1}", InArrayTypeName(param), InParamName(param.Name));
                }
                else // generic type
                {
                    strParams += string.Format("const {0} &{1}", ToTargetTypeName(param.Type), InParamName(param.Name));
                }
            }

            return strParams;
        }

        public string ParamOutString(Parameter[] parameter)
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
                    strParams += string.Format("{0} &{1}", StrTypeString(param), "Out" + param.Name);
                }
                else if (param.IsArray) // array
                {
                    strParams += string.Format("{0} &{1}", OutArrayTypeName(param), "Out" + param.Name);
                }
                else // generic type
                {
                    strParams += string.Format("{0} &{1}", ToTargetTypeName(param.Type), "Out" + param.Name);
                }
            }

            return strParams;
        }

        public string ParamArgument(Parameter[] parameter)
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
                else // generic type
                {
                    strParams += string.Format("{0}", InParamName(param.Name));
                }
            }

            return strParams;
        }  // 



    }
}
