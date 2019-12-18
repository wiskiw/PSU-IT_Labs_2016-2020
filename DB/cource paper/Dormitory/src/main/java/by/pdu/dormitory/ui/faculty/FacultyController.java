package by.pdu.dormitory.ui.faculty;


import by.pdu.dormitory.domain.Employee;
import by.pdu.dormitory.domain.Faculty;
import by.pdu.dormitory.mapper.EmployeeMapper;
import by.pdu.dormitory.mapper.FacultyMapper;
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

public class FacultyController extends TabController {

    private TableView table;

    public FacultyController(TableView table) {
        super(table);
        this.table = table;

        ObservableList<TableColumn> columnsFaculty = table.getColumns();
        columnsFaculty.get(0).setCellValueFactory(new PropertyValueFactory<Faculty, Long>("id"));
        columnsFaculty.get(1).setCellValueFactory(new PropertyValueFactory<Faculty, String>("name"));
    }

    @Override
    public void add() {
        try {
            Stage stage = modalWindow("fxml/faculty/add.fxml","Добавить факультет");
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
            Faculty obj = (Faculty) table.getSelectionModel().getSelectedItem();
            if (obj != null) {
                FacultyMapper mapper = ctx.getBean("facultyMapper", FacultyMapper.class);
                mapper.deleteFaculty(obj.getId());
            }else{
                AlertWindow.errorAlert("Выберите элемент");
            }
        } catch (Exception ex) {
            AlertWindow.errorAlert(ex.getMessage());
            ex.printStackTrace();
        }
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
            UpdateController controller = (UpdateController)loader.loadModal("fxml/faculty/update.fxml","Редактировать фвкультет",update,stage);
            controller.setFaculty((Faculty) obj);
            update.showAndWait();
            Object data = update.getUserData();
            if (data != null && (Integer) data == Window.CLICK_EDIT) updateView();
        }catch (Exception ex){
            AlertWindow.errorAlert(ex.getMessage());
            ex.printStackTrace();
        }
    }

    @Override
    public void updateView() {
        FacultyMapper facultyMapper = ctx.getBean("facultyMapper",FacultyMapper.class);
        ObservableList<Faculty> faculties = FXCollections.observableArrayList(facultyMapper.getFaculty());
        table.setItems(faculties);
    }
}
