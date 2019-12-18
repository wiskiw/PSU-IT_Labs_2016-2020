package by.pdu.dormitory.ui.post;

import by.pdu.dormitory.mapper.PostMapper;
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
            PostMapper postMapper = ctx.getBean("postMapper", PostMapper.class);
            postMapper.insertPost(nameText.getText());
            close(Window.CLICK_ADD);
        } catch (Exception ex) {
            AlertWindow.errorAlert(ex.getMessage());
            ex.printStackTrace();
        }
    }
}
