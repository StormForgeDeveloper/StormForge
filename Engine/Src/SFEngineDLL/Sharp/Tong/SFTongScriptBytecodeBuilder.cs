////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2018 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Tong script byte code interface
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

namespace SF.Tong.Compiler
{


    public class BytecodeBuilder : IDisposable
    {
        public UIntPtr NativeHandle { get; private set; }

        public BytecodeBuilder()
        {
            // Don't use constructor of SFObject, it will increase reference count of the object
            NativeHandle = NativeCreate();
        }

        public void Dispose()
        {
            NativeDelete(NativeHandle);
            NativeHandle = UIntPtr.Zero;
        }



        public void AppendNoop()
        {
            NativeAppendNoop(NativeHandle);
        }

        public void AppendLabel(FixedString32 label)
        {
            NativeAppendLabel(NativeHandle, label.StringHash);
        }

        public void AppendExit()
        {
            NativeAppendExit(NativeHandle);
        }

        public void AppendAdd()
        {
            NativeAppendAdd(NativeHandle);
        }

        public void AppendMul()
        {
            NativeAppendMul(NativeHandle);
        }

        public void AppendSub()
        {
            NativeAppendSub(NativeHandle);
        }

        public void AppendDiv()
        {
            NativeAppendDiv(NativeHandle);
        }

        public void AppendAddI(int value)
        {
            NativeAppendAddI(NativeHandle, value);
        }

        public void AppendMulI(int value)
        {
            NativeAppendMulI(NativeHandle, value);
        }

        public void AppendSubI(int value)
        {
            NativeAppendSubI(NativeHandle, value);
        }

        public void AppendDivI(int value)
        {
            NativeAppendDivI(NativeHandle, value);
        }

        public void AppendAddF(float value)
        {
            NativeAppendAddF(NativeHandle, value);
        }

        public void AppendMulF(float value)
        {
            NativeAppendMulF(NativeHandle, value);
        }

        public void AppendSubF(float value)
        {
            NativeAppendSubF(NativeHandle, value);
        }

        public void AppendDivF(float value)
        {
            NativeAppendDivF(NativeHandle, value);
        }

        public void AppendCmpEqual()
        {
            NativeAppendCmpEqual(NativeHandle);
        }

        public void AppendCmpGreater()
        {
            NativeAppendCmpGreater(NativeHandle);
        }

        public void AppendCmpLess()
        {
            NativeAppendCmpLess(NativeHandle);
        }

        public void AppendCmpGreaterOrEqual()
        {
            NativeAppendCmpGreaterOrEqual(NativeHandle);
        }

        public void AppendCmpLessOrEqual()
        {
            NativeAppendCmpLessOrEqual(NativeHandle);
        }

        public void AppendJump(FixedString32 label)
        {
            NativeAppendJump(NativeHandle, label.StringHash);
        }

        public void AppendJumpFalse(FixedString32 label)
        {
            NativeAppendJumpFalse(NativeHandle, label.StringHash);
        }

        public void AppendYieldFrame()
        {
            NativeAppendYieldFrame(NativeHandle);
        }

        public void AppendStoreToContext(string name)
        {
            NativeAppendStoreToContext(NativeHandle, name);
        }

        public void AppendStore(string path)
        {
            NativeAppendStore(NativeHandle, path);
        }

        public void AppendLoadI(int value)
        {
            NativeAppendLoadI(NativeHandle, value);
        }

        public void AppendLoadF(float value)
        {
            NativeAppendLoadF(NativeHandle, value);
        }

        public void AppendLoadString(string value)
        {
            throw new Exception("TODO: Not supported yet");
            //NativeAppendLoadI(NativeHandle, value);
        }

        public void AppendLoad(string path)
        {
            NativeAppendLoad(NativeHandle, path);
        }

        public void AppendMoveToContext(string name)
        {
            NativeAppendMoveToContext(NativeHandle, name);
        }

        public void AppendMove(string path)
        {
            NativeAppendMove(NativeHandle, path);
        }

        public void AppendCall(string funcName)
        {
            NativeAppendCall(NativeHandle, funcName);
        }




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

