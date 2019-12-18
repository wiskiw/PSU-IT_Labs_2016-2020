package app.scanner;

import app.scanner.exception.TooManyInputAttemps;

import java.io.IOException;
import java.util.Scanner;

/**
 * Класс для ввода данных с клавиатуры
 *
 * @author Andrew Yablonski
 */

public class SimpleAppScannerImpl implements SimpleAppScanner {

    private Scanner scanner;

    /**
     * Кинструсктор, инициализация сканера
     */
    public SimpleAppScannerImpl() {
        this.scanner = new Scanner(System.in);
    }

    /**
     * Считывает целочисленое значение
     *
     * @param msg сообщение для отображения перед вводом
     * @return возвращает введенное значение
     */
    @Override
    public int readInt(String msg) throws TooManyInputAttemps {
        return readInt(msg, -1);
    }


    /**
     * Считывает дробное значение
     *
     * @param msg         сообщение для отображения перед вводом
     * @param maxAttempts максимально количество попыток ввода, после будет выброшена TooManyInputAttemps
     * @return возвращает введенное значение
     * @throws TooManyInputAttemps бросается при привышении попыток ввода
     */
    @Override
    public int readInt(String msg, int maxAttempts) throws TooManyInputAttemps {
        if (msg.isEmpty()) {
            msg = "Enter a number (int): ";
        }
        System.out.print(msg);
        String stringInput;
        for (int i = 0; i < maxAttempts || maxAttempts < 0; i++) {
            try {
                stringInput = scanner.nextLine();
                if (stringInput.trim().isEmpty()) {
                    // для пропуска пустых введенных строк
                    i--;
                } else {
                    return Integer.parseInt(stringInput.trim());
                }
            } catch (Exception ex) {
                if (i < maxAttempts - 1 || maxAttempts < 0) {
                    // NumberFormatException
                    System.out.print("Int input error, try again: ");
                }
            }
        }
        throw new TooManyInputAttemps("Int input error, number of attempts(" + maxAttempts + ") exceeded!");
    }


    /**
     * Считывает дробное значение
     *
     * @param msg сообщение для отображения перед вводом
     * @return возвращает введенное значение
     */
    @Override
    public double readDouble(String msg) throws TooManyInputAttemps {
        return readDouble(msg, -1);
    }

    /**
     * Считывает дробное значение
     *
     * @param msg         сообщение для отображения перед вводом
     * @param maxAttempts максимально количество попыток ввода, после будет выброшена TooManyInputAttemps
     * @return возвращает введенное значение
     * @throws TooManyInputAttemps бросается при привышении попыток ввода
     */
    @Override
    public double readDouble(String msg, int maxAttempts) throws TooManyInputAttemps {
        if (msg.isEmpty()) {
            msg = "Enter a number (double): ";
        }
        System.out.print(msg);

        ///*
        String stringInput;
        for (int i = 0; i < maxAttempts || maxAttempts < 0; i++) {
            try {
                stringInput = scanner.nextLine();
                if (stringInput.trim().isEmpty()) {
                    // для пропуска пустых введенных строк
                    i--;
                } else {
                    return Double.parseDouble(stringInput.trim());
                }
            } catch (Exception ex) {
                if (i < maxAttempts - 1 || maxAttempts < 0) {
                    // NumberFormatException
                    System.out.print("Double input error, try again: ");
                }
            }
        }
        throw new TooManyInputAttemps("Double input error, number of attempts(" + maxAttempts + ") exceeded!");
    }

    /**
     * Считывает символ
     *
     * @param msg         сообщение для отображения перед вводом
     * @param maxAttempts максимально количество попыток ввода, после будет выброшена TooManyInputAttemps
     * @return возвращает введенное значение
     * @throws TooManyInputAttemps бросается при привышении попыток ввода
     */
    @Override
    public char readChar(String msg, int maxAttempts) throws IOException {
        if (msg.isEmpty()) {
            msg = "Enter a number (char): ";
        }
        System.out.print(msg);

        ///*
        String stringInput;
        for (int i = 0; i < maxAttempts || maxAttempts < 0; i++) {
            try {
                stringInput = scanner.nextLine();
                if (stringInput.trim().isEmpty()) {
                    // для пропуска пустых введенных строк
                    i--;
                } else {
                    return stringInput.trim().charAt(0);
                }
            } catch (Exception ex) {
                if (i < maxAttempts - 1 || maxAttempts < 0) {
                    // NumberFormatException
                    System.out.print("Char input error, try again: ");
                }
            }
        }
        throw new TooManyInputAttemps("Char input error, number of attempts(" + maxAttempts + ") exceeded!");
    }


    /**
     * Считывает символ
     *
     * @param msg сообщение для отображения перед вводом
     * @return возвращает введенное значение
     */
    @Override
    public char readChar(String msg) throws IOException {
        return readChar(msg, -1);
    }
}
