package app.parser.args;

import param.ParamsCharSrc;
import param.ParamsDoubleSrc;
import param.ParamsIntSrc;
import param.ParamsSrc;

public class ArgsParser {

    /**
     * Обработка меню приложения.
     * Значение массива аргументов
     * [0] - value type : 1-char, 2-int, 3-double
     * [1] - destination : 1-single, 2-list
     * [2] - A value
     * [3] - B value
     * [4] - C value
     *
     * @param args     - аргументы коммандной строки
     * @param callback - метод обратного вызова для пунктов меню
     * @return true - если параметры юыли найдены
     */
    public boolean checkArgs(String[] args, Callback callback) {
        if (args.length == 5) {
            ParamsSrc paramsSrc = null;
            try {
                int action = Short.parseShort(args[1].trim());
                int valueType = Short.parseShort(args[0].trim());
                switch (valueType) {
                    case 1:
                        paramsSrc = new ParamsCharSrc();
                        paramsSrc.setA(args[0].trim().charAt(0));
                        paramsSrc.setB(args[1].trim().charAt(0));
                        paramsSrc.setC(args[2].trim().charAt(0));
                        break;
                    case 2:
                        paramsSrc = new ParamsIntSrc();
                        paramsSrc.setA(Integer.parseInt(args[0].trim()));
                        paramsSrc.setB(Integer.parseInt(args[1].trim()));
                        paramsSrc.setC(Integer.parseInt(args[2].trim()));
                        break;
                    case 3:
                        paramsSrc = new ParamsDoubleSrc();
                        paramsSrc.setA(Double.parseDouble(args[0].trim()));
                        paramsSrc.setB(Double.parseDouble(args[1].trim()));
                        paramsSrc.setC(Double.parseDouble(args[2].trim()));
                        break;
                }


                assert paramsSrc != null;
                System.out.println("Detected args params: " + paramsSrc.toString());
                System.out.println("Detected args action: " + (action == 1 ? "single" : "list"));

                switch (action) {
                    case 1:
                        callback.singleAction(paramsSrc);
                        break;
                    case 2:
                        callback.addToList(paramsSrc);
                        break;
                }
                return true;

            } catch (Exception ex) {
                System.out.println("Wrong console arguments! '" + String.join(", ", args) + "'");
            }
        }
        return false;
    }

    public interface Callback {
        void addToList(ParamsSrc paramsSrc);

        void singleAction(ParamsSrc paramsSrc);
    }

}
