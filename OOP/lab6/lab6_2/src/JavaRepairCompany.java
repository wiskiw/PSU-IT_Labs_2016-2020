public class JavaRepairCompany {

    private static JavaRepairCompany instance;


    public static JavaRepairCompany getInstance() {
        if (instance == null) {
            instance = new JavaRepairCompany();
        }
        return instance;
    }

    private JavaRepairCompany() {

    }


    private final String name = "JavaRepairCompany";
    private String address = "Belarus, Polotsk";
    private String tel = "";

    public void startWork() {
        System.out.println(getName() + " start working in " + getAddress());
    }

    public String getName() {
        return name;
    }

    public String getAddress() {
        return address;
    }

    public String getTel() {
        return tel;
    }

    public void changeTel(String tel) {
        this.tel = tel;
    }

    public void changeAddress(String address) {
        this.address = address;
    }
}
