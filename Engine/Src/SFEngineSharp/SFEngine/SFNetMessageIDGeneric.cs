////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2017 StromForge
// 
// Author : Generated
// 
// Description : Generic Message IDs
// 
////////////////////////////////////////////////////////////////////////////////


using System;
using System.Diagnostics;
using System.Runtime.InteropServices;
using SF;



namespace SF.Net
{
 

	public partial class MessageIDGeneric
	{
 		const string NativeDLLName = 
		#if UNITY_IOS
		    "__Internal";
		#else
		    "SFEngineDLL";
		#endif
		// Cmd: Generic failure message
		public static int GenericFailureCmd { get { return CSSFNetMessageID_GenericGenericFailureCmd(); } }

		public static int GenericFailureRes { get { return CSSFNetMessageID_GenericGenericFailureRes(); } }


		#region Native Interfaces 
		// Cmd: Generic failure message
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_GenericGenericFailureCmd", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_GenericGenericFailureCmd();


		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_GenericGenericFailureRes", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_GenericGenericFailureRes();



		#endregion //Native Interfaces 
	}; // public partial class MessageIDGeneric




} // namespace SF.Net


