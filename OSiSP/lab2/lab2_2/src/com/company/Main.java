package com.company;

import java.io.File;
import java.util.ArrayList;

public class Main {

    /*
    2. Реализовать класс для хранния сущности компьютер с его характеристиками,
        обеспесить пользовательский интерфейс по добавлению, удалению и редактированию компьюетров в памяти.
        Дополнительно используя механизм сериализации реализовать загрузку и выгрузку коvпьютеров в(из) файла.
     */

    public static void main(String[] args) {
        // write your code here

        SimpleAppScanner simpleAppScanner = new SimpleAppScanner();
        ComputerEntityIO computerEntityIO = new ComputerEntityIO(simpleAppScanner);
        File comFile = ComputerRoom.getDefaultFile();
        AppMenu appMenu = new AppMenu(simpleAppScanner);

        ArrayList<ComputerEntity> computerList = new ArrayList<>();


        /*
        ComputerEntity comp1 = new ComputerEntity(1000, 6000, "Intel", "Nvidia");
        ComputerEntity comp2 = new ComputerEntity(2000, 6000, "Intel 2", "Nvidia");

        computerList.add(comp1);
        computerList.add(comp2);
        */

        int intA;
        do {
            switch (appMenu.showMenu()) {
                case 1:

                    break;

                case 2:
                    computerList.add(computerEntityIO.readNewOne());
                    System.out.println();
                    break;

                case 3:
                    if (computerList.size() == 0) {
                        System.out.println("List is empty, nothing to edit!");
                    } else {
                        intA = simpleAppScanner.readInt("Edit item (list size " + computerList.size() + ") id: ",
                                false, 0);
                        if (intA < 0 || intA >= computerList.size()) {
                            System.err.println(intA + " - wrong item index!");
                        } else {
                            computerEntityIO.editOne(computerList.get(intA));
                        }
                    }
                    break;

                case 4:
                    if (computerList.size() == 0) {
                        System.out.println("List is empty, nothing to remove!");
                    } else {
                        intA = simpleAppScanner.readInt("Remove item (list size " + computerList.size() + ") id: ",
                                false, 0);
                        if (intA < 0 || intA >= computerList.size()) {
                            System.err.println(intA + " - wrong item index!");
                        } else {
                            computerList.remove(intA);
                        }
                    }
                    break;

                case 5:
                    System.out.println("List size " + computerList.size() + " : ");
                    for (int i = 0; i < computerList.size(); i++) {
                        System.out.println("[" + i + "] " + computerList.get(i));
                    }
                    break;

                case 6:
                    ComputerRoom.save(comFile, computerList);
                    System.out.println("Saved!");
                    break;

                case 7:
                    computerList = ComputerRoom.read(comFile);
                    System.out.println("Loaded " + computerList.size() + " computer(s)");
                    break;

                case 0:
                    return;
            }
        } while (true);
    }
}
