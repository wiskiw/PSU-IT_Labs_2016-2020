package basics;


@SuppressWarnings("ALL")
public class JavaBasics {


    private void stringConcatenation() {
        String firstName = "Amit";
        String lastName = "Shekhar";

        System.out.println("My name is: " +
                firstName + " " + lastName);
    }


    private void smartCasting(Object obj) {
        if (obj instanceof Car) {

            // error : obj.getSpeed()

            Car car = (Car) obj;
            System.out.println("Speed : " + car.getSpeed());
        }
    }


    private void multipleConditions(int n) {
        if (n >= 0 && n <= 150) {
            // do something
        }


        for (int i = 0; i < 20; i++) {
            System.out.println("id:" + i);
        }


        switch (n) {
            case 1:
                System.out.println("One");
                break;
            case 2:
                System.out.println("Two");
                break;
            case 3:
                System.out.println("Three");
                break;
            case 4:
            case 5:
            case 6:
                System.out.println(" 3 < n < 7 ");
                break;
            default:
                System.out.println(" n >= 7 ");
        }

    }


    private void nullSafety() {
        String msg = null;

        // NullPointerException
        System.out.println("len: " + msg.length());

        if (msg != null) {
            System.out.println("len: " + msg.length());
        } else {
            System.out.println("len: 0");
        }
    }


    private int method0(int value) {
        return 2 * value;
    }

    // Перегрузка метода
    private int method0() {
        // Значение по умолчанию
        return method0(0);
    }


    private String concatinate(char prefix, String a, char postfix) {
        return prefix + a + postfix;
    }

    // перегрузка 1
    private String concatinate(char prefix, String a) {
        return concatinate(prefix, a, '.');
    }

    // перегрузка 2
    private String concatinate(String a, char postfix) {
        return concatinate('.', a, postfix);
    }


    private void callConcatinatin() {
        System.out.println(concatinate('.', "hello", '-'));

        System.out.println(concatinate('+', "hello"));
        System.out.println(concatinate('+', "hello", '-'));
        System.out.println(concatinate("hello", '-'));
    }


}
