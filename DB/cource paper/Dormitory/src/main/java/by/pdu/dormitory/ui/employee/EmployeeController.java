package by.pdu.dormitory.ui.employee;


import by.pdu.dormitory.domain.Employee;
import by.pdu.dormitory.mapper.EmployeeMapper;
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

public class EmployeeController extends TabController {

    private TableView table;

    public EmployeeController(TableView table) {
        super(table);
        this.table = table;

        ObservableList<TableColumn> columns = table.getColumns();
        columns.get(0).setCellValueFactory(new PropertyValueFactory<Employee, String>("FIO"));
        columns.get(1).setCellValueFactory(new PropertyValueFactory<Employee, String>("post"));
        columns.get(2).setCellValueFactory(new PropertyValueFactory<Employee, String>("otherRoom"));
    }

    @Override
    public void add() {
        try {
            Stage stage = modalWindow("fxml/employee/add.fxml", "Добавить сотрудника");
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
            Employee obj = (Employee) table.getSelectionModel().getSelectedItem();
            if (obj != null) {
                EmployeeMapper mapper = ctx.getBean("employeeMapper", EmployeeMapper.class);
                mapper.deleteEmployee(obj.getId());
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
        EmployeeMapper employeeMapper = ctx.getBean("employeeMapper", EmployeeMapper.class);
        ObservableList<Employee> employees = FXCollections.observableArrayList(employeeMapper.getEmployee());
        table.setItems(employees);
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
            UpdateController controller = (UpdateController) loader.loadModal("fxml/employee/update.fxml", "Редактировать сотрудника", update, stage);
            controller.setEmployee((Employee) obj);
            update.showAndWait();
            Object data = update.getUserData();
            if (data != null && (Integer) data == Window.CLICK_EDIT) updateView();
        } catch (Exception ex) {
            AlertWindow.errorAlert(ex.getMessage());
            ex.printStackTrace();
        }
    }


}