        [DllImport(NativeDLLName, EntryPoint = "SFTongScriptByteCode_NativeCreate", CharSet = CharSet.Auto)]
        static extern UIntPtr NativeCreate();
        
        [DllImport(NativeDLLName, EntryPoint = "SFTongScriptByteCode_NativeDelete", CharSet = CharSet.Auto)]
        static extern void NativeDelete(UIntPtr nativeHandle);

        [DllImport(NativeDLLName, EntryPoint = "SFTongScriptByteCode_NativeAppendNoop", CharSet = CharSet.Auto)]
        static extern UInt32 NativeAppendNoop(UIntPtr nativeHandle);

        [DllImport(NativeDLLName, EntryPoint = "SFTongScriptByteCode_NativeAppendLabel", CharSet = CharSet.Auto)]
        static extern UInt32 NativeAppendLabel(UIntPtr nativeHandle, UInt32 labelCrc32);

        [DllImport(NativeDLLName, EntryPoint = "SFTongScriptByteCode_NativeAppendExit", CharSet = CharSet.Auto)]
        static extern UInt32 NativeAppendExit(UIntPtr nativeHandle);

        [DllImport(NativeDLLName, EntryPoint = "SFTongScriptByteCode_NativeAppendAdd", CharSet = CharSet.Auto)]
        static extern UInt32 NativeAppendAdd(UIntPtr nativeHandle);

        [DllImport(NativeDLLName, EntryPoint = "SFTongScriptByteCode_NativeAppendMul", CharSet = CharSet.Auto)]
        static extern UInt32 NativeAppendMul(UIntPtr nativeHandle);

        [DllImport(NativeDLLName, EntryPoint = "SFTongScriptByteCode_NativeAppendSub", CharSet = CharSet.Auto)]
        static extern UInt32 NativeAppendSub(UIntPtr nativeHandle);

        [DllImport(NativeDLLName, EntryPoint = "SFTongScriptByteCode_NativeAppendDiv", CharSet = CharSet.Auto)]
        static extern UInt32 NativeAppendDiv(UIntPtr nativeHandle);

        [DllImport(NativeDLLName, EntryPoint = "SFTongScriptByteCode_NativeAppendAddI", CharSet = CharSet.Auto)]
        static extern UInt32 NativeAppendAddI(UIntPtr nativeHandle, Int32 value);

        [DllImport(NativeDLLName, EntryPoint = "SFTongScriptByteCode_NativeAppendMulI", CharSet = CharSet.Auto)]
        static extern UInt32 NativeAppendMulI(UIntPtr nativeHandle, Int32 value);

        [DllImport(NativeDLLName, EntryPoint = "SFTongScriptByteCode_NativeAppendSubI", CharSet = CharSet.Auto)]
        static extern UInt32 NativeAppendSubI(UIntPtr nativeHandle, Int32 value);

        [DllImport(NativeDLLName, EntryPoint = "SFTongScriptByteCode_NativeAppendDivI", CharSet = CharSet.Auto)]
        static extern UInt32 NativeAppendDivI(UIntPtr nativeHandle, Int32 value);

        [DllImport(NativeDLLName, EntryPoint = "SFTongScriptByteCode_NativeAppendAddF", CharSet = CharSet.Auto)]
        static extern UInt32 NativeAppendAddF(UIntPtr nativeHandle, float value);

        [DllImport(NativeDLLName, EntryPoint = "SFTongScriptByteCode_NativeAppendMulF", CharSet = CharSet.Auto)]
        static extern UInt32 NativeAppendMulF(UIntPtr nativeHandle, float value);

        [DllImport(NativeDLLName, EntryPoint = "SFTongScriptByteCode_NativeAppendSubF", CharSet = CharSet.Auto)]
        static extern UInt32 NativeAppendSubF(UIntPtr nativeHandle, float value);

        [DllImport(NativeDLLName, EntryPoint = "SFTongScriptByteCode_NativeAppendDivF", CharSet = CharSet.Auto)]
        static extern UInt32 NativeAppendDivF(UIntPtr nativeHandle, float value);

        [DllImport(NativeDLLName, EntryPoint = "SFTongScriptByteCode_NativeAppendCmpEqual", CharSet = CharSet.Auto)]
        static extern UInt32 NativeAppendCmpEqual(UIntPtr nativeHandle);

