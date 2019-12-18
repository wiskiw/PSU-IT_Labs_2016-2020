package com.tetris.snake.wiskiw.snake_tetrisandroid;

import java.util.HashMap;
import java.util.Map;

public enum Direction {
    UP(0), DOWN(1), RIGHT(2), LEFT(3);

    private int value;
    private static Map map = new HashMap<>();

    private Direction(int value) {
        this.value = value;
    }

    static {
        for (Direction direction : Direction.values()) {
            map.put(direction.value, direction);
        }
    }

    public static Direction valueOf(int direction) {
        return (Direction) map.get(direction);
    }

    public int getValue() {
        return value;
    }


}
