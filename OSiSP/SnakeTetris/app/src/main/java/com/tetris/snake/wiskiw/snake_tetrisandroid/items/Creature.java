package com.tetris.snake.wiskiw.snake_tetrisandroid.items;

import com.tetris.snake.wiskiw.snake_tetrisandroid.Block;
import com.tetris.snake.wiskiw.snake_tetrisandroid.Direction;

import java.util.ArrayList;

public class Creature implements SnakeCreature, TetrisCreature {

    private Direction movingDirection;
    private ArrayList<Block> body;

    private Block snakeHead;

    public Creature() {
        this.body = new ArrayList<>();
    }

    @Override
    public Block getHead() {
        return snakeHead;
    }

    @Override
    public void setHead(Block snakeHead, Direction movingDirection) {
        this.snakeHead = snakeHead;
        this.movingDirection = movingDirection;
        this.body.add(0, snakeHead);
    }

    @Override
    public boolean addToBody(Block block) {
        if (body.contains(block)) {
            return false;
        } else {
            body.add(block);
            return true;
        }
    }

    @Override
    public ArrayList<Block> getBody() {
        return body;
    }

    @Override
    public void moveSnake() {
        body.remove(body.size() - 1);

        snakeHead.setColor(SnakeCreature.COLOR_BODY);
        snakeHead = new Block(snakeHead);
        snakeHead.move(movingDirection);
        snakeHead.setColor(SnakeCreature.COLOR_HEAD);

        setHead(snakeHead, movingDirection);
    }

    @Override
    public void setMovingDirection(Direction direction) {
        this.movingDirection = direction;
    }

    @Override
    public void moveTetrisDown() {
        movingDirection = Direction.DOWN;
        for (Block block : body) {
            block.move(movingDirection);
        }
    }


    @Override
    public void recolor(int color) {
        for (Block block : body) {
            block.setColor(color);
        }
    }

    @Override
    public Direction getMovingDirection() {
        return movingDirection;
    }
}
