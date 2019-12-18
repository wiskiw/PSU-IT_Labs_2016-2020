package com.tetris.snake.wiskiw.snake_tetrisandroid;

public class Block {

    private int x;
    private int y;
    private int color;


    public Block(int x, int y) {
        this.x = x;
        this.y = y;
    }

    public Block(int x, int y, int color) {
        this.x = x;
        this.y = y;
        this.color = color;
    }

    public Block(Block block) {
        this.x = block.x;
        this.y = block.y;
        this.color = block.color;
    }

    public int getX() {
        return x;
    }

    public void setX(int x) {
        this.x = x;
    }

    public int getY() {
        return y;
    }

    public void setY(int y) {
        this.y = y;
    }

    public int getColor() {
        return color;
    }

    public void setColor(int color) {
        this.color = color;
    }

    public void move(Direction direction) {
        switch (direction) {
            case UP:
                y++;
                break;
            case DOWN:
                y--;
                break;
            case RIGHT:
                x++;
                break;
            case LEFT:
                x--;
                break;
        }
    }

    @Override
    public String toString() {
        return "Block {" +
                "x=" + x +
                ", y=" + y +
                ", color=" + color +
                '}';
    }

    public boolean isIn(Block nextBlock) {
        return nextBlock.getX() == this.x && nextBlock.getY() == this.y;
    }
}
