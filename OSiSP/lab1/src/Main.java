import algorithm.Laborer;
import algorithm.ProLaborerImpl;
import app.AppMenu;
import app.parser.args.ArgsParser;
import app.scanner.SimpleAppScanner;
import app.scanner.SimpleAppScannerImpl;
import app.scanner.SimpleAppScannerImplEx;
import app.scanner.params.CharParamsScanner;
import app.scanner.params.DoubleParamsScanner;
import app.scanner.params.IntParamsScanner;
import param.ParamsSrc;
import result.ParamsRes;

import java.io.IOException;
import java.util.ArrayList;

public class Main {


    /**
     * Task 22
     * Даны три переменные: X, Y, Z. Если их значения упорядочены по возрастанию или убыванию, то удвоить их;
     * в противном случае заменить значение каждой переменной на противоположное.
     *
     * @param args - параметры командной строки
     * @author Andrew Yablonski
     */

    public static void main(String[] args) {
        SimpleAppScanner appScanner = new SimpleAppScannerImpl();
        //SimpleAppScanner appScanner = new SimpleAppScannerImplEx();

        // основной алгоритм
        Laborer laborer = new ProLaborerImpl();

        // список для хранения элементов элементов
        ArrayList<ParamsSrc> arrayList = new ArrayList<>();

        // меню приложения
        AppMenu appMenu = new AppMenu(appScanner);


        // проверка параметров командной строки
        new ArgsParser().checkArgs(args, new ArgsParser.Callback() {
            @Override
            public void addToList(ParamsSrc paramsSrc) {
                arrayList.add(paramsSrc);
            }

            @Override
            public void singleAction(ParamsSrc paramsSrc) {
                laborer.processThreeParams(paramsSrc, true);
            }
        });

        ParamsSrc paramsSrc;
        int menuCase = -1;
        // основной цикл
        while (menuCase != AppMenu.MENU_CASE_BACK) {
            menuCase = appMenu.update();
            switch (menuCase) {

                // ----------- Для одиночных элементов --------------
                case AppMenu.SUBMENU_1_ADDING_CASE_1_CHAR:
                    paramsSrc = new CharParamsScanner(appScanner).scannParams();
                    laborer.processThreeParams(paramsSrc, true);
                    break;

                case AppMenu.SUBMENU_1_ADDING_CASE_2_INT:
                    paramsSrc = new IntParamsScanner(appScanner).scannParams();
                    laborer.processThreeParams(paramsSrc, true);
                    break;

                case AppMenu.SUBMENU_1_ADDING_CASE_3_DOUBLE:
                    paramsSrc = new DoubleParamsScanner(appScanner).scannParams();
                    laborer.processThreeParams(paramsSrc, true);
                    break;
                // ----------- Для одиночных элементов --------------


                // ----------- Для элементов списка --------------
                case AppMenu.SUBMENU_2_LIST_CASE_1_ADD_CHAR:
                    paramsSrc = new CharParamsScanner(appScanner).scannParams();
                    arrayList.add(paramsSrc);
                    break;

                case AppMenu.SUBMENU_2_LIST_CASE_2_ADD_INT:
                    paramsSrc = new IntParamsScanner(appScanner).scannParams();
                    arrayList.add(paramsSrc);
                    break;

                case AppMenu.SUBMENU_2_LIST_CASE_3_ADD_DOUBLE:
                    paramsSrc = new DoubleParamsScanner(appScanner).scannParams();
                    arrayList.add(paramsSrc);
                    break;

                case AppMenu.SUBMENU_2_LIST_CASE_4_REMOVE:
                    try {
                        int itemIndex = appScanner.readInt("Item index to remove: ");
                        if (itemIndex >= 0 && itemIndex < arrayList.size()) {
                            arrayList.remove(itemIndex);
                            System.out.println("Item has been added. New size " + arrayList.size());
                        } else {
                            System.out.println("Cannot found item[id: " + itemIndex + "]. List size " + arrayList.size());
                        }
                    } catch (IOException e) {
                        System.out.println("Index input error!");
                    }
                    break;

                case AppMenu.SUBMENU_2_LIST_CASE_5_SHOW:
                    if (arrayList.size() > 0) {
                        System.out.println("Items list:");
                        for (int i = 0; i < arrayList.size(); i++) {
                            System.out.println("[" + i + "] " + arrayList.get(i));
                        }

                    /*
                        При помощи forEach
                    arrayList.forEach(System.out::println);

                    arrayList.forEach(threeParams -> {
                        System.out.println(threeParams);
                    });

                     */
                    } else {
                        System.out.println("Items list is empty");
                    }
                    break;

                case AppMenu.SUBMENU_2_LIST_CASE_6_ACTION:
                    if (arrayList.size() > 0) {
                        ParamsRes resParams;
                        System.out.println("Processed list:");
                        for (int i = 0; i < arrayList.size(); i++) {

                            resParams = laborer.processThreeParams(arrayList.get(i), false);
                            System.out.println("[" + i + "]  - " + resParams);
                        }
                        arrayList.clear();
                    } else {
                        System.out.println("Items list is empty");
                    }
                    break;

            }
        }
    }
}
