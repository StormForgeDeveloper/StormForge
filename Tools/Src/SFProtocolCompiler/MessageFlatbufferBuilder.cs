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
            IsCPPOut = true;
        }

        public override bool GenParameterContext => false;

        public string OutputDocName()
        {
            return Group.Name + ".fbs";
        }

        void BuildPrefix()
        {
            var includeSet = AppConfig.GetValueSet("include");
            foreach (var include in includeSet)
            {
                OutStream.WriteLine($"include \"{include.Key}\";");
            }

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
                    if (parameter == ParamResult)
                    {
                        continue;
                    }

                    MatchIndent(); OutStream.WriteLine($"{FlatbufferUtil.ToFlatVariableName(parameter.Name)}:{FlatbufferUtil.ToFlatType(parameter)};");
                }
            }

            CloseSection();
            NewLine();
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
