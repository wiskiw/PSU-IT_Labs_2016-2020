public class Main {

    public static void main(String[] args) {
        Transport.getTransportList().add(new Express(10));
        Transport.getTransportList().add(new Car("RED", 60));
        Transport.getTransportList().add(new Car("GREEN", 20));
        Transport.getTransportList().add(new Express(20));
        Transport.getTransportList().add(new Car("BLUE", 85));

        Transport.printList();

        /*
            ~Transport:
                ~Train:
                    - Express
                 - Car
         */
    }

}
