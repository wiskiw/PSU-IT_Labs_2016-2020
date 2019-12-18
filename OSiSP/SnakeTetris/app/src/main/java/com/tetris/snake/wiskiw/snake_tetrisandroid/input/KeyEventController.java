package com.tetris.snake.wiskiw.snake_tetrisandroid.input;

public class KeyEventController {

    private ControlButton lastEvent = null;

    public void onKeyPress(ControlButton event) {
        lastEvent = event;
    }

    public void tickUpdate() {
        lastEvent = null;
    }

    public boolean hasPress() {
        return lastEvent != null;
    }

    public ControlButton getPressedKey() {
        return lastEvent;
    }


}
