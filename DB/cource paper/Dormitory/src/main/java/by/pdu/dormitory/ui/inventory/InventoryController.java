package by.pdu.dormitory.ui.inventory;


import by.pdu.dormitory.domain.Group;
import by.pdu.dormitory.domain.Inventory;
import by.pdu.dormitory.mapper.GroupMapper;
import by.pdu.dormitory.mapper.InventoryMapper;
import by.pdu.dormitory.ui.windows.TabController;
import by.pdu.dormitory.ui.windows.Window;
import by.pdu.dormitory.util.AlertWindow;
import by.pdu.dormitory.util.LoadFXML;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.scene.control.TableColumn;
import javafx.scene.control.TableView;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.stage.Stage;

public class InventoryController extends TabController {

    private TableView table;

    public InventoryController(TableView table) {
        super(table);
        this.table = table;

        ObservableList<TableColumn> columns = table.getColumns();
        columns.get(0).setCellValueFactory(new PropertyValueFactory<Inventory, Long>("id"));
        columns.get(1).setCellValueFactory(new PropertyValueFactory<Inventory, String>("name"));
    }

    @Override
    public void add() {
        try {
            Stage stage = modalWindow("fxml/inventory/add.fxml","Добавить инвентарь");
            Object data = stage.getUserData();
            if (data != null && (Integer) data == Window.CLICK_ADD) updateView();
        } catch (Exception ex) {
            AlertWindow.errorAlert(ex.getMessage());
            ex.printStackTrace();
        }
    }

    @Override
    public void remove() {
        try {
            Inventory obj = (Inventory) table.getSelectionModel().getSelectedItem();
            if (obj != null) {
                InventoryMapper mapper = ctx.getBean("inventoryMapper", InventoryMapper.class);
                mapper.deleteInventory(obj.getId());
            }else{
                AlertWindow.errorAlert("Выберите элемент");
            }
        } catch (Exception ex) {
            AlertWindow.errorAlert(ex.getMessage());
            ex.printStackTrace();
        }
    }

    @Override
    public void updateView() {
        InventoryMapper inventoryMapper = ctx.getBean("inventoryMapper",InventoryMapper.class);
        ObservableList<Inventory> inventories = FXCollections.observableArrayList(inventoryMapper.getInventory());
        table.setItems(inventories);
    }

    @Override
    public void update() {
        try{
            Object obj = table.getSelectionModel().getSelectedItem();
            if (obj == null) {
                AlertWindow.errorAlert("Нет выбранного элемента");
                return;
            }
            Stage update = new Stage();
            LoadFXML loader = ctx.getBean("loader", LoadFXML.class);
            UpdateController controller = (UpdateController)loader.loadModal("fxml/inventory/update.fxml","Редактировать инвентарь",update,stage);
            controller.setInventory((Inventory) obj);
            update.showAndWait();
            Object data = update.getUserData();
            if (data != null && (Integer) data == Window.CLICK_EDIT) updateView();
        }catch (Exception ex){
            AlertWindow.errorAlert(ex.getMessage());
            ex.printStackTrace();
        }
    }


}
