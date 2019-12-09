package com.example.pms_laba3_bd.dialog;

/**
 * @author Andrey Yablonsky on 09.12.2019
 */
public class ListDialogItem {

    private String title;
    private Action action;
    private boolean isAvailable;

    public ListDialogItem(String title, Action action, boolean isAvailable) {
        this.title = title;
        this.action = action;
        this.isAvailable = isAvailable;
    }

    public ListDialogItem(String title, Action action) {
        this(title, action, true);
    }

    public String getTitle() {
        return title;
    }

    public void setTitle(String title) {
        this.title = title;
    }

    public Action getAction() {
        return action;
    }

    public void setAction(Action action) {
        this.action = action;
    }

    public boolean isAvailable() {
        return isAvailable;
    }

    public void setAvailable(boolean available) {
        isAvailable = available;
    }

    public interface Action {

        void execute(int position, ListDialogItem item);
    }
}
