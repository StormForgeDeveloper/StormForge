
package com.TestNet_Android;


import android.app.Activity;
import android.widget.*;
import android.view.*;
import android.os.Bundle;
import android.util.Log;
import java.util.Timer;
import java.util.TimerTask;

import com.TestNet.TestNetInterface;


public class TestNet_Android extends Activity
{
	TestNetInterface m_TestInterface = null;

	//String m_Address = "192.168.0.100";
	String m_Address = "112.169.214.196";
	int m_Port = 21001;

    /** Called when the activity is first created. */
    @Override
    public void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);

        setContentView(R.layout.main_layout);

		Button btnConnect = (Button) findViewById(R.id.btnConnect);
		btnConnect.setOnClickListener( new View.OnClickListener() {

            @Override
            public void onClick(View v) {
				if(m_TestInterface == null) 
					return;

                m_TestInterface.Connect(m_Address, m_Port);
            }
        });
		
		Button btnRanking = (Button) findViewById(R.id.btnRanking);
		btnRanking.setOnClickListener( new View.OnClickListener() {

            @Override
            public void onClick(View v) {
				if(m_TestInterface == null) 
					return;

                m_TestInterface.RequestRanking();
            }
        });
    }
		
	@Override
    protected void onStart()
    {
        super.onStart();

		if(m_TestInterface != null) 
			return;

		Log.v("TestNet", "OnStart");
		m_TestInterface = new TestNetInterface();
		Log.v("TestNet", "OnStart2");
		m_TestInterface.Initialize();
		Log.v("TestNet", "OnStart3");
    }

	@Override
    protected void onStop()
    {
		if(m_TestInterface != null)
			m_TestInterface.Deinitialize();
		m_TestInterface = null;

        super.onStop();
    }


}
