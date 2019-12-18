package by.pdu.dormitory.ui.tenant;


import by.pdu.dormitory.domain.EmployeeTenant;
import by.pdu.dormitory.domain.Room;
import by.pdu.dormitory.domain.Student;
import by.pdu.dormitory.domain.Tenant;
import by.pdu.dormitory.mapper.RoomMapper;
import by.pdu.dormitory.mapper.TenantMapper;
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

public class TenantController extends TabController {

    private TableView table;

    public TenantController(TableView table) {
        super(table);
        this.table = table;

        ObservableList<TableColumn> columns = table.getColumns();
        columns.get(0).setCellValueFactory(new PropertyValueFactory<Tenant, String>("FIO"));
        columns.get(1).setCellValueFactory(new PropertyValueFactory<Tenant, String>("unit"));
        columns.get(2).setCellValueFactory(new PropertyValueFactory<Tenant, String>("type"));
    }

    @Override
    public void add() {
        try {
            Stage stage = modalWindow("fxml/tenant/add.fxml", "Добавить жильца");
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
            Tenant obj = (Tenant) table.getSelectionModel().getSelectedItem();
            if (obj != null) {
                TenantMapper mapper = ctx.getBean("tenantMapper", TenantMapper.class);
                mapper.deleteTenant(obj.getId());
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
        TenantMapper tenantMapper = ctx.getBean("tenantMapper", TenantMapper.class);
        ObservableList<EmployeeTenant> employees = FXCollections.observableArrayList(tenantMapper.getEmployeeTenant());
        ObservableList<Student> students = FXCollections.observableArrayList(tenantMapper.getStudent());
        ObservableList list = FXCollections.observableArrayList();
        list.addAll(employees);
        list.addAll(students);
        table.setItems(list);
    }

    @Override
    public void update() {
        try {
            Object obj = table.getSelectionModel().getSelectedItem();
            if (obj == null) {
                AlertWindow.errorAlert("Нет выбранного элемента");
                return;
            }
            Stage update = new Stage();
            LoadFXML loader = ctx.getBean("loader", LoadFXML.class);
            UpdateController controller = (UpdateController) loader.loadModal("fxml/tenant/update.fxml", "Редактировать жильца", update, stage);
            controller.setTenant((Tenant) obj);
            update.showAndWait();
            Object data = update.getUserData();
            if (data != null && (Integer) data == Window.CLICK_EDIT) updateView();
        } catch (Exception ex) {
            AlertWindow.errorAlert(ex.getMessage());
            ex.printStackTrace();
        }
    }
}
