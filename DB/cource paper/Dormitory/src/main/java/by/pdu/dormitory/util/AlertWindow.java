package by.pdu.dormitory.util;


import javafx.scene.control.Alert;
import javafx.scene.control.ButtonType;
import javafx.scene.image.Image;
import javafx.stage.Stage;

import java.util.Optional;

public class AlertWindow {
    public static void errorAlert(String message) {
        Alert alert = new Alert(Alert.AlertType.WARNING);
        alert.setTitle("Ошибка");
        alert.setContentText(message);
        ((Stage) alert.getDialogPane().getScene().getWindow()).getIcons().add(new Image("img/icon.jpg"));
        alert.showAndWait();
    }

    public static ButtonType confirmationAlert(String message) {
        Alert alert = new Alert(Alert.AlertType.CONFIRMATION);
        alert.setTitle("Удалить");
        alert.setHeaderText("Удаление");
        alert.setResizable(false);
        alert.setContentText(message);
        //  alert.setContentText("Вы действиствительно хотите удалить выбранный элемент?");
        ((Stage) alert.getDialogPane().getScene().getWindow()).getIcons().add(new Image("img/icon.jpg"));
        Optional<ButtonType> result = alert.showAndWait();
        return result.get();
    }

    public static void errorAlert() {
        errorAlert("Фиг пойми что за ошибка ;)\nТут мои привилегии кончаются\nБегите глупцы :D");
    }

    public static void checkException(String message) {
        if (message.contains("ORA-01920") || message.contains("ORA-20001")) {
            AlertWindow.errorAlert("Такой пользователь существует.\nПопробуйте снова.");
            return;
        }

        if (message.contains("ORA-00001") || message.contains("ORA-20000")) {
            AlertWindow.errorAlert("Одно из полей должно быть уникально.\nПожалуйста исправьте данные и попробуйте снова.");
            return;
        }

        if (message.contains("ORA-20002")) {
            String [] str = message.split("\n");
            String oraMes="";
            for (String temp:str){
                if (temp.contains("ORA-20002")) oraMes=temp.substring(45);
            }
            AlertWindow.errorAlert(oraMes);
            return;
        }

        if (message.contains("ORA-20003")) {
            AlertWindow.errorAlert("Дата рождения не может быть больше текущего дня.");
            return;
        }

        if (message.contains("ORA-20004")) {
            AlertWindow.errorAlert("Абонемент должен быть действителен.");
            return;
        }

        if (message.contains("ORA-20005")) {
            AlertWindow.errorAlert("Логин должен состоять из: \n" +
                    "Заглавные латинские буквы: от A до Z\n" +
                    "Строчные латинские буквы: от a до z\n" +
                    "Цифры от 0 до 9\n" +
                    "Недолжен начинаться на цифру\n" +
                    "Длина от 6 до 26 символов\n" +
                    "Недолжен состоять из одних цифр");
            return;
        }

        if (message.contains("ORA-20006")) {
            AlertWindow.errorAlert("Пароль должен состоять из: \n" +
                    "Заглавные латинские буквы: от A до Z\n" +
                    "Строчные латинские буквы: от a до z\n" +
                    "Цифры от 0 до 9\n" +
                    "Длина от 6 до 26 символов\n");
            return;
        }

        if (message.contains("ORA-01400")){
            AlertWindow.errorAlert("Не должно быть пустых полей");
            return;
        }

        if (message.contains("ORA-02290")){
            AlertWindow.errorAlert("Нарушена правильностей данных в поле или полях");
            return;
        }

        if (message.contains("ORA")) {
            errorAlert("Ошибка Oracle.\nГлупцы бегите быстрее к администратору\nи сообщите код ошибки\n" + message);
        } else {
            errorAlert();
        }
    }
}
