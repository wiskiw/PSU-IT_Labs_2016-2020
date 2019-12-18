package by.pdu.dormitory.ui.windows;

public abstract class SupportWindow extends Window {

    protected void close(int code) {
        stage.setUserData(code);
        close();
    }

    protected void close(){
        commit();
        stage.close();
    }
}
