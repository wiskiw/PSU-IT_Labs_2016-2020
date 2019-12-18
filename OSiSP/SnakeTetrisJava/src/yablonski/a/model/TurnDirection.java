package yablonski.a.model;

public enum TurnDirection {
    RIGHT(1), LEFT(-1);

    private int value;

    TurnDirection(int value) {
        this.value = value;
    }

    public int getValue() {
        return value;
    }
}
