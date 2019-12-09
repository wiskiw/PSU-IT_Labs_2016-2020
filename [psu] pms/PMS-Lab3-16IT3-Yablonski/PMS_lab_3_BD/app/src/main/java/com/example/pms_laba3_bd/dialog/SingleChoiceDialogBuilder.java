package com.example.pms_laba3_bd.dialog;

import java.util.ArrayList;
import java.util.List;

import android.app.Dialog;
import android.content.Context;
import androidx.annotation.StringRes;
import androidx.appcompat.app.AlertDialog;

/**
 * Класс для создания диалога-списка одиночного выбора.
 *
 * @author Andrey Yablonsky on 09.12.2019
 */
public class SingleChoiceDialogBuilder {

    private Context context;

    private String title;

    private List<ListDialogItem> items = new ArrayList<>();

    public SingleChoiceDialogBuilder(Context context) {
        this.context = context;
    }

    /**
     * Устанавливает заголовок диалога.
     * Если передан {@code null} заголовок не будет отображен.
     */
    public SingleChoiceDialogBuilder setTitle(String title) {
        this.title = title;
        return this;
    }

    /**
     * Добавляет пункт в список доступных действий диалога
     *
     * @param item элемент списка диалога
     */
    public SingleChoiceDialogBuilder addItem(ListDialogItem item) {
        items.add(item);
        return this;
    }

    /**
     * Добавляет пункт активный пустк без сабтайтла в список доступных действий диалога
     *
     * @param title  заголовок действия
     * @param action действие, при выборе данного элемента
     *
     * @see #addItem(ListDialogItem)
     */
    public SingleChoiceDialogBuilder addItem(String title, ListDialogItem.Action action) {
        addItem(new ListDialogItem(title, action, true));
        return this;
    }

    /**
     * @see #addItem(String, ListDialogItem.Action)
     */
    public SingleChoiceDialogBuilder addItem(@StringRes int titleId, ListDialogItem.Action action) {
        addItem(context.getString(titleId), action);
        return this;
    }

    /**
     * Создает диалог
     */
    public Dialog build() {
        AlertDialog.Builder builder = new AlertDialog.Builder(context);
        if (title != null) {
            builder.setTitle(title);
        }

        builder.setItems(getTitles(items), (dialog, which) -> {
            ListDialogItem item = items.get(which);
            item.getAction().execute(which, item);
        });

        return builder.create();
    }

    private String[] getTitles(List<ListDialogItem> items) {
        String[] titles = new String[items.size()];
        for (int itemIndex = 0; itemIndex < items.size(); itemIndex++) {
            ListDialogItem item = items.get(itemIndex);
            titles[itemIndex] = item.getTitle();
        }
        return titles;
    }

}
