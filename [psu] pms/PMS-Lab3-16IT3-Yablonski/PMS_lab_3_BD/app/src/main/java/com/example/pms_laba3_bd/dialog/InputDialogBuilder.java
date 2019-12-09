package com.example.pms_laba3_bd.dialog;

import android.app.AlertDialog;
import android.app.Dialog;
import android.content.Context;
import android.widget.EditText;

/**
 * @author Andrey Yablonsky on 09.12.2019
 */
public class InputDialogBuilder {

    private Context context;

    private String title;
    private String value;
    private String hint;

    private Action okAction;

    public InputDialogBuilder(Context context) {
        this.context = context;
    }

    /**
     * Устанавливает заголовок диалога.
     * Если передан {@code null} заголовок не будет отображен.
     */
    public InputDialogBuilder setTitle(String title) {
        this.title = title;
        return this;
    }

    public InputDialogBuilder setValue(String value) {
        this.value = value;
        return this;
    }

    public InputDialogBuilder setHint(String hint) {
        this.hint = hint;
        return this;
    }

    public InputDialogBuilder setOkAction(Action okAction) {
        this.okAction = okAction;
        return this;
    }

    public InputDialogBuilder setOkAction(String label, DoneListener listener) {
        setOkAction(new Action(label, listener));
        return this;
    }

    public Dialog build() {
        final EditText editText = new EditText(context);
        editText.setHint(hint);
        if (value != null) {
            editText.setText(value);
        }

        AlertDialog.Builder builder = new AlertDialog.Builder(context);
        builder.setTitle(title);
        builder.setView(editText);

        if (okAction != null) {
            builder.setPositiveButton(okAction.getLabel(),
                (dialog, which) -> okAction.getListener().onEditDone(editText.getText().toString()));
        }

        return builder.create();
    }

    public final class Action {

        private String label;
        private DoneListener listener;

        public String getLabel() {
            return label;
        }

        public void setLabel(String label) {
            this.label = label;
        }

        public void setListener(DoneListener listener) {
            this.listener = listener;
        }

        public DoneListener getListener() {
            return listener;
        }

        public Action(String label, DoneListener listener) {
            this.label = label;
            this.listener = listener;
        }
    }

    public interface DoneListener {

        void onEditDone(String value);

    }

}
