package com.example.pms_lab4;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;
import android.widget.Toast;
import androidx.appcompat.app.AppCompatActivity;

public class MainActivity extends AppCompatActivity {

    public static final String COMMON_STATION_RESULT_KEY = "station";
    private static final int STATION_REQUEST_CODE = 55;

    public TextView station;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        setContentView(R.layout.activity_main);
        station = findViewById(R.id.station);

        Toast.makeText(this, getIntent().getAction(), Toast.LENGTH_SHORT).show();

        Button getStations = findViewById(R.id.get_stations);
        getStations.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Intent stations = new Intent("com.example.pms_lab4.PICK_METRO_STATION");
                startActivityForResult(stations, STATION_REQUEST_CODE);
            }
        });

        Button getStationsTwo = findViewById(R.id.get_stations_two);
        getStationsTwo.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Intent stationsTwo = new Intent(MainActivity.this, StationsActivityTwo.class);
                startActivityForResult(stationsTwo, STATION_REQUEST_CODE);
            }
        });
    }

    @Override
    public void onActivityResult(int requestCode, int resultCode, Intent data) {
        switch (requestCode) {
            case STATION_REQUEST_CODE:
                onStationResult(resultCode, data);
                break;
        }
    }

    private void onStationResult(int resultCode, Intent data) {
        switch (resultCode) {
            case RESULT_OK:
                station.setText(data.getStringExtra(COMMON_STATION_RESULT_KEY ));
                break;

            case RESULT_CANCELED:
                station.setText(R.string.default_station);
                break;
        }
    }
}
