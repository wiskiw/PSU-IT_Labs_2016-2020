package com.example.pms_laba_3;

import android.os.Bundle;
import android.view.KeyEvent;
import android.view.View;
import android.widget.CheckBox;
import android.widget.EditText;
import android.widget.RadioButton;
import android.widget.Toast;
import android.widget.ToggleButton;
import androidx.appcompat.app.AppCompatActivity;

public class MainActivity extends AppCompatActivity {

    private EditText editText;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        editText = findViewById(R.id.editText);
        editText.setOnKeyListener(new KeyEventListener());
    }

    public void onButtonClicked(View v) {
        Toast.makeText(this, "On button click", Toast.LENGTH_SHORT).show();
    }

    public void onCheckboxClicked(View v) {
        boolean isCheck = ((CheckBox) v).isChecked();
        String message = isCheck ? "Checkbox's state have changed to ON" : "Checkbox's state have changed to OFF";
        Toast.makeText(this, message, Toast.LENGTH_SHORT).show();
    }

    public void onToggleClicked(View v) {
        boolean isToggleOn = ((ToggleButton) v).isChecked();
        String message = isToggleOn ? "Toggle's state have changed to ON" : "Toggle's state have changed to OFF";
        Toast.makeText(this, message, Toast.LENGTH_SHORT).show();
    }

    public void onRadioButtonClicked(View v) {
        RadioButton radioButton = (RadioButton) v;
        String message = "On radio clicked: " + radioButton.getText();
        Toast.makeText(this, message, Toast.LENGTH_SHORT).show();
    }

    public void onClearButtonClicked(View v) {
        editText.setText("");
        Toast.makeText(this, "Edit text have cleaned", Toast.LENGTH_SHORT).show();
    }

    private final class KeyEventListener implements View.OnKeyListener {

        @Override
        public boolean onKey(View v, int keyCode, KeyEvent event) {
            EditText editText = (EditText) v;
            if ((event.getAction() == KeyEvent.ACTION_DOWN) && (keyCode == KeyEvent.KEYCODE_ENTER)) {
                Toast.makeText(getApplicationContext(), editText.getText(), Toast.LENGTH_SHORT).show();

                return true;
            }
            return false;
        }
    }
}
