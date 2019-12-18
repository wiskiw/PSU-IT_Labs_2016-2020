package by.pdu.dormitory.ui.room;

import by.pdu.dormitory.domain.*;
import by.pdu.dormitory.mapper.FacultyMapper;
import by.pdu.dormitory.mapper.GroupMapper;
import by.pdu.dormitory.mapper.RoomMapper;
import by.pdu.dormitory.mapper.UnitMapper;
import by.pdu.dormitory.ui.windows.SupportWindow;
import by.pdu.dormitory.ui.windows.Window;
import by.pdu.dormitory.util.AlertWindow;
import by.pdu.dormitory.util.ApplicationContext;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.fxml.FXML;
import javafx.scene.control.ComboBox;
import javafx.scene.control.TextField;


public class UpdateController extends InitRoom {
    private Room room;

    @FXML
    private TextField squareField,countBetsField;

    @FXML
    private ComboBox unitBox;

    @FXML
    private void update() {
        try {
            RoomMapper roomMapper = ctx.getBean("roomMapper",RoomMapper.class);
            Unit unit = (Unit) unitBox.getValue();
            if (unit == null) {
                AlertWindow.errorAlert("Выберите блок");
                return;
            }
            roomMapper.updateRoom(room.getId(),Double.parseDouble(squareField.getText()),Long.parseLong(countBetsField.getText()),unit.getNumber());
            roomMapper.deleteInventory(room.getId());
            for (Object inventory:inventRoomTable.getItems()){
                roomMapper.insertInventory(room.getId(),((Inventory)inventory).getId());
            }
            close(Window.CLICK_EDIT);
        } catch (Exception ex) {
            AlertWindow.errorAlert(ex.getMessage());
            ex.printStackTrace();
        }
    }

    public void setRoom(Room room) {
        this.room = room;
        squareField.setText(room.getSquare().toString());
        countBetsField.setText(room.getCountBets().toString());
        unitBox.getSelectionModel().select(room.getUnit());

        RoomMapper mapper = ctx.getBean("roomMapper",RoomMapper.class);
        for (Inventory inventory : mapper.getInventory(room.getId())){
            inventRoomTable.getItems().add(inventory);
            inventTable.getItems().remove(inventory);
        }
    }

    @Override
    public void setApplicationContext(ApplicationContext ctx) {
        super.setApplicationContext(ctx);
        UnitMapper unitMapper = ctx.getBean("unitMapper",UnitMapper.class);
        ObservableList<Unit> units = FXCollections.observableArrayList(unitMapper.getUnit());
        unitBox.setItems(units);
    }
}
