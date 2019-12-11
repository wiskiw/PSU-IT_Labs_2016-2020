package com.example.pms_lab4;

import android.app.ListActivity;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.Toast;

public class StationsActivity extends ListActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        final String[] stationsArray = getResources().getStringArray(R.array.stations);
        ArrayAdapter<String> stationsAdapter = new ArrayAdapter<>(this, R.layout.list_item, stationsArray);
        setListAdapter(stationsAdapter);

        getListView().setOnItemClickListener(new AdapterView.OnItemClickListener() {
            @Override
            public void onItemClick(AdapterView<?> adapterView, View view, int position, long l) {
                setStationResult(stationsArray[position]);
                finish();
            }
        });
    }

    private void setStationResult(String station) {
        Intent result = new Intent();
        result.putExtra(MainActivity.COMMON_STATION_RESULT_KEY, station);
        setResult(RESULT_OK, result);
        finish();
    }
}
