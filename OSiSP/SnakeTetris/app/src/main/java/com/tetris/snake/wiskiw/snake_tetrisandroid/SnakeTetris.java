package com.tetris.snake.wiskiw.snake_tetrisandroid;

import com.tetris.snake.wiskiw.snake_tetrisandroid.input.ControlButton;
import com.tetris.snake.wiskiw.snake_tetrisandroid.items.Creature;
import com.tetris.snake.wiskiw.snake_tetrisandroid.items.Food;
import com.tetris.snake.wiskiw.snake_tetrisandroid.items.MapCreature;
import com.tetris.snake.wiskiw.snake_tetrisandroid.items.SnakeCreature;
import com.tetris.snake.wiskiw.snake_tetrisandroid.items.TetrisCreature;

import java.util.ArrayList;
import java.util.HashSet;
import java.util.List;
import java.util.Random;

public class SnakeTetris {

    private static final int TETRIS_FALLING_SPEED = 2;

    private SnakeTetrisCallback callback;

    private HashSet<Block> staticBlocks = new HashSet<>();
    private Creature creature;
    private Food food;

    private int score = 0;

    private int mapWidth;
    private int mapHeight;
    private boolean debugMode = false;

    // 0 - gameOver/gameOver
    // 1 - play
    private int gameState = 0;

    private CreatureState creatureState = CreatureState.SNAKE;

    public SnakeTetris(SnakeTetrisCallback callback, int mapWidth, int mapHeight, boolean debugMode) {
        this.callback = callback;
        this.mapWidth = mapWidth;
        this.mapHeight = mapHeight;
        this.debugMode = debugMode;
    }

    private void start() {
        gameState = 1;
        staticBlocks.clear();
        food = null;
        creature = null;
        spawnSnake();
        spawnFood();
        score = 0;
    }

    private void gameOver(int score) {
        gameState = 0;
        callback.onGameOver(score);
    }

    private boolean isPlaying() {
        return gameState == 1;
    }

    public List<Block> getBlocksToDraw() {
        List<Block> blocks = new ArrayList<>(staticBlocks);
        if (food != null) {
            blocks.addAll(food.getBody());
        }
        blocks.addAll(creature.getBody());
        return blocks;
    }

    private void spawnSnake() {
        Random rand = new Random();
        int size = 4;
        int randX = rand.nextInt(mapWidth) + 1;
        //mapWidth is the maximum and the 1 is minimum
        this.creature = new Creature();
        this.creature.setHead(new Block(randX, mapHeight - size + 1,
                SnakeCreature.COLOR_HEAD), Direction.DOWN);

        for (int i = size - 1; i > 0; i--) {
            this.creature.addToBody(new Block(randX, mapHeight - i + 1, SnakeCreature.COLOR_BODY));
        }
    }


    private void spawnFood() {
        int higherYPoint = 0;

        for (Block staticBlock : staticBlocks) {
            if (staticBlock.getY() > higherYPoint) {
                higherYPoint = staticBlock.getY();
            }
        }
        higherYPoint++;

        System.out.println("...");
        System.out.println("higherYPoint: " + higherYPoint);
        Random random = new Random();
        int xP = random.nextInt(mapWidth) + 1;
        int yP = random.nextInt(mapHeight - higherYPoint) + higherYPoint;
        this.food = new Food(xP, yP);
        System.out.println("New Food: " + this.food.toString());
    }


    // проверка налиция опоры ниже mapCreature
    private boolean isFlorBellow(MapCreature mapCreature) {
        // нижний край поля
        for (Block block : mapCreature.getBody()) {
            if (block.getY() == 0) {
                return true;
            }
        }


        for (Block staticBlock : staticBlocks) {
            for (Block creatureBlock : mapCreature.getBody()) {
                // it.y - 1  - проверка координаты снизу
                if (creatureBlock.getX() == staticBlock.getX() &&
                        creatureBlock.getY() - 1 == staticBlock.getY()) {
                    return true;
                }
            }
        }
        return false;
    }

    private boolean isNextStepAllow() {
        Block tempHead = new Block(creature.getHead());
        tempHead.move(creature.getMovingDirection());

        // проверка границ
        if (tempHead.getX() <= 0 || tempHead.getX() > mapWidth) {
            // границы по горозонтали
            return false;
        } else if (tempHead.getY() < 0 || tempHead.getY() > mapHeight) {
            // по вертикали
            return false;
        }

        // проверка столкновения со статичными блоками
        for (Block block : staticBlocks) {
            if (tempHead.isIn(block)) {
                return false;
            }
        }

        // проверка столкновения с хвостом
        for (Block snakeBlock : creature.getBody()) {
            if (snakeBlock.isIn(tempHead)) {
                return false;
            }
        }
        return true;
    }

    private int checkLayers(int count) {
        int fieldBlockCounter;
        List<Block> toRemove;
        for (int yLayer = 0; yLayer <= mapHeight; yLayer++) {
            fieldBlockCounter = 0;

            for (Block staticBlock : staticBlocks) {
                if (staticBlock.getY() == yLayer) {
                    fieldBlockCounter++;
                }
            }

            if (fieldBlockCounter == mapWidth) {
                // если вся строка занята

                // убираем уровеснь со сдвигом вниз
                toRemove = new ArrayList<>();
                for (Block staticBlock : staticBlocks) {
                    if (staticBlock.getY() > yLayer) {
                        staticBlock.move(Direction.DOWN);
                    } else if (staticBlock.getY() == yLayer) {
                        toRemove.add(staticBlock);
                    }
                }
                staticBlocks.removeAll(toRemove);

                // перепроверка
                checkLayers(count + 1);
            }
        }

        // count - количество свернутых слоев
        return count;
    }

    public void onKeyPress(ControlButton button) {
        if (!isPlaying()) {
            start();
        } else {
            switch (button) {
                case UP:
                    creature.setMovingDirection(Direction.UP);
                    break;
                case DOWN:
                    creature.setMovingDirection(Direction.DOWN);
                    break;
                case LEFT:
                    creature.setMovingDirection(Direction.LEFT);
                    break;
                case RIGHT:
                    creature.setMovingDirection(Direction.RIGHT);
                    break;
            }
        }
    }

    private int randomColor(int[] colors) {
        return colors[new Random().nextInt(colors.length)];
    }

    // tick update method
    public void update() {
        if (!isPlaying()) return;
        switch (creatureState) {
            case SNAKE:
                if (isNextStepAllow()) {
                    creature.moveSnake();
                    if (food.isIn(creature.getHead())) {
                        // есть еду
                        food = null;
                        creatureState = CreatureState.TETRIS_FALLING;
                        creature.recolor(randomColor(TetrisCreature.piecColors));
                    }
                } else {
                    if (debugMode) {
                        creatureState = CreatureState.TETRIS_FALLING;
                        creature.recolor(randomColor(TetrisCreature.piecColors));
                    } else {
                        // game over
                        gameOver(score);
                        return;
                    }
                }
                break;

            case TETRIS_FALLING:
                for (int i = 0; i < TETRIS_FALLING_SPEED; i++) {
                    if (isFlorBellow(creature)) {
                        staticBlocks.addAll(creature.getBody());
                        spawnSnake();
                        spawnFood();
                        score += 10 * checkLayers(0); // обновление счета
                        creatureState = CreatureState.SNAKE;
                    } else {
                        creature.moveTetrisDown();
                    }
                }
                break;
        }
        callback.onGameUpdate(score);
    }

}
