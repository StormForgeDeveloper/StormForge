////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : ActorMovement interface
//	
//
////////////////////////////////////////////////////////////////////////////////

using System;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using System.Text;
#if UNITY_IOS
using AOT;
#endif

#nullable enable

namespace SF
{
    public class ActorMovementObject : SFObject
    {

        public static UInt32 FramesPerSeconds { get { return NativeGetFramesPerSeconds(); } }
        public static UInt32 DeltaMSPerFrame { get { return NativeGetDeltaMSPerFrame(); } }
        public static float DeltaSecondsPerFrame { get { return NativeGetDeltaSecondsPerFrame(); } }
        public static float MoveFrameTimeoutSeconds { get { return NativeGetMoveFrameTimeoutSeconds(); } }
        public static UInt32 MoveFrameTimeout { get { return NativeGetMoveFrameTimeout(); } }

        ////////////////////////////////////////////////////////////////////////////////
        //
        //	Native interfaces
        //

        #region Native interfaces

        const string NativeDLLName =
#if UNITY_IOS
            "__Internal";
#else
            "SFEngineDLL";
#endif

        [DllImport(NativeDLLName, EntryPoint = "SFActorMovement_NativeGetFramesPerSeconds", CharSet = CharSet.Auto)]
        static extern UInt32 NativeGetFramesPerSeconds();

        [DllImport(NativeDLLName, EntryPoint = "SFActorMovement_NativeGetDeltaMSPerFrame", CharSet = CharSet.Auto)]
        static extern UInt32 NativeGetDeltaMSPerFrame();

        [DllImport(NativeDLLName, EntryPoint = "SFActorMovement_NativeGetDeltaSecondsPerFrame", CharSet = CharSet.Auto)]
        static extern float NativeGetDeltaSecondsPerFrame();

        [DllImport(NativeDLLName, EntryPoint = "SFActorMovement_NativeGetMoveFrameTimeoutSeconds", CharSet = CharSet.Auto)]
        static extern float NativeGetMoveFrameTimeoutSeconds();

        [DllImport(NativeDLLName, EntryPoint = "SFActorMovement_NativeGetMoveFrameTimeout", CharSet = CharSet.Auto)]
        static extern UInt32 NativeGetMoveFrameTimeout();

        #endregion
    }
}

#nullable restore
