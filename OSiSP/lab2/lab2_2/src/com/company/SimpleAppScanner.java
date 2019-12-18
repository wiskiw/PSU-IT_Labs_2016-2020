package com.company;


import java.io.IOException;
import java.util.Scanner;

/**
 * Класс для ввода данных с клавиатуры
 *
 * @author Andrew Yablonski
 */

public class SimpleAppScanner {

    private Scanner scanner;

    /**
     * Кинструсктор, инициализация сканера
     */
    public SimpleAppScanner() {
        this.scanner = new Scanner(System.in);
    }

    /**
     * Считывает дробное значение
     *
     * @param msg сообщение для отображения перед вводом
     * @return возвращает введенное значение
     */
    public int readInt(String msg, boolean allowEmpty, int defaultValue) {
        if (msg.isEmpty()) {
            msg = "Enter a number (int): ";
        }
        System.out.print(msg);
        String stringInput;
        while (true) {
            try {
                stringInput = scanner.nextLine().trim();
                if (allowEmpty) {
                    if (stringInput.isEmpty()) {
                        return defaultValue;
                    } else {
                        return Integer.parseInt(stringInput.trim());
                    }
                } else {
                    return Integer.parseInt(stringInput.trim());
                }
            } catch (Exception ex) {
                // NumberFormatException
                System.out.print("Int input error, try again: ");
            }
        }
    }


    /**
     * Считывает дробное значение
     *
     * @param msg сообщение для отображения перед вводом
     * @return возвращает введенное значение
     */
    public double readDouble(String msg) {
        if (msg.isEmpty()) {
            msg = "Enter a number (double): ";
        }
        System.out.print(msg);

        ///*
        String stringInput;
        while (true) {
            try {
                stringInput = scanner.nextLine();
                if (stringInput.trim().isEmpty()) {
                    // для пропуска пустых введенных строк
                } else {
                    return Double.parseDouble(stringInput.trim());
                }
            } catch (Exception ex) {
                // NumberFormatException
                System.out.print("Double input error, try again: ");
            }
        }
    }

    /**
     * Считывает символ
     *
     * @param msg сообщение для отображения перед вводом
     * @return возвращает введенное значение
     */
    public char readChar(String msg) {
        if (msg.isEmpty()) {
            msg = "Enter char: ";
        }
        System.out.print(msg);

        String stringInput;
        while (true) {
            try {
                stringInput = scanner.nextLine();
                if (stringInput.trim().isEmpty()) {
                    // для пропуска пустых введенных строк
                } else {
                    return stringInput.trim().charAt(0);
                }
            } catch (Exception ex) {
                // NumberFormatException
                System.out.print("Char input error, try again: ");
            }
        }
    }


    public String readString(String msg, boolean allowEmpty, String defaultValue) {
        if (msg.isEmpty()) {
            msg = "Enter line (String): ";
        }
        System.out.print(msg);

        ///*
        String stringInput;
        while (true) {
            try {
                stringInput = scanner.nextLine().trim();
                if (allowEmpty) {
                    if (stringInput.isEmpty()) {
                        return defaultValue;
                    } else {
                        return stringInput;
                    }
                } else {
                    throw new IOException("Input cannot be empty!");
                    // пропуск пустых введенных строк
                }
            } catch (Exception ex) {
                // NumberFormatException
                System.out.print("String input error, try again: ");
            }
        }
    }
}
