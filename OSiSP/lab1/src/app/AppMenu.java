package app;

import app.scanner.SimpleAppScanner;

import java.io.IOException;

public class AppMenu {

    public static final int MENU_CASE_IOE = -1;
    public static final int MENU_CASE_BACK = 0;

    public static final int MENU_CASE_1_ADDING = 1;
    public static final int SUBMENU_1_ADDING_CASE_1_CHAR = 11;
    public static final int SUBMENU_1_ADDING_CASE_2_INT = 12;
    public static final int SUBMENU_1_ADDING_CASE_3_DOUBLE = 13;


    public static final int MENU_CASE_2_LIST = 2;
    public static final int SUBMENU_2_LIST_CASE_1_ADD_CHAR = 21;
    public static final int SUBMENU_2_LIST_CASE_2_ADD_INT = 22;
    public static final int SUBMENU_2_LIST_CASE_3_ADD_DOUBLE = 23;
    public static final int SUBMENU_2_LIST_CASE_4_REMOVE = 24;
    public static final int SUBMENU_2_LIST_CASE_5_SHOW = 25;
    public static final int SUBMENU_2_LIST_CASE_6_ACTION = 26;


    private SimpleAppScanner appScanner;

    public AppMenu(SimpleAppScanner appScanner) {
        this.appScanner = appScanner;
    }

    private int inputMenuCase() {
        try {
            return appScanner.readInt(":");
        } catch (IOException ioe) {
            return MENU_CASE_IOE;
        }
    }

    public int update() {
        System.out.println();
        System.out.println("1 - Single...");
        System.out.println("2 - List...");
        System.out.println("0 - Exit");

        int inputCase = inputMenuCase();

        switch (inputCase) {
            case MENU_CASE_1_ADDING:
                inputCase = submenuAdding();
                if (inputCase != 0) {
                    // возвращаем выбранные результат
                    return inputCase;
                }
                // ..
                break;
            case MENU_CASE_2_LIST:
                inputCase = submenuList();
                if (inputCase != 0) {
                    // возвращаем выбранные результат
                    return inputCase;
                }
                break;
            case MENU_CASE_IOE:
                System.out.println("Menu input error!");
                update();
                break;
        }
        return MENU_CASE_BACK;
    }

    private int submenuList() {
        System.out.println("1 - add char params");
        System.out.println("2 - add int params");
        System.out.println("3 - add double params");
        System.out.println("4 - remove item");
        System.out.println("5 - show the list");
        System.out.println("6 - process the list");
        System.out.println("0 - back");

        int inputCase = inputMenuCase();
        if (inputCase == MENU_CASE_IOE) {
            System.out.println("Menu input error!");
            return submenuList();
        } else {
            return inputCase + MENU_CASE_2_LIST * 10;
        }
    }

    private int submenuAdding() {
        System.out.println("1 - input char params");
        System.out.println("2 - input int params");
        System.out.println("3 - input double params");
        System.out.println("0 - back");

        int inputCase = inputMenuCase();
        if (inputCase == MENU_CASE_IOE) {
            System.out.println("Menu input error!");
            return submenuAdding();
        } else {
            return inputCase + MENU_CASE_1_ADDING * 10;
        }
    }


}
