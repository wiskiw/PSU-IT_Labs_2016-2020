package by.pdu.dormitory.ui.employee;

import by.pdu.dormitory.domain.Employee;
import by.pdu.dormitory.domain.Faculty;
import by.pdu.dormitory.domain.OtherRoom;
import by.pdu.dormitory.domain.Post;
import by.pdu.dormitory.mapper.EmployeeMapper;
import by.pdu.dormitory.mapper.GroupMapper;
import by.pdu.dormitory.ui.windows.Window;
import by.pdu.dormitory.util.AlertWindow;
import javafx.fxml.FXML;


public class UpdateController extends InitEmployee {
    private Employee employee;

    @FXML
    private void update() {
        try {
            EmployeeMapper employeeMapper = ctx.getBean("employeeMapper",EmployeeMapper.class);
            Post post = (Post)postBox.getValue();
            OtherRoom otherRoom = (OtherRoom) otherRoomBox.getValue();
            if (post == null || otherRoom == null) {
                AlertWindow.errorAlert("Не выбрана должность или закрепленная комната");
                return;
            }
            employeeMapper.updateEmployee(employee.getId(),nameText.getText(),post.getId(),otherRoom.getId());
            close(Window.CLICK_EDIT);
        } catch (Exception ex) {
            AlertWindow.errorAlert(ex.getMessage());
            ex.printStackTrace();
        }
    }

    public void setEmployee(Employee employee) {
        this.employee = employee;
        nameText.setText(employee.getFIO());
        postBox.getSelectionModel().select(employee.getPost());
        otherRoomBox.getSelectionModel().select(employee.getOtherRoom());
    }


}
