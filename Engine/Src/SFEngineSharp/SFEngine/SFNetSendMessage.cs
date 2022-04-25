////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) StromForge
// 
// Author : Generated
// 
// Description : PlayInstance Network Adapter
// 
////////////////////////////////////////////////////////////////////////////////


using System;
using System.Diagnostics;
using System.Runtime.InteropServices;
using SF;



namespace SF.Net
{
 

	public class SendMessage
	{
 
		protected SF.SFConnection m_Connection;

		public SF.SFConnection Connection { get { return m_Connection; } set { m_Connection = value; } }


		public  SendMessage()
		{
		}

        public SendMessage(SF.SFConnection connection)
        {
            m_Connection = connection;
        }

    };




} // namespace SF.Net