        [DllImport(NativeDLLName, EntryPoint = "SFTongScriptByteCode_NativeAppendCmpGreater", CharSet = CharSet.Auto)]
        static extern UInt32 NativeAppendCmpGreater(UIntPtr nativeHandle);

        [DllImport(NativeDLLName, EntryPoint = "SFTongScriptByteCode_NativeAppendCmpLess", CharSet = CharSet.Auto)]
        static extern UInt32 NativeAppendCmpLess(UIntPtr nativeHandle);

        [DllImport(NativeDLLName, EntryPoint = "SFTongScriptByteCode_NativeAppendCmpGreaterOrEqual", CharSet = CharSet.Auto)]
        static extern UInt32 NativeAppendCmpGreaterOrEqual(UIntPtr nativeHandle);

        [DllImport(NativeDLLName, EntryPoint = "SFTongScriptByteCode_NativeAppendCmpLessOrEqual", CharSet = CharSet.Auto)]
        static extern UInt32 NativeAppendCmpLessOrEqual(UIntPtr nativeHandle);

        [DllImport(NativeDLLName, EntryPoint = "SFTongScriptByteCode_NativeAppendJump", CharSet = CharSet.Auto)]
        static extern UInt32 NativeAppendJump(UIntPtr nativeHandle, UInt32 label);

        [DllImport(NativeDLLName, EntryPoint = "SFTongScriptByteCode_NativeAppendJumpFalse", CharSet = CharSet.Auto)]
        static extern UInt32 NativeAppendJumpFalse(UIntPtr nativeHandle, UInt32 label);

        [DllImport(NativeDLLName, EntryPoint = "SFTongScriptByteCode_NativeAppendYieldFrame", CharSet = CharSet.Auto)]
        static extern UInt32 NativeAppendYieldFrame(UIntPtr nativeHandle);

        [DllImport(NativeDLLName, EntryPoint = "SFTongScriptByteCode_NativeAppendStoreToContext", CharSet = CharSet.Auto)]
        static extern UInt32 NativeAppendStoreToContext(UIntPtr nativeHandle, [MarshalAs(UnmanagedType.LPStr)] string name);

        [DllImport(NativeDLLName, EntryPoint = "SFTongScriptByteCode_NativeAppendStore", CharSet = CharSet.Auto)]
        static extern UInt32 NativeAppendStore(UIntPtr nativeHandle, [MarshalAs(UnmanagedType.LPStr)] string path);

        [DllImport(NativeDLLName, EntryPoint = "SFTongScriptByteCode_NativeAppendLoadI", CharSet = CharSet.Auto)]
        static extern UInt32 NativeAppendLoadI(UIntPtr nativeHandle, Int32 value);

        [DllImport(NativeDLLName, EntryPoint = "SFTongScriptByteCode_NativeAppendLoadF", CharSet = CharSet.Auto)]
        static extern UInt32 NativeAppendLoadF(UIntPtr nativeHandle, float value);

        [DllImport(NativeDLLName, EntryPoint = "SFTongScriptByteCode_NativeAppendLoad", CharSet = CharSet.Auto)]
        static extern UInt32 NativeAppendLoad(UIntPtr nativeHandle, [MarshalAs(UnmanagedType.LPStr)] string path);

        [DllImport(NativeDLLName, EntryPoint = "SFTongScriptByteCode_NativeAppendMoveToContext", CharSet = CharSet.Auto)]
        static extern UInt32 NativeAppendMoveToContext(UIntPtr nativeHandle, [MarshalAs(UnmanagedType.LPStr)] string name);

        [DllImport(NativeDLLName, EntryPoint = "SFTongScriptByteCode_NativeAppendMove", CharSet = CharSet.Auto)]
        static extern UInt32 NativeAppendMove(UIntPtr nativeHandle, [MarshalAs(UnmanagedType.LPStr)] string path);

        [DllImport(NativeDLLName, EntryPoint = "SFTongScriptByteCode_NativeAppendCall", CharSet = CharSet.Auto)]
        static extern UInt32 NativeAppendCall(UIntPtr nativeHandle, [MarshalAs(UnmanagedType.LPStr)] string path);

        #endregion
    }
}