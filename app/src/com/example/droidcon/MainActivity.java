package com.example.droidcon;

import android.os.Bundle;
import android.app.Activity;
import android.util.Log;
import android.view.Menu;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;

import android.droidcon.DroidconManager;

public class MainActivity extends Activity {

	private DroidconManager mDroidconManager;
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
		
		mDroidconManager = (DroidconManager)this.getSystemService(DROIDCON_SERVICE);
		
		Button btnPut = (Button)findViewById(R.id.button_put);
		btnPut.setOnClickListener(new View.OnClickListener() {
			@Override
			public void onClick(View arg0) {
				EditText et = (EditText)findViewById(R.id.editText1);
				mDroidconManager.putData(et.getText().toString());
			}
		});
		
		Button btnGet = (Button)findViewById(R.id.button_get);
		btnGet.setOnClickListener(new View.OnClickListener() {
			@Override
			public void onClick(View arg0) {
				String str = mDroidconManager.getData();
				TextView tv = (TextView)findViewById(R.id.textView1);
				tv.setText(str);
			}
		});
	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.main, menu);
		return true;
	}

}
