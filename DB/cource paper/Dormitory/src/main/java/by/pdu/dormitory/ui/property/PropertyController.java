package by.pdu.dormitory.ui.property;


import by.pdu.dormitory.domain.Faculty;
import by.pdu.dormitory.domain.Inventory;
import by.pdu.dormitory.domain.Post;
import by.pdu.dormitory.domain.Property;
import by.pdu.dormitory.mapper.PostMapper;
import by.pdu.dormitory.mapper.PropertyMapper;
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

public class PropertyController extends TabController {

    private TableView table;

    public PropertyController(TableView table) {
        super(table);
        this.table = table;
        ObservableList<TableColumn> columnsFaculty = table.getColumns();
        columnsFaculty.get(0).setCellValueFactory(new PropertyValueFactory<Property, Long>("id"));
        columnsFaculty.get(1).setCellValueFactory(new PropertyValueFactory<Property, String>("name"));
    }

    @Override
    public void add() {
        try {
            Stage stage = modalWindow("fxml/property/add.fxml","Добавить имущество");
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
            Property obj = (Property) table.getSelectionModel().getSelectedItem();
            if (obj != null) {
                PropertyMapper mapper = ctx.getBean("propertyMapper", PropertyMapper.class);
                mapper.deleteProperty(obj.getId());
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
        PropertyMapper propertyMapper = ctx.getBean("propertyMapper",PropertyMapper.class);
        ObservableList<Property> properties = FXCollections.observableArrayList(propertyMapper.getProperty());
        table.setItems(properties);
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
            UpdateController controller = (UpdateController)loader.loadModal("fxml/property/update.fxml","Редактировать имущество",update,stage);
            controller.setProperty((Property) obj);
            update.showAndWait();
            Object data = update.getUserData();
            if (data != null && (Integer) data == Window.CLICK_EDIT) updateView();
        }catch (Exception ex){
            AlertWindow.errorAlert(ex.getMessage());
            ex.printStackTrace();
        }
    }


}
