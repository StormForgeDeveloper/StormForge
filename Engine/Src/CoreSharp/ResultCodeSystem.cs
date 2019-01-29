////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Auto generated file, System
//
////////////////////////////////////////////////////////////////////////////////

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml.Serialization;


namespace SF {
	public partial struct ResultCode {

		// Success 
		public static readonly ResultCode S_OK = new ResultCode(unchecked((int)0x00000000)); 

		// Success 
		public static readonly ResultCode S_FALSE = new ResultCode(unchecked((int)0x00000001)); 

		// Invalid pointer 
		public static readonly ResultCode E_POINTER = new ResultCode(unchecked((int)0xC0000002)); 

		// Fail 
		public static readonly ResultCode E_FAIL = new ResultCode(unchecked((int)0xC0000003)); 

		// Not implemented 
		public static readonly ResultCode E_NOTIMPL = new ResultCode(unchecked((int)0xC0000004)); 

		// Out of memory 
		public static readonly ResultCode E_OUTOFMEMORY = new ResultCode(unchecked((int)0xC0000005)); 

		// Unexpected 
		public static readonly ResultCode E_UNEXPECTED = new ResultCode(unchecked((int)0xC0000006)); 

		// Invalid argument 
		public static readonly ResultCode E_INVALIDARG = new ResultCode(unchecked((int)0xC0000007)); 

	}
}


