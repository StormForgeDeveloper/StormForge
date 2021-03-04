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

		public const int SUCCESS =                              0;
        public const int SUCCESS_FALSE =                        1;
        public const int SUCCESS_YIELD = 2;
        public const int INVALID_POINTER =                      unchecked((int)0xC0000002L);
        public const int FAIL=                                 unchecked((int)0xC0000003L);
        public const int NOT_IMPLEMENTED =                     unchecked((int)0xC0000004L);
        public const int OUT_OF_MEMORY =                       unchecked((int)0xC0000005L);
        public const int UNEXPECTED =                          unchecked((int)0xC0000006L);
        public const int INVALID_ARG =                          unchecked((int)0xC0000007L);
        public const int NO_DATA_EXIST =                        unchecked((int)0xC0000008L);

    }
}



