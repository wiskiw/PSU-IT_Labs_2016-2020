package by.pdu.dormitory.ui.group;

import by.pdu.dormitory.domain.Faculty;
import by.pdu.dormitory.mapper.FacultyMapper;
import by.pdu.dormitory.mapper.GroupMapper;
import by.pdu.dormitory.mapper.InventoryMapper;
import by.pdu.dormitory.ui.windows.SupportWindow;
import by.pdu.dormitory.ui.windows.Window;
import by.pdu.dormitory.util.AlertWindow;
import by.pdu.dormitory.util.ApplicationContext;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.fxml.FXML;
import javafx.scene.control.TextField;
import javafx.scene.control.ComboBox;

public class AddController extends SupportWindow {

    @FXML
    private TextField nameText;

    @FXML
    private ComboBox facultyBox;

    @FXML
    private void add() {
        try {
            GroupMapper groupMapper = ctx.getBean("groupMapper",GroupMapper.class);
            Faculty faculty = (Faculty)facultyBox.getValue();
            if (faculty == null) {
                AlertWindow.errorAlert("Выберите факультет");
                return;
            }
            groupMapper.insertGroup(nameText.getText(),faculty.getId());
            close(Window.CLICK_ADD);
        } catch (Exception ex) {
            AlertWindow.errorAlert(ex.getMessage());
            ex.printStackTrace();
        }
    }

    @Override
    public void setApplicationContext(ApplicationContext ctx) {
        super.setApplicationContext(ctx);
        FacultyMapper facultyMapper = ctx.getBean("facultyMapper",FacultyMapper.class);
        ObservableList<Faculty> faculties = FXCollections.observableArrayList(facultyMapper.getFaculty());
        facultyBox.setItems(faculties);
    }
}
