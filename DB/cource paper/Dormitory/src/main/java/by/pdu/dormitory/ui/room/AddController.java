package by.pdu.dormitory.ui.room;

import by.pdu.dormitory.domain.Inventory;
import by.pdu.dormitory.domain.Unit;
import by.pdu.dormitory.mapper.InventoryMapper;
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
import javafx.scene.control.TableColumn;
import javafx.scene.control.TableView;
import javafx.scene.control.TextField;
import javafx.scene.control.cell.PropertyValueFactory;

public class AddController extends InitRoom{
    @FXML
    private void add() {
        try {
            RoomMapper roomMapper = ctx.getBean("roomMapper", RoomMapper.class);
            Unit unit = (Unit) unitBox.getValue();
            if (unit == null) {
                AlertWindow.errorAlert("Выберите блок");
                return;
            }
            Long id = roomMapper.nextId();
            roomMapper.insertRoom(id, Double.parseDouble(squareField.getText()), Long.parseLong(countBetsField.getText()), unit.getNumber());
            for (Object inventory:inventRoomTable.getItems()){
                roomMapper.insertInventory(id,((Inventory)inventory).getId());
            }
            close(Window.CLICK_ADD);
        } catch (Exception ex) {
            AlertWindow.errorAlert(ex.getMessage());
            ex.printStackTrace();
        }
    }

}
