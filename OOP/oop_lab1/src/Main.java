import company.Company;

public class Main {

    public static void main(String[] args) {
        Company myCompany = new Company();
        myCompany.setId(1223);
        myCompany.setAddress("Pushkina street");
        myCompany.setName("Epam");
        myCompany.mainLoop();
/*
        Order o = new Order("iOS app for cats", 999);
        o.setCustomer("VASYA");

        myCompany.addOrder(o);
        myCompany.addOrder(new Order("Turtles dating chat", 4324));

        myCompany.updateOrderProgressState(o);

        myCompany.printOrderList();*/
    }

}
