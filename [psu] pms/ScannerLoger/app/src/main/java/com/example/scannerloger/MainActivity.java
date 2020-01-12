package com.example.scannerloger;

import android.os.Bundle;
import android.os.Environment;
import android.util.Log;
import android.view.MotionEvent;
import android.view.View;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.ListView;
import android.widget.Toast;

import androidx.appcompat.app.AppCompatActivity;

import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

public class MainActivity extends AppCompatActivity {

    private static final String FILE_NAME = "coords_list.txt";

    // Список с координатами(строки)
    private List<String> coordsList = new ArrayList<>();

    // Адаптер для списка, чтобы отображать в ListView
    private ArrayAdapter<String> listAdapter;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // Создание адаптера
        listAdapter = new ArrayAdapter<>(this, R.layout.list_item, coordsList);

        // Поиск и установка обработчика нажатий на "Зеленую область"
        View touchView = findViewById(R.id.touchView);
        touchView.setOnTouchListener(new TouchListener());


        // Поиск и установка обработчика нажатий "Clear"
        Button clear = findViewById(R.id.clear);
        clear.setOnClickListener(new ClearClickListener());

        // Поиск и установка обработчика нажатий "Save"
        Button save = findViewById(R.id.save);
        save.setOnClickListener(new SaveClickListener());

        // Поиск ListView и установка адаптера
        ListView listView = findViewById(R.id.listView);
        listView.setAdapter(listAdapter);
    }

    private void addCoordsToList(String coods) {
        coordsList.add(coods); // добавление в список
        listAdapter.notifyDataSetChanged(); // сообщаем адаптеру, что данные были изменены
    }

    private void clearList() {
        coordsList.clear(); // очистка списка
        listAdapter.notifyDataSetChanged(); // сообщаем адаптеру, что данные были изменены
    }


    private void writeToFile(List<String> coordsList) {

        // перевод списка координат в одну строку
        String coordsData = listJoin(coordsList, ",\n");

        try {
            // Сохранение в файл
            File file = new File(Environment.getExternalStorageDirectory() + "/" + FILE_NAME);
            if (!file.exists()) {
                file.createNewFile();
            }
            FileWriter writer = new FileWriter(file);
            writer.append(coordsData);
            writer.flush();
            writer.close();

            Toast.makeText(this, "Saving success!", Toast.LENGTH_SHORT).show();

        } catch (IOException e) {
            Toast.makeText(this, "Saving failed!", Toast.LENGTH_SHORT).show();
            Log.e("Exception", "File write failed: " + e.toString());
        }
    }

    // разделяет список строку input с помощь separator.
    // Возвращает строку со всеми эелемнтами списка
    private static String listJoin(List<String> input, String separator) {

        if (input == null || input.size() <= 0) return "";

        StringBuilder sb = new StringBuilder();

        for (int i = 0; i < input.size(); i++) {

            sb.append(input.get(i));

            // if not the last item
            if (i != input.size() - 1) {
                sb.append(separator);
            }

        }

        return sb.toString();

    }

    // обработчки нажатий
    private final class TouchListener implements View.OnTouchListener {

        @Override
        public boolean onTouch(View v, MotionEvent event) {

            int x = (int) event.getX();
            int y = (int) event.getY();

            switch (event.getAction()) {
                case MotionEvent.ACTION_DOWN:
                    // если дейстки "Тап"

                    // добавление координат Тапа в список
                    String coords = String.format("%d : %d", x, y);
                    addCoordsToList(coords);
                    break;
            }

            return true;
        }
    }

    // Обработчик клика по Clear
    private final class ClearClickListener implements View.OnClickListener {

        @Override
        public void onClick(View v) {
            // очистка списка
            clearList();
        }
    }

    // Обработчик клика по Save
    private final class SaveClickListener implements View.OnClickListener {

        @Override
        public void onClick(View v) {
            // запуск сохранения в файл
            writeToFile(coordsList);
        }
    }


}
