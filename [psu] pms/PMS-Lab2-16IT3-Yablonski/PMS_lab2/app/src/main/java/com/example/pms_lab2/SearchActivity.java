package com.example.pms_lab2;

import android.os.Bundle;
import android.widget.Button;
import androidx.appcompat.app.AppCompatActivity;

public class SearchActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_search);

        setTitle("Поиск - LinearLayout");


        Button menu = findViewById(R.id.menu);
        menu.setOnClickListener(new StartActivityClickListener(this, MainActivity.class));

        Button samples = findViewById(R.id.samples);
        samples.setOnClickListener(new StartActivityClickListener(this, SamplesActivity.class));

        Button webView = findViewById(R.id.webView);
        webView.setOnClickListener(new StartActivityClickListener(this, WebViewActivity.class));


    }
}
