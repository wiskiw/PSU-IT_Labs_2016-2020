package by.pdu.dormitory.ui.inventory;

import by.pdu.dormitory.domain.Inventory;
import by.pdu.dormitory.mapper.InventoryMapper;
import by.pdu.dormitory.ui.windows.SupportWindow;
import by.pdu.dormitory.ui.windows.Window;
import by.pdu.dormitory.util.AlertWindow;
import javafx.fxml.FXML;
import javafx.scene.control.TextField;
import javafx.stage.Stage;



public class UpdateController extends SupportWindow {
    private Inventory inventory;

    @FXML
    private TextField nameText;

    @FXML
    private void update() {
        try {
            InventoryMapper inventoryMapper = ctx.getBean("inventoryMapper",InventoryMapper.class);
            inventoryMapper.updateInventory(inventory.getId(), nameText.getText());
            close(Window.CLICK_EDIT);
        } catch (Exception ex) {
            AlertWindow.errorAlert(ex.getMessage());
            ex.printStackTrace();
        }
    }

    public void setInventory(Inventory inventory) {
        this.inventory = inventory;
        nameText.setText(inventory.getName());
    }
}
