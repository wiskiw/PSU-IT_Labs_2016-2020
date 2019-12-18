package by.pdu.dormitory.ui.unit;


import by.pdu.dormitory.domain.Property;
import by.pdu.dormitory.domain.Tenant;
import by.pdu.dormitory.domain.Unit;
import by.pdu.dormitory.mapper.PropertyMapper;
import by.pdu.dormitory.mapper.TenantMapper;
import by.pdu.dormitory.mapper.UnitMapper;
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

public class UnitController extends TabController {

    private TableView table;

    public UnitController(TableView table) {
        super(table);
        this.table = table;
        ObservableList<TableColumn> columnsFaculty = table.getColumns();
        columnsFaculty.get(0).setCellValueFactory(new PropertyValueFactory<Unit, Long>("number"));
    }

    @Override
    public void add() {
        try {
            Stage stage = modalWindow("fxml/unit/add.fxml","Добавить блок");
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
            Unit obj = (Unit) table.getSelectionModel().getSelectedItem();
            if (obj != null) {
                UnitMapper mapper = ctx.getBean("unitMapper", UnitMapper.class);
                mapper.deleteUnit(obj.getNumber());
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
        UnitMapper unitMapper = ctx.getBean("unitMapper",UnitMapper.class);
        ObservableList<Unit> units = FXCollections.observableArrayList(unitMapper.getUnit());
        table.setItems(units);
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
            UpdateController controller = (UpdateController)loader.loadModal("fxml/unit/update.fxml","Редактировать блок",update,stage);
            controller.setUnit((Unit) obj);
            update.showAndWait();
            Object data = update.getUserData();
            if (data != null && (Integer) data == Window.CLICK_EDIT) updateView();
        }catch (Exception ex){
            AlertWindow.errorAlert(ex.getMessage());
            ex.printStackTrace();
        }
    }


}
