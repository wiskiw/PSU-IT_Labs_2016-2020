package com.company;

public class AppMenu {

    private SimpleAppScanner simpleAppScanner;

    public AppMenu(SimpleAppScanner simpleAppScanner) {
        this.simpleAppScanner = simpleAppScanner;
    }

    public int showMenu() {
        System.out.println();
        System.out.println("1 - ...");
        System.out.println("2 - Add a computer");
        System.out.println("3 - Edit a computer");
        System.out.println("4 - Delete a computer");
        System.out.println("5 - Show list");
        System.out.println("6 - Save list");
        System.out.println("7 - Load list");
        System.out.println("0 - Exit");

        int menuItem = simpleAppScanner.readInt(": ", false, 0);
        System.out.println();
        return menuItem;
    }


}
