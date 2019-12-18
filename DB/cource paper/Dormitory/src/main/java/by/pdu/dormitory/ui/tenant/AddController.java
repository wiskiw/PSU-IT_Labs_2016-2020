package by.pdu.dormitory.ui.tenant;

import by.pdu.dormitory.domain.Group;
import by.pdu.dormitory.domain.Property;
import by.pdu.dormitory.domain.Room;
import by.pdu.dormitory.mapper.TenantMapper;
import by.pdu.dormitory.ui.windows.Window;
import by.pdu.dormitory.util.AlertWindow;
import javafx.fxml.FXML;

public class AddController extends InitTenant {

    @FXML
    private void add() {
        try {
            TenantMapper tenantMapper = ctx.getBean("tenantMapper", TenantMapper.class);
            Long number = Long.parseLong(numberField.getText());
            String fio = fioField.getText();
            String birthday = birthdayPicker.getEditor().getText();
            Room room = (Room) roomBox.getValue();
            if (room == null) {
                AlertWindow.errorAlert("Выберите комнату");
                return;
            }

            if (choose.getSelectionModel().getSelectedItem().getText().equals("Студент")) {
                Group group = (Group) groupBox.getSelectionModel().getSelectedItem();
                if (group == null) {
                    AlertWindow.errorAlert("Выберите группу");
                    return;
                }
                tenantMapper.insertStudent(number, birthday, fio, room.getId(), group.getId());
            } else {
                tenantMapper.insertEmployeeTenant(number, birthday, fio, room.getId(), workField.getText());
            }

            for (Object obj : propTenantView.getItems()) {
                tenantMapper.insertProperty(number, ((Property) obj).getId());
            }

            close(Window.CLICK_ADD);
        } catch (Exception ex) {
            AlertWindow.errorAlert(ex.getMessage());
            ex.printStackTrace();
        }
    }

}
