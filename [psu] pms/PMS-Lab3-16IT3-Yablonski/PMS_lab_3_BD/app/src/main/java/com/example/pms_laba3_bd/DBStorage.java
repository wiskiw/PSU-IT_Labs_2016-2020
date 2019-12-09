package com.example.pms_laba3_bd;

import java.util.ArrayList;
import java.util.List;
import java.util.Locale;

import android.content.ContentValues;
import android.content.Context;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;

/**
 * @author Andrey Yablonsky on 09.12.2019
 */
public class DBStorage {

    private static final String DATABASE_NAME = "androidDatabase.db";
    private static final String DATABASE_TABLE = "items";

    private static final String ID_COLUMN = "_id";
    private static final String NAME_COLUMN = "name";

    private static final String CREATE_TABLE_QUERY =
        String.format("create table if not exists %s (%s integer primary key autoincrement, %s text not null);",
            DATABASE_TABLE, ID_COLUMN, NAME_COLUMN);


    private final SQLiteDatabase database;

    public DBStorage(Context context) {
        database = context.openOrCreateDatabase(DATABASE_NAME, Context.MODE_PRIVATE, null);
    }

    public List<String> readItems() {
        Cursor cursor = database.query(DATABASE_TABLE, new String[] {NAME_COLUMN},
            null, null, null, null, null);

        List<String> items = new ArrayList<>();
        if (cursor.moveToFirst()) {
            do {
                items.add(cursor.getString(cursor.getColumnIndex(NAME_COLUMN)));
            }
            while (cursor.moveToNext());
        }
        cursor.close();
        return items;
    }

    public void init(boolean drop) {
        if (drop) {
            database.execSQL("DROP TABLE IF EXISTS " + DATABASE_TABLE + ";");
        }
        database.execSQL(CREATE_TABLE_QUERY);
    }

    public int getId(String name) {
        String selection = String.format("%s = '%s'", NAME_COLUMN, name);

        Cursor idQueryCursor = database.query(DATABASE_TABLE, new String[] {ID_COLUMN}, selection,
            null, null, null, null, null);

        if (idQueryCursor.moveToFirst()) {
            return Integer.parseInt(idQueryCursor.getString(idQueryCursor.getColumnIndex(ID_COLUMN)));
        }
        idQueryCursor.close();

        return -1;
    }

    public void delete(int id) {
        String query = String.format(Locale.getDefault(), "delete from %s where %s=%d", DATABASE_TABLE, ID_COLUMN, id);
        database.execSQL(query);
    }

    public void update(int id, String name) {
        String query = String.format(Locale.getDefault(),
            "update %s set %s = '%s' where %s=%d", DATABASE_TABLE, NAME_COLUMN, name, ID_COLUMN, id);
        database.execSQL(query);
    }

    public void add(String name) {
        String query = String.format("insert into %s (%s) values ('%s')", DATABASE_TABLE, NAME_COLUMN, name);
        database.execSQL(query);
    }

    public void addAll(List<String> items) {
        ContentValues newRow = new ContentValues();

        for (String item : items) {
            newRow.put(NAME_COLUMN, item);
        }
        database.insert(DATABASE_TABLE, null, newRow);
    }

}
