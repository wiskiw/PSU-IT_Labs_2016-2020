package com.example.pms_lab2;

import android.graphics.Bitmap;
import android.os.Bundle;
import android.webkit.WebView;
import android.webkit.WebViewClient;
import android.widget.Button;
import android.widget.Toast;
import androidx.appcompat.app.AppCompatActivity;

public class WebViewActivity extends AppCompatActivity {

    private static final String DESTINATION_URL = "https://google.com";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_webview);
        setTitle("Оформить заказ - WebView");

        WebView webView = findViewById(R.id.webView);
        webView.setWebViewClient(webViewClient);
        webView.loadUrl(DESTINATION_URL);

        Button menu = findViewById(R.id.menu);
        menu.setOnClickListener(new StartActivityClickListener(this, MainActivity.class));

        Button search = findViewById(R.id.search);
        search.setOnClickListener(new StartActivityClickListener(this, SearchActivity.class));

        Button samples = findViewById(R.id.samples);
        samples.setOnClickListener(new StartActivityClickListener(this, WebViewActivity.class));
    }

    private WebViewClient webViewClient = new WebViewClient() {

        @Override
        public boolean shouldOverrideUrlLoading(WebView view, String url) {
            view.loadUrl(url);
            return true;
        }

        @Override
        public void onPageFinished(WebView view, String url) {
            super.onPageFinished(view, url);
            Toast.makeText(getApplicationContext(), "Done.", Toast.LENGTH_SHORT).show();
        }

        @Override
        public void onPageStarted(WebView view, String url, Bitmap favicon) {
            super.onPageStarted(view, url, favicon);
            Toast.makeText(getApplicationContext(), "Loading...", Toast.LENGTH_SHORT).show();
        }
    };

}
