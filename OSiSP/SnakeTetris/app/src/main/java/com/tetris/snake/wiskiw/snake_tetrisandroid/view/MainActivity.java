package com.tetris.snake.wiskiw.snake_tetrisandroid.view;

import android.graphics.Color;
import android.os.Bundle;
import android.support.annotation.Nullable;
import android.support.v7.app.AppCompatActivity;
import android.view.Gravity;
import android.view.View;
import android.widget.GridLayout;
import android.widget.TextView;

import com.tetris.snake.wiskiw.snake_tetrisandroid.R;
import com.tetris.snake.wiskiw.snake_tetrisandroid.input.ControlButton;
import com.tetris.snake.wiskiw.snake_tetrisandroid.presenter.MainPresenter;

import java.util.Timer;
import java.util.TimerTask;

public class MainActivity extends AppCompatActivity implements MainViewInterface {

    private static final Long SPEED = 440L;

    private static final int gameFieldSizeY = 12;
    private static final int gameFieldSizeX = 8;

    private GridLayout gridLayout;
    private TextView[][] gameSquaresHolder;
    private TextView textView;

    private static final boolean debugGrid = false;

    private MainPresenter presenter;

    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        textView = findViewById(R.id.textView);

        gridLayout = findViewById(R.id.gridLayout);
        gridLayout.setColumnCount(gameFieldSizeX);
        gridLayout.setRowCount(gameFieldSizeY);

        fillGrid();
        setupButtons();


        presenter = new MainPresenter(this, gameFieldSizeX, gameFieldSizeY);

        Timer timer = new Timer("Tick");
        long delay = SPEED + 1000;
        long period = SPEED;
        // scheduleAtFixedRate
        timer.schedule(new TimerTask() {
            public void run() {
                presenter.tickUpdate();
            }
        }, delay, period);
    }

    private void fillGrid() {
        gameSquaresHolder = new TextView[gameFieldSizeY][gameFieldSizeX];
        TextView v;
        int size = 128;
        GridLayout.LayoutParams param;
        for (int y = 0; y < gameFieldSizeY; y++) {
            for (int x = 0; x < gameFieldSizeX; x++) {
                v = new TextView(this);
                gameSquaresHolder[y][x] = v;

                param = new GridLayout.LayoutParams();
                //param.height = GridLayout.LayoutParams.WRAP_CONTENT;
                //param.width = GridLayout.LayoutParams.WRAP_CONTENT;
                param.height = size;
                param.width = size;
                param.columnSpec = GridLayout.spec(x);
                param.rowSpec = GridLayout.spec(y);
                v.setLayoutParams(param);
                v.setGravity(Gravity.CENTER);
                v.setBackgroundColor(Color.WHITE);

                gridLayout.addView(v);

                // debug
                if (debugGrid) {
                    v.setText(x + ":" + y);
                }
            }
        }
    }

    private void setupButtons() {
        findViewById(R.id.buttonUp).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                presenter.onKeyPress(ControlButton.UP);
            }
        });
        findViewById(R.id.buttonDown).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                presenter.onKeyPress(ControlButton.DOWN);
            }
        });
        findViewById(R.id.buttonRight).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                presenter.onKeyPress(ControlButton.RIGHT);
            }
        });
        findViewById(R.id.buttonLeft).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                presenter.onKeyPress(ControlButton.LEFT);
            }
        });
    }

    @Override
    public boolean updateSquare(int x, int y, int color) {
        // переход к координатной сетке JPanel
        x = x - 1;
        y = gameFieldSizeY - y - 1;
        if (x < 0 || y < 0) {
            return false;
        }
        gameSquaresHolder[y][x].setBackgroundColor(color);
        return false;
    }

    @Override
    public void updateScore(int score) {
        this.showMessage("Score: " + score);
    }

    @Override
    public void showMessage(final String msg) {
        runOnUiThread(new Runnable() {
            @Override
            public void run() {
                textView.setText(msg);
            }
        });
    }

    @Override
    public void clearGameField() {
        for (int y = 0; y < gameFieldSizeY; y++) {
            for (int x = 0; x < gameFieldSizeX; x++) {
                gameSquaresHolder[y][x].setBackgroundColor(Color.WHITE);
            }
        }
    }
}
