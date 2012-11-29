package fr.enseirb.odroidx;

import android.app.Activity;
import android.os.Bundle;
import android.util.Log;

public class MainActivity extends Activity {

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.mainactivity_layout);
		DashManager manager = new DashManager();
		int ret = manager.openStream("http://testaddress.fr");
		Log.e("DEBUG", String.valueOf(ret));
	}
	
}
