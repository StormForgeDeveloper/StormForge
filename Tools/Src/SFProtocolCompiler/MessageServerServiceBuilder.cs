////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Server service Builder
//
////////////////////////////////////////////////////////////////////////////////


using System;
using System.Collections.Generic;
using System.Text;
using ProtocolXml;

namespace ProtocolCompiler
{
    class MessageServerServiceBuilder : Builder
    {
        Parameter m_ParameterRouteHopContext;

        Parameter m_ParamSenderEntityID;

        // constructor
        public MessageServerServiceBuilder(string strBasePath)
            : base(strBasePath+"ServerService")
        {
            GenParameterRouteHopCount = true;
            m_ParameterRouteHopContext = ParamRouteContext;
            ParamRouteContext = null;

            m_ParamSenderEntityID = new Parameter();
            m_ParamSenderEntityID.IsArray = false;
            m_ParamSenderEntityID.IsArraySpecified = false;
            m_ParamSenderEntityID.Name = "SenderEntityID";
            m_ParamSenderEntityID.Type = ParameterType.EntityID;

        }


        public virtual string OutputHeaderName { get { return Group.Name + "Service.h"; } }
        public virtual string OutputCppName { get { return Group.Name + "Service.cpp"; } }
        public virtual string ServiceClassName { get { return Group.Name + "Service"; } }

        public virtual string NetInterfaceString { get { return "Policy::NetPolicy" + Group.Name + "(GetConnection())"; } }

        public virtual string BasePolicyHeaderName { get { return Group.Name + "NetPolicy.h"; } }

        //public virtual string SvrPolicyClassName { get { return "NetSvrPolicy" + Group.Name; } }


        protected virtual void BuildHPrefix()
        {
            OutStream.WriteLine("////////////////////////////////////////////////////////////////////////////////");
            OutStream.WriteLine("// ");
            OutStream.WriteLine("// CopyRight (c) 2016 Kyungkun Ko");
            OutStream.WriteLine("// ");
            OutStream.WriteLine("// Author : Generated");
            OutStream.WriteLine("// ");
            OutStream.WriteLine("// Description : {0} Service definitions", Group.Name);
            OutStream.WriteLine("// ");
            OutStream.WriteLine("////////////////////////////////////////////////////////////////////////////////");
            OutStream.WriteLine("");
            OutStream.WriteLine("#pragma once");
            OutStream.WriteLine("");
            OutStream.WriteLine("#include \"SFTypedefs.h\"");
            OutStream.WriteLine("#include \"Protocol/SFProtocol.h\"");
            OutStream.WriteLine("#include \"ServerService/ServerServiceBase.h\"");

            OutStream.WriteLine("#include \"Net/SFNetDef.h\"");
            OutStream.WriteLine("#include \"Protocol/Policy/{0}\"", BasePolicyHeaderName);
            NewLine(3);

            // namespace definition
            OpenSection("namespace", "SF");
            OpenSection("namespace", "Svr");
        }


        void BuildCPPPrefix()
        {
            OutStream.WriteLine("////////////////////////////////////////////////////////////////////////////////");
            OutStream.WriteLine("// ");
            OutStream.WriteLine("// CopyRight (c) 2016 Kyungkun Ko");
            OutStream.WriteLine("// ");
            OutStream.WriteLine("// Author : Generated");
            OutStream.WriteLine("// ");
            OutStream.WriteLine("// Description : {0} Message debug implementations", Group.Name);
            OutStream.WriteLine("// ");
            OutStream.WriteLine("////////////////////////////////////////////////////////////////////////////////");
            OutStream.WriteLine("");
            OutStream.WriteLine("");
            OutStream.WriteLine("#include \"{0}\"", PreCompiledHeader);
            OutStream.WriteLine("#include \"SFTypedefs.h\"");
            OutStream.WriteLine("#include \"Protocol/SFProtocol.h\"");
            OutStream.WriteLine("#include \"ServerEntity/ServerEntity.h\"");
            OutStream.WriteLine("#include \"Server/BrServer.h\"");
            OutStream.WriteLine("#include \"Server/BrServerUtil.h\"");
            OutStream.WriteLine("#include \"Entity/EntityInformation.h\"");
            OutStream.WriteLine("#include \"Protocol/ServerService/{0}\"", OutputHeaderName);
            OutStream.WriteLine("#include \"SvrTrace.h\"");

            NewLine(3);

            // namespace definition
            OpenSection("namespace", PrjPrefix);
            OpenSection("namespace", "Svr");
        }

        protected string ParamString(Parameter[] parameter)
        {
            return ParamInString(parameter);
        }

        Parameter[] MakeParametersForEvent(Parameter[] parameter)
        {
            List<Parameter> list = new List<Parameter>(MakeParameters(MsgType.Evt, parameter));
            list.Insert(0, m_ParamSenderEntityID);
            return list.ToArray();
        }

