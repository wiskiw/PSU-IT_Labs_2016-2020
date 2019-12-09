package com.example.pms_lab2;

import android.os.Bundle;
import android.widget.Button;
import android.widget.TabHost;
import androidx.appcompat.app.AppCompatActivity;

public class SamplesActivity extends AppCompatActivity {

    private static final String LL1_TAB_TAG = "ll_1_tab";
    private static final String LL2_TAB_TAG = "ll_2_tab";
    private static final String LL3_TAB_TAG = "ll_3_tab";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_samples);
        setTitle("Купоны желаний - Tab Widget");

        TabHost tabHost = findViewById(R.id.tabHost);
        tabHost.setup();

        TabHost.TabSpec tabSpec = tabHost.newTabSpec(LL1_TAB_TAG);
        tabSpec.setContent(R.id.linearLayout);
        tabSpec.setIndicator("Пример 1");
        tabHost.addTab(tabSpec);

        tabSpec = tabHost.newTabSpec(LL2_TAB_TAG);
        tabSpec.setContent(R.id.linearLayout2);
        tabSpec.setIndicator("Пример 2");
        tabHost.addTab(tabSpec);

        tabSpec = tabHost.newTabSpec(LL3_TAB_TAG);
        tabSpec.setContent(R.id.linearLayout3);
        tabSpec.setIndicator("Пример 3");
        tabHost.addTab(tabSpec);

        tabHost.setCurrentTab(0);

        Button menu = findViewById(R.id.menu);
        menu.setOnClickListener(new StartActivityClickListener(this, MainActivity.class));

        Button search = findViewById(R.id.search);
        search.setOnClickListener(new StartActivityClickListener(this, SearchActivity.class));

        Button webView = findViewById(R.id.webView);
        webView.setOnClickListener(new StartActivityClickListener(this, WebViewActivity.class));
    }

}
