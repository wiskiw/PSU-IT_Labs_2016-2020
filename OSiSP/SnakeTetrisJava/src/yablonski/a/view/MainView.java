package yablonski.a.view;

import javafx.util.Pair;
import yablonski.a.presenter.MainPresenter;

import javax.swing.*;
import javax.swing.border.EmptyBorder;
import java.awt.*;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;

public class MainView extends JFrame implements MainViewInterface {

    private MainPresenter presenter;

    private static final int CONTROLS_BAR_HEIGHT = 50;

    private static final int WINDOW_HEIGHT = 550;
    private static final int WINDOW_WIDTH = 400;


    private static final double GAME_SQUARE_SIZE_FACTOR = 2;

    private static int gameFieldSizeX = (int) (25 / GAME_SQUARE_SIZE_FACTOR);
    private static int gameFieldSizeY = (int) (30 / GAME_SQUARE_SIZE_FACTOR);


    private JLabel textLabel = new JLabel();
    private JPanel gameFieldPane;
    private JPanel controlPane;

    private JPanel[][] gameSquaresHolder = new JPanel[gameFieldSizeX][gameFieldSizeY];

    public MainView() throws HeadlessException {
        super("Snake-Tetris");

        this.setBounds(500, 100, WINDOW_WIDTH, WINDOW_HEIGHT);
        this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);


        System.out.println("gameFieldSizeX: " + gameFieldSizeX);
        System.out.println("gameFieldSizeY: " + gameFieldSizeY);

        // Game field
        prepareGameField();

        // Control/stats field
        prepareControlBar();

        initPressListener();


        JPanel panesHolder = new JPanel();
        panesHolder.setLayout(new BoxLayout(panesHolder, BoxLayout.Y_AXIS));
        panesHolder.add(gameFieldPane);
        panesHolder.add(controlPane);

        this.add(panesHolder);

        presenter = new MainPresenter(this, gameFieldSizeX, gameFieldSizeY);
    }

    public void update() {
        presenter.tickUpdate();
    }

    private void initPressListener() {
        KeyListener listener = new KeyListener() {
            @Override
            public void keyPressed(KeyEvent event) {
                presenter.onKeyPress(event);
            }

            @Override
            public void keyReleased(KeyEvent event) {
                //System.out.println("Key Released: " + event.toString());
            }

            @Override
            public void keyTyped(KeyEvent event) {
                //System.out.println("Key Typed: " + event.toString());
            }
        };

        this.addKeyListener(listener);
    }

    private void prepareGameField() {
        gameFieldPane = new JPanel();
        gameFieldPane.setMaximumSize(new Dimension(WINDOW_WIDTH, WINDOW_HEIGHT - CONTROLS_BAR_HEIGHT));

        GridLayout layout = new GridLayout(gameFieldSizeY, gameFieldSizeX);
        gameFieldPane.setLayout(layout);

        JLabel l;
        for (int y = 0; y < gameFieldSizeY; y++) {
            for (int x = 0; x < gameFieldSizeX; x++) {
                gameSquaresHolder[x][y] = new JPanel();

/*
                //debug grid
                l = new JLabel(x + ":" + y);
                l.setFont(new Font(l.getFont().getName(), Font.PLAIN, 8));
                //gameSquaresHolder[x][y].setBackground(new Color(y * 5, x * 0, 0));
                gameSquaresHolder[x][y].add(l);
*/
                gameFieldPane.add(gameSquaresHolder[x][y]);
            }
        }
    }

    private void prepareControlBar() {
        controlPane = new JPanel(new FlowLayout(FlowLayout.CENTER));
        controlPane.setBackground(new Color(250, 126, 3));
        controlPane.add(textLabel);
        controlPane.setMaximumSize(new Dimension(Integer.MAX_VALUE, CONTROLS_BAR_HEIGHT));


        // Changing Score text size, padding
        textLabel.setFont(new Font(textLabel.getFont().getName(), Font.PLAIN, 16));
        textLabel.setBorder(new EmptyBorder(10, 0, 10, 0));
    }

    @Override
    public boolean updateSquare(int x, int y, Color color) {
        // переход к координатной сетке JPanel
        x = x - 1;
        y = gameFieldSizeY - y - 1;
        if (x < 0 || y < 0) {
            return false;
        }
        if (x < gameSquaresHolder.length && y < gameSquaresHolder[x].length) {
            gameSquaresHolder[x][y].setBackground(color);
            return true;
        } else {
            return false;
        }
    }

    @Override
    public void updateScore(int score) {
        if (score >= 0) {
            textLabel.setVisible(true);
            textLabel.setText("Score: " + score);
        } else {
            textLabel.setText("Score: 0");
            textLabel.setVisible(false);
        }
    }

    @Override
    public void showMessage(String msg) {
        textLabel.setVisible(true);
        textLabel.setText(msg);
    }

    @Override
    public Pair<Integer, Integer> getGameFieldSize() {
        return new Pair<>(gameFieldSizeX, gameFieldSizeY);
    }

    @Override
    public void clearGameField() {
        for (int y = 0; y < gameFieldSizeY; y++) {
            for (int x = 0; x < gameFieldSizeX; x++) {
                gameSquaresHolder[x][y].setBackground(null);
            }
        }
    }
}
