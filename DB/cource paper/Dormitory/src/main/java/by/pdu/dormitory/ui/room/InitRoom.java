package by.pdu.dormitory.ui.room;

import by.pdu.dormitory.domain.Inventory;
import by.pdu.dormitory.domain.Unit;
import by.pdu.dormitory.mapper.InventoryMapper;
import by.pdu.dormitory.mapper.UnitMapper;
import by.pdu.dormitory.ui.windows.SupportWindow;
import by.pdu.dormitory.util.ApplicationContext;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.fxml.FXML;
import javafx.scene.control.ComboBox;
import javafx.scene.control.TableColumn;
import javafx.scene.control.TableView;
import javafx.scene.control.TextField;
import javafx.scene.control.cell.PropertyValueFactory;

public class InitRoom  extends SupportWindow {
    @FXML
    protected TextField squareField, countBetsField;

    @FXML
    protected TableView inventTable, inventRoomTable;

    @FXML
    protected ComboBox unitBox;

    @FXML
    public void initialize() {
        ObservableList<TableColumn> columns = inventTable.getColumns();
        columns.get(0).setCellValueFactory(new PropertyValueFactory<Inventory, String>("name"));

        columns = inventRoomTable.getColumns();
        columns.get(0).setCellValueFactory(new PropertyValueFactory<Inventory, String>("name"));
    }

    @FXML
    protected void addInv() {
        Object obj = inventTable.getSelectionModel().getSelectedItem();
        if (obj != null) {
            inventTable.getItems().remove(obj);
            inventRoomTable.getItems().add(obj);
        }
    }

    @FXML
    protected void removeInv() {
        Object obj = inventRoomTable.getSelectionModel().getSelectedItem();
        if (obj != null) {
            inventRoomTable.getItems().remove(obj);
            inventTable.getItems().add(obj);
        }
    }

    @Override
    public void setApplicationContext(ApplicationContext ctx) {
        super.setApplicationContext(ctx);
        UnitMapper unitMapper = ctx.getBean("unitMapper", UnitMapper.class);
        ObservableList<Unit> units = FXCollections.observableArrayList(unitMapper.getUnit());
        unitBox.setItems(units);

        InventoryMapper inventoryMapper = ctx.getBean("inventoryMapper", InventoryMapper.class);
        ObservableList<Inventory> inventories = FXCollections.observableArrayList(inventoryMapper.getInventory());
        inventTable.setItems(inventories);

    }
}
