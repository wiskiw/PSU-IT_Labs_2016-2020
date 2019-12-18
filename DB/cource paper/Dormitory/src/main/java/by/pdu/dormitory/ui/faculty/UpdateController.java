package by.pdu.dormitory.ui.faculty;

import by.pdu.dormitory.domain.Faculty;
import by.pdu.dormitory.mapper.FacultyMapper;
import by.pdu.dormitory.ui.windows.SupportWindow;
import by.pdu.dormitory.ui.windows.Window;
import by.pdu.dormitory.util.AlertWindow;
import javafx.fxml.FXML;
import javafx.scene.control.TextField;

public class UpdateController extends SupportWindow {
    private Faculty faculty;

    @FXML
    private TextField nameText;

    @FXML
    private void update() {
        try {
            System.out.println(13);
            FacultyMapper facultyMapper = ctx.getBean("facultyMapper",FacultyMapper.class);
            facultyMapper.updateFaculty(faculty.getId(), nameText.getText());
            close(Window.CLICK_EDIT);
        } catch (Exception ex) {
            AlertWindow.errorAlert(ex.getMessage());
            ex.printStackTrace();
        }
    }

    public void setFaculty(Faculty faculty) {
        this.faculty = faculty;
        nameText.setText(faculty.getName());
    }
}
