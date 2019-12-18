package by.pdu.dormitory.ui.faculty;

import by.pdu.dormitory.mapper.FacultyMapper;
import by.pdu.dormitory.ui.windows.SupportWindow;
import by.pdu.dormitory.ui.windows.Window;
import by.pdu.dormitory.util.AlertWindow;
import javafx.fxml.FXML;
import javafx.scene.control.TextField;
import javafx.stage.Stage;


public class AddController extends SupportWindow {


    @FXML
    private TextField nameText;

    @FXML
    private void add() {
        try {
            FacultyMapper facultyMapper = ctx.getBean("facultyMapper",FacultyMapper.class);
            facultyMapper.insertFaculty(nameText.getText());
            close(Window.CLICK_ADD);
        } catch (Exception ex) {
            AlertWindow.errorAlert(ex.getMessage());
            ex.printStackTrace();
        }
    }
}
