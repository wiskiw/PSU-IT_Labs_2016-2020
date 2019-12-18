package by.pdu.dormitory.ui.group;


import by.pdu.dormitory.domain.Faculty;
import by.pdu.dormitory.domain.Group;
import by.pdu.dormitory.domain.Inventory;
import by.pdu.dormitory.mapper.FacultyMapper;
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

public class GroupController extends TabController {

    private TableView table;

    public GroupController(TableView table) {
        super(table);
        this.table = table;

        ObservableList<TableColumn> columns = table.getColumns();
        columns.get(0).setCellValueFactory(new PropertyValueFactory<Inventory, String>("name"));
        columns.get(1).setCellValueFactory(new PropertyValueFactory<Inventory, String>("faculty"));
    }

    @Override
    public void add() {
        try {
            Stage stage = modalWindow("fxml/group/add.fxml","Добавить группу");
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
            Group obj = (Group) table.getSelectionModel().getSelectedItem();
            if (obj != null) {
                GroupMapper mapper = ctx.getBean("groupMapper", GroupMapper.class);
                mapper.deleteGroup(obj.getId());
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
        GroupMapper groupMapper = ctx.getBean("groupMapper",GroupMapper.class);
        ObservableList<Group> groups = FXCollections.observableArrayList(groupMapper.getGroup());
        table.setItems(groups);
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
            UpdateController controller = (UpdateController)loader.loadModal("fxml/group/update.fxml","Редактировать группу",update,stage);
            controller.setGroup((Group) obj);
            update.showAndWait();
            Object data = update.getUserData();
            if (data != null && (Integer) data == Window.CLICK_EDIT) updateView();
        }catch (Exception ex){
            AlertWindow.errorAlert(ex.getMessage());
            ex.printStackTrace();
        }
    }


}
