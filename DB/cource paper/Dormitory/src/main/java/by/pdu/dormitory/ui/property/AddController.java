package by.pdu.dormitory.ui.property;

import by.pdu.dormitory.mapper.PropertyMapper;
import by.pdu.dormitory.ui.windows.SupportWindow;
import by.pdu.dormitory.ui.windows.Window;
import by.pdu.dormitory.util.AlertWindow;
import javafx.fxml.FXML;
import javafx.scene.control.TextField;


public class AddController extends SupportWindow {

    @FXML
    private TextField nameText;

    @FXML
    private void add() {
        try {
            PropertyMapper propertyMapper = ctx.getBean("propertyMapper", PropertyMapper.class);
            propertyMapper.insertProperty(nameText.getText());
            close(Window.CLICK_ADD);
        } catch (Exception ex) {
            AlertWindow.errorAlert(ex.getMessage());
            ex.printStackTrace();
        }
    }
}
