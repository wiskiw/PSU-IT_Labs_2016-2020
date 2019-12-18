package by.pdu.dormitory.ui.tenant;

import by.pdu.dormitory.domain.Group;
import by.pdu.dormitory.domain.Property;
import by.pdu.dormitory.domain.Room;
import by.pdu.dormitory.mapper.GroupMapper;
import by.pdu.dormitory.mapper.PropertyMapper;
import by.pdu.dormitory.mapper.RoomMapper;
import by.pdu.dormitory.ui.windows.SupportWindow;
import by.pdu.dormitory.util.ApplicationContext;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.fxml.FXML;
import javafx.scene.control.*;
import javafx.scene.control.cell.PropertyValueFactory;

public class InitTenant extends SupportWindow {
    @FXML
    protected TabPane choose;

    @FXML
    protected TextField fioField, numberField, workField;

    @FXML
    protected DatePicker birthdayPicker;

    @FXML
    protected ComboBox groupBox, roomBox;

    @FXML
    protected TableView propView, propTenantView;

    @FXML
    protected void addProp() {
        Object obj = propView.getSelectionModel().getSelectedItem();
        if (obj != null) {
            propView.getItems().remove(obj);
            propTenantView.getItems().add(obj);
        }
    }

    @FXML
    protected void removeProp() {
        Object obj = propTenantView.getSelectionModel().getSelectedItem();
        if (obj != null) {
            propTenantView.getItems().remove(obj);
            propView.getItems().add(obj);
        }
    }

    @Override
    public void setApplicationContext(ApplicationContext ctx) {
        super.setApplicationContext(ctx);
        GroupMapper groupMapper = ctx.getBean("groupMapper", GroupMapper.class);
        ObservableList<Group> groups = FXCollections.observableArrayList(groupMapper.getGroup());
        groupBox.setItems(groups);

        RoomMapper roomMapper = ctx.getBean("roomMapper", RoomMapper.class);
        ObservableList<Room> rooms = FXCollections.observableArrayList(roomMapper.getRoom());
        roomBox.setItems(rooms);

        ObservableList<TableColumn> columns = propView.getColumns();
        columns.get(0).setCellValueFactory(new PropertyValueFactory<Property, String>("name"));
        PropertyMapper propertyMapper = ctx.getBean("propertyMapper", PropertyMapper.class);
        ObservableList<Property> properties = FXCollections.observableArrayList(propertyMapper.getProperty());
        propView.getItems().addAll(properties);

        ObservableList<TableColumn> columnsEmpl = propTenantView.getColumns();
        columnsEmpl.get(0).setCellValueFactory(new PropertyValueFactory<Property, String>("name"));
    }
}
