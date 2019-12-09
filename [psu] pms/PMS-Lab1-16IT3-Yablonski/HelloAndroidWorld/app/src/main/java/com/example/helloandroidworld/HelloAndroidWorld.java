package com.example.helloandroidworld;

import androidx.appcompat.app.AppCompatActivity;
import android.widget.Toast;
import android.os.Bundle;

public class HelloAndroidWorld extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        Toast.makeText(this, "onCreate()", Toast.LENGTH_LONG).show();
    }

    @Override
    protected void onPause() {
        Toast.makeText(this, "onPause()", Toast.LENGTH_LONG).show();
        super.onPause();
    }

    @Override
    protected void onRestart() {
        super.onRestart();
        Toast.makeText(this, "onRestart()", Toast.LENGTH_LONG).show();
    }

    @Override
    protected void onStart() {
        super.onStart();
        Toast.makeText(this, "onStart()", Toast.LENGTH_LONG).show();
    }
}