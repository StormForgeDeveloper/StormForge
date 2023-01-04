////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Debugger
//	
//
////////////////////////////////////////////////////////////////////////////////

#include "SFTypedefs.h"


#pragma once


namespace SF
{

    class Debugger
    {
    public:
        // check if debugger is attached
        static bool IsAttached();

        // wait for debugger is attached
        static void WaitDebuggerAttached();
    };

} // namespace SF