        protected virtual void BuildServerServiceH()
        {
            Parameter[] newparams;

            OpenSection("class", string.Format("{0} : public ServerServiceBase", ServiceClassName));
            MatchIndent(); OutStream.WriteLine("public:");
            MatchIndent(); OutStream.WriteLine("// Constructor");
            MatchIndent(); OutStream.WriteLine("{0} ( ServerServiceInformation* pService );", ServiceClassName);
            NewLine();

            foreach (MessageBase baseMsg in Group.Items)
            {
                if (baseMsg is ProtocolsProtocolGroupCommand)
                {
                    MatchIndent(); OutStream.WriteLine("// Cmd: " + baseMsg.Desc);
                    ProtocolsProtocolGroupCommand msg = baseMsg as ProtocolsProtocolGroupCommand;

                    newparams = MakeParameters(MsgType.Cmd, msg.Cmd);
                    MatchIndent(); OutStream.WriteLine("Result {0}Cmd( {1} );", msg.Name, ParamString(newparams));
                }

                if (baseMsg is ProtocolsProtocolGroupC2SEvent)
                {
                    MatchIndent(); OutStream.WriteLine("// C2S: " + baseMsg.Desc);
                    ProtocolsProtocolGroupC2SEvent msg = baseMsg as ProtocolsProtocolGroupC2SEvent;

                    if( Group.GenParameterRouteContext )
                        newparams = MakeParametersForEvent(msg.Params);
                    else
                        newparams = MakeParameters(MsgType.Evt, msg.Params);
                    MatchIndent(); OutStream.WriteLine("Result {0}C2SEvt( {1} );", msg.Name, ParamString(newparams));
                }
            }

            NewLine();

            CloseSection();
        }


        // Build parser class implementation
        void BuildServerServiceMethodImpl(MsgType type, Parameter[] originalParameters, string Name, string typeName, Parameter[] parameters)
        {
            OpenSection("Result", string.Format("{0}::{1}{2}( {3} )", ServiceClassName, Name, typeName, ParamInString(parameters)));

            DefaultHRESULT(); NewLine();

            if (Group.GenParameterRouteContext)
            {
                if (type == MsgType.Cmd)
                {
                    MatchIndent(); OutStream.WriteLine("RouteContext InRouteContext( EntityUID(GetMyServerID(),TransactionID(InTransactionID).GetEntityID()), GetServiceEntityUID() );");
                    ParamRouteContext = m_ParameterRouteHopContext;
                    parameters = MakeParameters(type, originalParameters);
                    ParamRouteContext = null;

                    MatchIndent(); OutStream.WriteLine("svrCheck({0}.{1}{2}( {3} ) );", NetInterfaceString, Name, typeName, ParamArgument(parameters));
                }
                else if (type == MsgType.Evt)
                {
                    MatchIndent(); OutStream.WriteLine("RouteContext InRouteContext( EntityUID(GetMyServerID(),InSenderEntityID), GetServiceEntityUID() );");
                    ParamRouteContext = m_ParameterRouteHopContext;
                    parameters = MakeParameters(type, originalParameters);
                    ParamRouteContext = null;

                    MatchIndent(); OutStream.WriteLine("svrCheck({0}.{1}{2}( {3} ) );", NetInterfaceString, Name, typeName, ParamArgument(parameters));
                }
            }
            else
            {
                MatchIndent(); OutStream.WriteLine(" svrCheck({0}.{1}{2}( {3} ) );", NetInterfaceString, Name, typeName, ParamArgument(parameters));
            }

            NewLine();
            ReturnHR();
            NewLine();

            CloseSection();
        }

        void BuildServerServiceCPP()
        {

            MatchIndent(); OutStream.WriteLine("{0}::{0}( ServerServiceInformation* pService)", ServiceClassName);
            MatchIndent(1); OutStream.WriteLine(": ServerServiceBase(pService)");
            MatchIndent(); OutStream.WriteLine("{");
            MatchIndent(); OutStream.WriteLine("}");

            NewLine(2);

            Parameter[] newparams;
            foreach (MessageBase baseMsg in Group.Items)
            {
                if (baseMsg is ProtocolsProtocolGroupCommand)
                {
                    MatchIndent(); OutStream.WriteLine("// Cmd: " + baseMsg.Desc);
                    ProtocolsProtocolGroupCommand msg = baseMsg as ProtocolsProtocolGroupCommand;

                    newparams = MakeParameters(MsgType.Cmd, msg.Cmd);
                    BuildServerServiceMethodImpl(MsgType.Cmd, msg.Cmd, msg.Name, "Cmd", newparams);
                }

                if (baseMsg is ProtocolsProtocolGroupC2SEvent)
                {
                    MatchIndent(); OutStream.WriteLine("// C2S: " + baseMsg.Desc);
                    ProtocolsProtocolGroupC2SEvent msg = baseMsg as ProtocolsProtocolGroupC2SEvent;

                    if (Group.GenParameterRouteContext)
                        newparams = MakeParametersForEvent(msg.Params);
                    else
                        newparams = MakeParameters(MsgType.Evt, msg.Params);
                    BuildServerServiceMethodImpl(MsgType.Evt, msg.Params, msg.Name, "C2SEvt", newparams);
                }
            }
        }

        void BuildH()
        {
            // build IParser
            OpenOutFile(OutputHeaderName);

            BuildHPrefix();

            BuildServerServiceH();
            NewLine(2);

            CloseOutFile();
        }

        void BuildCPP()
        {
            OpenOutFile(OutputCppName);

            BuildCPPPrefix();

            BuildServerServiceCPP();
            NewLine(2);

            CloseOutFile();
        }

        public override void Build()
        {
            if (!Group.IsServer)
                return;

            BuildH();
            BuildCPP();
        }

    } //  class MessageIPolicyBuilder : Builder

} // namespace ProtocolCompiler
