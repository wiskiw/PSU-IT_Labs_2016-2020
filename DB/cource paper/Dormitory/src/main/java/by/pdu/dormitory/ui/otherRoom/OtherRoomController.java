package by.pdu.dormitory.ui.otherRoom;


import by.pdu.dormitory.domain.Inventory;
import by.pdu.dormitory.domain.OtherRoom;
import by.pdu.dormitory.domain.Post;
import by.pdu.dormitory.mapper.InventoryMapper;
import by.pdu.dormitory.mapper.OtherRoomMapper;
import by.pdu.dormitory.mapper.PostMapper;
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

public class OtherRoomController extends TabController {

    private TableView table;

    public OtherRoomController(TableView table) {
        super(table);
        this.table = table;
        ObservableList<TableColumn> columnsFaculty = table.getColumns();
        columnsFaculty.get(0).setCellValueFactory(new PropertyValueFactory<OtherRoom, Long>("id"));
        columnsFaculty.get(1).setCellValueFactory(new PropertyValueFactory<OtherRoom, String>("name"));
    }

    @Override
    public void add() {
        try {
            Stage stage = modalWindow("fxml/otherRoom/add.fxml","Добавить нежилую комнату");
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
            OtherRoom obj = (OtherRoom) table.getSelectionModel().getSelectedItem();
            if (obj != null) {
                OtherRoomMapper mapper = ctx.getBean("otherRoomMapper", OtherRoomMapper.class);
                mapper.deleteOtherRoom(obj.getId());
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
        OtherRoomMapper otherRoomMapper = ctx.getBean("otherRoomMapper",OtherRoomMapper.class);
        ObservableList<OtherRoom> otherRooms = FXCollections.observableArrayList(otherRoomMapper.getOtherRoom());
        table.setItems(otherRooms);
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
            UpdateController controller = (UpdateController)loader.loadModal("fxml/otherRoom/update.fxml","Редактировать нежилую комнату",update,stage);
            controller.setOtherRoom((OtherRoom) obj);
            update.showAndWait();
            Object data = update.getUserData();
            if (data != null && (Integer) data == Window.CLICK_EDIT) updateView();
        }catch (Exception ex){
            AlertWindow.errorAlert(ex.getMessage());
            ex.printStackTrace();
        }
    }


}
