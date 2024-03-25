////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : System default result codes
//
////////////////////////////////////////////////////////////////////////////////

using System;


namespace SF {
	public partial struct ResultCode {

        public const int _SUCCESS = 0;
        public static readonly Result SUCCESS =                              new Result(0);
        public static readonly Result SUCCESS_FALSE = new Result(1);
        public static readonly Result SUCCESS_YIELD = new Result(2);
        public static readonly Result INVALID_POINTER = new Result(unchecked((int)0xC0000002L));
        public static readonly Result FAIL= new Result(unchecked((int)0xC0000003L));
        public static readonly Result NOT_IMPLEMENTED = new Result(unchecked((int)0xC0000004L));
        public static readonly Result OUT_OF_MEMORY = new Result(unchecked((int)0xC0000005L));
        public static readonly Result UNEXPECTED = new Result(unchecked((int)0xC0000006L));
        public static readonly Result INVALID_ARG = new Result(unchecked((int)0xC0000007L));
        public static readonly Result NO_DATA_EXIST = new Result(unchecked((int)0xC0001008L));

    }
}



