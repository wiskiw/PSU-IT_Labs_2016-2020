package yablonski.a.model;

import yablonski.a.model.input.KeyActionTranslator;
import yablonski.a.model.map.items.*;

import java.awt.*;
import java.awt.event.KeyEvent;
import java.util.*;
import java.util.List;

public class SnakeTetris implements KeyActionTranslator.Callback {

    private static final int TETRIS_FALLING_SPEED = 2;

    private KeyActionTranslator keyTranslator;
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
        keyTranslator = new KeyActionTranslator(this);
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
        if (!staticBlocks.isEmpty()) {
            higherYPoint = Collections.max(staticBlocks, Comparator.comparing(Block::getY)).getY();
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
        Block zBlock = mapCreature.getBody().stream()
                .filter(block -> block.getY() == 0).findFirst().orElse(null);
        if (zBlock != null) {
            return true;
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
        Block sBlock = staticBlocks.stream()
                .filter(block -> block.getX() == tempHead.getX()
                        && block.getY() == tempHead.getY())
                .findFirst()
                .orElse(null);
        if (sBlock != null) {
            return false;
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

    public void onKeyPress(KeyEvent event) {
        keyTranslator.process(event);
    }

    private Color randomColor(Color[] colors) {
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

    @Override
    public void goUp() {
        creature.setMovingDirection(Direction.UP);
    }

    @Override
    public void goDown() {
        creature.setMovingDirection(Direction.DOWN);
    }

    @Override
    public void goRight() {
        creature.setMovingDirection(Direction.RIGHT);
    }

    @Override
    public void goLeft() {
        creature.setMovingDirection(Direction.LEFT);
    }

    @Override
    public void action() {
        if (!isPlaying()) {
            start();
        }
    }
}
