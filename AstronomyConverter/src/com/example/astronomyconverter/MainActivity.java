package com.example.astronomyconverter;

import java.text.DecimalFormat;

import android.app.Activity;
import android.os.Bundle;
import android.view.Menu;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.EditText;

public class MainActivity extends Activity {

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
		final EditText kmValue = (EditText)findViewById(R.id.km);
		final EditText auValue = (EditText)findViewById(R.id.au);
		final EditText lyValue = (EditText)findViewById(R.id.ly);
		final EditText pcValue = (EditText)findViewById(R.id.pc);
		Button clearButton = (Button)findViewById(R.id.clearButton);
		final Button convertButton = (Button)findViewById(R.id.convertButton);		

		convertButton.setOnClickListener(new OnClickListener() {
			@Override
			public void onClick(View arg0) {
				if (!kmValue.getText().toString().equals("")) {
					double km = Double.valueOf(kmValue.getText().toString());
					double au = km*(6.6845*Math.pow(10, -9));
					double ly = km*(1.0570*Math.pow(10, -13));
					double pc = km*(3.2408*Math.pow(10, -14));
					auValue.setText(String.valueOf(FormatDecimal(au)));
					lyValue.setText(String.valueOf(FormatDecimal(ly)));
					pcValue.setText(String.valueOf(FormatDecimal(pc)));
					kmValue.setFocusableInTouchMode(false);
					auValue.setFocusableInTouchMode(false);
					lyValue.setFocusableInTouchMode(false);
					pcValue.setFocusableInTouchMode(false);
					convertButton.setClickable(false);
				}
				else if (!auValue.getText().toString().equals("")) {
					double au = Double.valueOf(auValue.getText().toString());
					double km = au*(1.4960*Math.pow(10, 9));
					double ly = au*(1.5812*Math.pow(10, -5));
					double pc = au*(4.8482*Math.pow(10, -6));
					kmValue.setText(String.valueOf(FormatDecimal(km)));
					lyValue.setText(String.valueOf(FormatDecimal(ly)));
					pcValue.setText(String.valueOf(FormatDecimal(pc)));
					kmValue.setFocusableInTouchMode(false);
					auValue.setFocusableInTouchMode(false);
					lyValue.setFocusableInTouchMode(false);
					pcValue.setFocusableInTouchMode(false);
					convertButton.setClickable(false);
				}
				else if (!lyValue.getText().toString().equals("")) {
					double ly = Double.valueOf(lyValue.getText().toString());
					double km = ly*(9.4607*Math.pow(10, 12));
					double au = ly*(6.3242*Math.pow(10, 4));
					double pc = ly*(3.0660*Math.pow(10, -1));
					kmValue.setText(String.valueOf(FormatDecimal(km)));
					auValue.setText(String.valueOf(FormatDecimal(au)));
					pcValue.setText(String.valueOf(FormatDecimal(pc)));
					kmValue.setFocusableInTouchMode(false);
					auValue.setFocusableInTouchMode(false);
					lyValue.setFocusableInTouchMode(false);
					pcValue.setFocusableInTouchMode(false);
					convertButton.setClickable(false);
				}
				else if (!pcValue.getText().toString().equals("")) {
					double pc = Double.valueOf(pcValue.getText().toString());
					double km = pc*(3.0857*Math.pow(10, 13));
					double au = pc*(2.0626*Math.pow(10, 5));
					double ly = pc*(3.2615);
					kmValue.setText(String.valueOf(FormatDecimal(km)));
					auValue.setText(String.valueOf(FormatDecimal(au)));
					lyValue.setText(String.valueOf(FormatDecimal(ly)));
					kmValue.setFocusableInTouchMode(false);
					auValue.setFocusableInTouchMode(false);
					lyValue.setFocusableInTouchMode(false);
					pcValue.setFocusableInTouchMode(false);
					convertButton.setClickable(false);
				}
			}
		});
		
		clearButton.setOnClickListener(new OnClickListener() {

			@Override
			public void onClick(View arg0) {
				kmValue.setText(null);
				auValue.setText(null);
				lyValue.setText(null);
				pcValue.setText(null);
				kmValue.setFocusableInTouchMode(true);
				auValue.setFocusableInTouchMode(true);
				lyValue.setFocusableInTouchMode(true);
				pcValue.setFocusableInTouchMode(true);
				convertButton.setClickable(true);
			}
		});
	} // end onCreate
	

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.main, menu);
		return true;
	}
	
	public String FormatDecimal(double value) {
		// scientific notation
		DecimalFormat df = new DecimalFormat("0.0000E0");
		return df.format(value);
	}
}