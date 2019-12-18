package functions;

@SuppressWarnings("ALL")
public class Main {




    public static class StringUtils {

        static String getFirstWord(String s, String separator) {
            int index = s.indexOf(separator);

            if (index < 0) {
                return s;
            } else {
                return s.substring(0, index);
            }
        }

        static String getFirstWord(String s) {
            return getFirstWord(s, " ");
        }

    }

    // ***************************************


    public static void main(String[] args) {
        String fullName = "Ivan Ivanov, Ivanovich";

        System.out.println(StringUtils.getFirstWord(fullName));

        System.out.println(StringUtils.getFirstWord(fullName, ","));

    }

}
