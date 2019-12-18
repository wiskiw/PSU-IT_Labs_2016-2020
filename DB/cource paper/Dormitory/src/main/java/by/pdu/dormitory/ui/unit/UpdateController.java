package by.pdu.dormitory.ui.unit;

import by.pdu.dormitory.domain.Property;
import by.pdu.dormitory.domain.Unit;
import by.pdu.dormitory.mapper.PropertyMapper;
import by.pdu.dormitory.mapper.UnitMapper;
import by.pdu.dormitory.ui.windows.SupportWindow;
import by.pdu.dormitory.ui.windows.Window;
import by.pdu.dormitory.util.AlertWindow;
import javafx.fxml.FXML;
import javafx.scene.control.TextField;


public class UpdateController extends SupportWindow {
    private Unit unit;

    @FXML
    private TextField nameText;

    @FXML
    private void update() {
        try {
            UnitMapper unitMapper = ctx.getBean("unitMapper", UnitMapper.class);
            unitMapper.updateUnit(unit.getNumber(),Long.parseLong(nameText.getText()));
            close(Window.CLICK_EDIT);
        } catch (Exception ex) {
            AlertWindow.errorAlert(ex.getMessage());
            ex.printStackTrace();
        }
    }

    public void setUnit(Unit unit) {
        this.unit = unit;
        nameText.setText(unit.getNumber().toString());
    }
}
