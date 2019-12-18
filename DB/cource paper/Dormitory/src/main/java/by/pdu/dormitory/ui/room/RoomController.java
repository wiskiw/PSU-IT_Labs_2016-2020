package by.pdu.dormitory.ui.room;


import by.pdu.dormitory.domain.Group;
import by.pdu.dormitory.domain.Inventory;
import by.pdu.dormitory.domain.Property;
import by.pdu.dormitory.domain.Room;
import by.pdu.dormitory.mapper.GroupMapper;
import by.pdu.dormitory.mapper.PropertyMapper;
import by.pdu.dormitory.mapper.RoomMapper;
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

public class RoomController extends TabController {

    private TableView table;

    public RoomController(TableView table) {
        super(table);
        this.table = table;

        ObservableList<TableColumn> columns = table.getColumns();
        columns.get(0).setCellValueFactory(new PropertyValueFactory<Room, String>("unit"));
        columns.get(1).setCellValueFactory(new PropertyValueFactory<Room, Double>("square"));
        columns.get(2).setCellValueFactory(new PropertyValueFactory<Room, Long>("countBets"));
    }

    @Override
    public void add() {
        try {
            Stage stage = modalWindow("fxml/room/add.fxml","Добавить комнату");
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
            Room obj = (Room) table.getSelectionModel().getSelectedItem();
            if (obj != null) {
                RoomMapper mapper = ctx.getBean("roomMapper", RoomMapper.class);
                mapper.deleteRoom(obj.getId());
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
        RoomMapper roomMapper = ctx.getBean("roomMapper",RoomMapper.class);
        ObservableList<Room> rooms = FXCollections.observableArrayList(roomMapper.getRoom());
        table.setItems(rooms);
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
            UpdateController controller = (UpdateController)loader.loadModal("fxml/room/update.fxml","Редактировать комнату",update,stage);
            controller.setRoom((Room) obj);
            update.showAndWait();
            Object data = update.getUserData();
            if (data != null && (Integer) data == Window.CLICK_EDIT) updateView();
        }catch (Exception ex){
            AlertWindow.errorAlert(ex.getMessage());
            ex.printStackTrace();
        }
    }


}
