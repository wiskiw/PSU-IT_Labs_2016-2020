package by.pdu.dormitory.ui.property;

import by.pdu.dormitory.domain.Property;
import by.pdu.dormitory.mapper.PropertyMapper;
import by.pdu.dormitory.ui.windows.SupportWindow;
import by.pdu.dormitory.ui.windows.Window;
import by.pdu.dormitory.util.AlertWindow;
import javafx.fxml.FXML;
import javafx.scene.control.TextField;
import javafx.stage.Stage;


public class UpdateController extends SupportWindow {
    private Property property;

    @FXML
    private TextField nameText;

    @FXML
    private void update() {
        try {
            PropertyMapper propertyMapper = ctx.getBean("propertyMapper", PropertyMapper.class);
            propertyMapper.updateProperty(property.getId(), nameText.getText());
            close(Window.CLICK_EDIT);
        } catch (Exception ex) {
            AlertWindow.errorAlert(ex.getMessage());
            ex.printStackTrace();
        }
    }

    public void setProperty(Property property) {
        this.property = property;
        nameText.setText(property.getName());
    }
}
