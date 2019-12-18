package by.pdu.dormitory.util;

import by.pdu.dormitory.Main;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.image.Image;
import javafx.stage.Modality;
import javafx.stage.Stage;
import by.pdu.dormitory.ui.windows.Window;

import java.awt.*;
import java.io.IOException;

public class LoadFXML {
    private ApplicationContext ctx;

    public LoadFXML(ApplicationContext ctx) {
        this.ctx = ctx;
    }

    public void setApplicationContext(ApplicationContext ctx) {
        this.ctx = ctx;
    }

    public Window loadModal(String fxml, String title, Stage primaryStage, Stage owner, int width, int height) {
        return loadModal(fxml, title, primaryStage, owner, width, height, false);
    }

    public Window loadModal(String fxml, String title, Stage primaryStage, Stage owner) {
        return loadModal(fxml, title, primaryStage, owner, false);
    }

    public Window loadModal(String fxml, String title, Stage primaryStage, Stage owner, boolean resizable) {
        primaryStage.initOwner(owner);
        primaryStage.initModality(Modality.APPLICATION_MODAL);
        Window window = load(fxml, title, primaryStage, resizable);
        primaryStage.centerOnScreen();
        return window;
    }


    public Window loadModal(String fxml, String title, Stage primaryStage, Stage owner, int width, int height, boolean resizable) {
        primaryStage.initOwner(owner);
        primaryStage.initModality(Modality.APPLICATION_MODAL);
        Window window = load(fxml, title, primaryStage, width, height, resizable);
        primaryStage.centerOnScreen();
        return window;
    }

    public Window load(String fxml, String title, Stage primaryStage) {
        return load(fxml, title, primaryStage, false);
    }

    public Window load(String fxml, String title, Stage primaryStage, int width, int height) {
        return load(fxml, title, primaryStage, width, height, false);
    }

    private void centering(Stage primaryStage, int width, int height) {
        int oldWidth, oldHeight;
        oldHeight = (int) primaryStage.getHeight();
        oldWidth = (int) primaryStage.getWidth();
        int oldX, oldY;
        oldX = (int) primaryStage.getX();
        oldY = (int) primaryStage.getY();

        int centerX = (oldWidth / 2 + oldX);
        int centerY = (oldHeight / 2 + oldY);

        int newX = centerX - width / 2;
        int newY = centerY - height / 2;

        Dimension dim = Toolkit.getDefaultToolkit().getScreenSize();
        if (newX < 10) newX = 10;
        if (newX + width > dim.width) newX = dim.width - width;
        if (newY < 10) newY = 10;
        if (newY + height > dim.height - 75) newY = dim.height - height - 75;

        primaryStage.setX(newX);
        primaryStage.setY(newY);
    }

    public Window load(String fxml, String title, Stage primaryStage, boolean resizable) {
        try {
            FXMLLoader loader = new FXMLLoader();
            Parent root = loader.load(Main.class.getClassLoader().getResourceAsStream(fxml));
            Window controller = loader.getController();
            controller.setStage(primaryStage);
            controller.setApplicationContext(ctx);
            primaryStage.setTitle(title);
            primaryStage.setScene(new Scene(root));
            primaryStage.getIcons().removeAll();
            primaryStage.getIcons().add(new Image("img/icon.jpg"));
            primaryStage.setResizable(resizable);
            return controller;
        } catch (IOException e) {
            AlertWindow.errorAlert("Произошла непредвиденная ошибка.\nПрограмма будет закрыта");
            e.printStackTrace();
            System.exit(0);
        }
        return null;
    }

    public Window load(String fxml, String title, Stage primaryStage, int width, int height, boolean resizable) {
        try {
            FXMLLoader loader = new FXMLLoader();
            Parent root = loader.load(Main.class.getClassLoader().getResourceAsStream(fxml));
            Window controller = loader.getController();
            controller.setApplicationContext(ctx);
            controller.setStage(primaryStage);
            centering(primaryStage, width, height);
            primaryStage.setTitle(title);
            primaryStage.setScene(new Scene(root, width, height));
            primaryStage.getIcons().removeAll();
            primaryStage.getIcons().add(new Image("img/icon.jpg"));
            primaryStage.setResizable(resizable);
            return controller;
        } catch (IOException e) {
            AlertWindow.errorAlert("Произошла непредвиденная ошибка.\nПрограмма будет закрыта");
            e.printStackTrace();
            System.exit(0);
        }
        return null;
    }
}
