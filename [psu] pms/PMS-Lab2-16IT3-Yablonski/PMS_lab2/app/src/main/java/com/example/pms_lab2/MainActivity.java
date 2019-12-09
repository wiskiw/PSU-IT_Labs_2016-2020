package com.example.pms_lab2;

import android.os.Bundle;
import android.widget.Button;
import androidx.appcompat.app.AppCompatActivity;


public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        setTitle("Меню - Linear Layout");

        Button search = findViewById(R.id.search);
        search.setOnClickListener(new StartActivityClickListener(this, SearchActivity.class));

        Button samples = findViewById(R.id.samples);
        samples.setOnClickListener(new StartActivityClickListener(this, SamplesActivity.class));

        Button webView = findViewById(R.id.webView);
        webView.setOnClickListener(new StartActivityClickListener(this, WebViewActivity.class));
    }

}
