package yablonski.a;

import yablonski.a.view.MainView;

import java.util.Timer;
import java.util.TimerTask;

public class Main {

    private static final Long SPEED = 400L;

    public static void main(String[] args) {
        MainView mainView = new MainView();
        mainView.setVisible(true);

        Timer timer = new Timer("Tick");
        long delay = SPEED + 1000;
        long period = SPEED;
        // scheduleAtFixedRate
        timer.schedule(new TimerTask() {
            public void run() {
                mainView.update();
            }
        }, delay, period);
    }

}
