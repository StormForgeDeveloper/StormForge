
package com.TestNet;

import java.lang.*;

class TestNetInterface
{
	public native void Initialize();
	public native void Deinitialize();
	public native void Connect(String address, int port);
	public native void RequestRanking();


	static {
      System.loadLibrary("TestNet_AndroidLib");
   }
}
