package com.example.pms_laba3_bd;

import java.util.List;

import com.example.pms_laba3_bd.dialog.InputDialogBuilder;
import com.example.pms_laba3_bd.dialog.SingleChoiceDialogBuilder;

import android.app.Activity;
import android.os.Bundle;
import android.view.View;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.ListView;
import android.widget.TextView;
import android.widget.Toast;

public class MainActivity extends Activity {

    private DBStorage dbStorage;
    private ArrayAdapter<String> listAdapter;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        dbStorage = new DBStorage(this);
        dbStorage.init(false);

        List<String> heroes = dbStorage.readItems();
        listAdapter = new ArrayAdapter<>(this, android.R.layout.simple_list_item_1, heroes);

        ListView listView = findViewById(R.id.list);
        listView.setAdapter(listAdapter);
        listView.setOnItemClickListener(new ListItemClickListener());
        listView.setOnItemLongClickListener(new ListItemLongClickListener());

        findViewById(R.id.addButton).setOnClickListener(v -> showAddDialog());

        loadList();
    }

    private void loadList() {
        listAdapter.clear();
        listAdapter.addAll(dbStorage.readItems());
    }

    private void showAddDialog() {
        new InputDialogBuilder(this)
            .setTitle("Add")
            .setHint("Name")
            .setOkAction("Add", this::add)
            .build()
            .show();
    }

    private void showMenuDialog(int listItemIndex) {
        new SingleChoiceDialogBuilder(this)
            .setTitle("Actions")

            .addItem("Edit", (position, action) -> {
                String value = listAdapter.getItem(listItemIndex);
                int id = dbStorage.getId(value);
                showEditDialog(id, value);
            })

            .addItem("Delete", (position, action) -> {
                String value = listAdapter.getItem(listItemIndex);
                int id = dbStorage.getId(value);
                delete(id);
            })
            .build()
            .show();
    }

    private void showEditDialog(int id, String value) {
        new InputDialogBuilder(this)
            .setTitle("Edit")
            .setHint("Name")
            .setValue(value)
            .setOkAction("Save", newValue -> update(id, newValue))
            .build()
            .show();
    }

    private void delete(int id) {
        dbStorage.delete(id);
        loadList();
    }

    private void update(int id, String value) {
        dbStorage.update(id, value);
        loadList();
    }

    private void add(String value) {
        dbStorage.add(value);
        loadList();
    }

    private final class ListItemClickListener implements AdapterView.OnItemClickListener {

        @Override
        public void onItemClick(AdapterView<?> parent, View view, int position, long id) {
            String name = (String) ((TextView) view).getText();
            int itemId = dbStorage.getId(name);
            Toast.makeText(getApplicationContext(), String.valueOf(itemId), Toast.LENGTH_LONG).show();
        }
    }

    private final class ListItemLongClickListener implements AdapterView.OnItemLongClickListener {

        @Override
        public boolean onItemLongClick(AdapterView<?> parent, View view, int position, long id) {
            showMenuDialog(position);
            return true;
        }
    }

}
