package by.pdu.dormitory.ui.tenant;

import by.pdu.dormitory.domain.*;
import by.pdu.dormitory.mapper.PropertyMapper;
import by.pdu.dormitory.mapper.TenantMapper;
import by.pdu.dormitory.ui.windows.Window;
import by.pdu.dormitory.util.AlertWindow;
import javafx.fxml.FXML;


public class UpdateController extends InitTenant {
    private Tenant tenant;

    @FXML
    private void update() {
        try {
            TenantMapper tenantMapper = ctx.getBean("tenantMapper", TenantMapper.class);
            Long number = tenant.getId();
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
                tenantMapper.updateStudent(number, birthday, fio, room.getId(), group.getId());
            } else {
                tenantMapper.updateEmployeeTenant(number, birthday, fio, room.getId(), workField.getText());
            }

            tenantMapper.removeProperty(number);

            for (Object obj : propTenantView.getItems()) {
                tenantMapper.insertProperty(number, ((Property) obj).getId());
            }

            close(Window.CLICK_EDIT);
        } catch (Exception ex) {
            AlertWindow.errorAlert(ex.getMessage());
            ex.printStackTrace();
        }
    }

    public void setTenant(Tenant tenant) {
        PropertyMapper propertyMapper = ctx.getBean("propertyMapper", PropertyMapper.class);
        this.tenant = tenant;
        fioField.setText(tenant.getFIO());
        String[] dates = tenant.getBirthday().toString().split("-");
        String birthday = dates[2] + "." + dates[1] + "." + dates[0];
        birthdayPicker.getEditor().setText(birthday);
        System.out.println(tenant.getRoom());
        roomBox.getSelectionModel().select(tenant.getRoom());
        for (Property prop : propertyMapper.getPropertyTenant(tenant.getId())) {
            propView.getItems().remove(prop);
            propTenantView.getItems().add(prop);
        }
        if (tenant.getClass().equals(EmployeeTenant.class)) {
            workField.setText(((EmployeeTenant) tenant).getWork());
            choose.getSelectionModel().select(1);
        } else {
            groupBox.getSelectionModel().select(((Student) tenant).getGroup());
        }

    }

}
