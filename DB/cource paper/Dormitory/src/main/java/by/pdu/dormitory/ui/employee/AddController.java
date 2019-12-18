package by.pdu.dormitory.ui.employee;

import by.pdu.dormitory.domain.OtherRoom;
import by.pdu.dormitory.domain.Post;
import by.pdu.dormitory.mapper.EmployeeMapper;
import by.pdu.dormitory.ui.windows.Window;
import by.pdu.dormitory.util.AlertWindow;
import javafx.fxml.FXML;

public class AddController extends InitEmployee {
    @FXML
    private void add() {
        try {
            EmployeeMapper employeeMapper = ctx.getBean("employeeMapper", EmployeeMapper.class);
            Post post = (Post) postBox.getValue();
            OtherRoom otherRoom = (OtherRoom) otherRoomBox.getValue();
            if (post == null || otherRoom == null) {
                AlertWindow.errorAlert("Не выбрана должность или закрепленная комната");
                return;
            }
            employeeMapper.insertEmployee(nameText.getText(), post.getId(), otherRoom.getId());
            close(Window.CLICK_ADD);
        } catch (Exception ex) {
            AlertWindow.errorAlert(ex.getMessage());
            ex.printStackTrace();
        }
    }


}
