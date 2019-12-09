package com.example.pms_lab2_task1;

import android.app.ListActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.TextView;
import android.widget.Toast;

public class MainActivity extends ListActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        //setContentView(R.layout.activity_main);

        String[] stationsArray = getResources().getStringArray(R.array.stations);

        ArrayAdapter<String> listAdapter = new ArrayAdapter<>(this, R.layout.list_item, stationsArray);
        setListAdapter(listAdapter);

        getListView().setOnItemClickListener(new AdapterView.OnItemClickListener() {
            @Override
            public void onItemClick(AdapterView<?> adapterView, View view, int i, long l) {
                CharSequence text = ((TextView) view).getText();
                Toast.makeText(view.getContext(), text, Toast.LENGTH_LONG).show();
            }
        });
    }
}