
package com.SF;

import java.lang.*;
import android.content.res.*;


public class SFEngine
{
	private long m_NativeHandle = 0;


	public SFEngine()
	{
	}

	public void StartEngine()
	{
		if(m_NativeHandle != 0)
			return;
		m_NativeHandle = NativeStartEngineEmpty();
	}

	public void StartEngine(AssetManager assetManager)
	{
		if(m_NativeHandle != 0)
			return;
		m_NativeHandle = NativeStartEngine(assetManager);
	}

	public void StopEngine()
	{
		if(m_NativeHandle == 0)
			return;

		NativeStopEngine();
		m_NativeHandle = 0;
	}


	private native long NativeStartEngine(AssetManager assetManager);
	private native long NativeStartEngineEmpty();
	private native void NativeStopEngine();
	private native void NativeConfigChanged(Configuration config);
	private native void NativeFocused(boolean focused);
	private native void NativeSurfaceCreated(Object surface);
	private native void NativeSurfaceDestroyed(Object surface);


	static {
      System.loadLibrary("SFEngineDLL");
   }
}
