﻿////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Autogenerated file, Engine
//
////////////////////////////////////////////////////////////////////////////////

using System;


namespace SF {
	public partial struct ResultCode {

		// Engine initialization is failed 
		 public const int _ENGINE_INITIALIZATION_FAILED = (unchecked((int)0xE7020000)); 
		public static readonly Result ENGINE_INITIALIZATION_FAILED = new Result(_ENGINE_INITIALIZATION_FAILED); 

		// Invalid configuration 
		 public const int _ENGINE_INVALID_CONFIG = (unchecked((int)0xE7020001)); 
		public static readonly Result ENGINE_INVALID_CONFIG = new Result(_ENGINE_INVALID_CONFIG); 

		// Connection failed 
		 public const int _ENGINE_CONNECTION_FAILED = (unchecked((int)0xE7020002)); 
		public static readonly Result ENGINE_CONNECTION_FAILED = new Result(_ENGINE_CONNECTION_FAILED); 

		// Connectionlost 
		 public const int _ENGINE_CONNECTION_LOST = (unchecked((int)0xE7020003)); 
		public static readonly Result ENGINE_CONNECTION_LOST = new Result(_ENGINE_CONNECTION_LOST); 

		// Invalid character data 
		 public const int _ENGINE_INVALID_CHARACTER = (unchecked((int)0xE7020004)); 
		public static readonly Result ENGINE_INVALID_CHARACTER = new Result(_ENGINE_INVALID_CHARACTER); 

		// Invalid table id 
		 public const int _ENGINE_INVALID_TABLE_ID = (unchecked((int)0xE7020005)); 
		public static readonly Result ENGINE_INVALID_TABLE_ID = new Result(_ENGINE_INVALID_TABLE_ID); 

		// Invalid platform 
		 public const int _ENGINE_INVALID_PLATFORM = (unchecked((int)0xE7020006)); 
		public static readonly Result ENGINE_INVALID_PLATFORM = new Result(_ENGINE_INVALID_PLATFORM); 

		// Already Used Item 
		 public const int _ENGINE_ALREADY_USED_ITEM = (unchecked((int)0xE7020007)); 
		public static readonly Result ENGINE_ALREADY_USED_ITEM = new Result(_ENGINE_ALREADY_USED_ITEM); 

		// Already Used Key 
		 public const int _ENGINE_ALREADY_USED_KEY = (unchecked((int)0xE7020008)); 
		public static readonly Result ENGINE_ALREADY_USED_KEY = new Result(_ENGINE_ALREADY_USED_KEY); 

		// Invalid online session. probably kicked 
		 public const int _ENGINE_INVALID_ONLINE_SESSION = (unchecked((int)0xE7020009)); 
		public static readonly Result ENGINE_INVALID_ONLINE_SESSION = new Result(_ENGINE_INVALID_ONLINE_SESSION); 

	}
}



