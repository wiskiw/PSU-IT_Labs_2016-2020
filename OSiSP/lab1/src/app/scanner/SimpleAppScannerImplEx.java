package app.scanner;

import jdk.nashorn.internal.ir.annotations.Ignore;

import java.io.IOException;
import java.util.Scanner;

public class SimpleAppScannerImplEx implements SimpleAppScanner {

    private Scanner scanner;

    /**
     * Кинструсктор, инициализация сканера
     */
    public SimpleAppScannerImplEx() {
        this.scanner = new Scanner(System.in);
    }


    @Override
    public double readDouble(String msg) {
        if (msg.isEmpty()) {
            msg = "Enter a number (double): ";
        }
        System.out.print(msg);
        return scanner.nextDouble();
    }

    @Override
    public int readInt(String msg) {
        if (msg.isEmpty()) {
            msg = "Enter a number (int): ";
        }
        System.out.print(msg);
        return scanner.nextInt();
    }

    /**
     * Считываение введенного числа(Int)
     *
     * @param msg         - сообщение для вывода польователю, можно соатвить пустым
     * @param maxAttempts - не имеет значения, т к SimpleAppScannerImplEx выбрасывает исключение при ошибке ввода
     * @return введенное число Int
     */
    @Override
    public int readInt(String msg, @Ignore int maxAttempts) {
        return readInt(msg);
    }

    /**
     * Считываение введенного числа(Double)
     *
     * @param msg         - сообщение для вывода польователю, можно соатвить пустым
     * @param maxAttempts - не имеет значения, т к SimpleAppScannerImplEx выбрасывает исключение при ошибке ввода
     * @return введенное число Int
     */
    @Override
    public double readDouble(String msg, @Ignore int maxAttempts) {
        return readDouble(msg);
    }

    /**
     * Считываение введенного символа(Char)
     *
     * @param msg         - сообщение для вывода польователю, можно соатвить пустым
     * @param maxAttempts - не имеет значения, т к SimpleAppScannerImplEx выбрасывает исключение при ошибке ввода
     * @return введенный символ Char
     */
    @Override
    public char readChar(String msg, @Ignore int maxAttempts) {
        return readChar(msg);
    }

    @Override
    public char readChar(String msg) {
        if (msg.isEmpty()) {
            msg = "Enter a char: ";
        }
        System.out.print(msg);
        return scanner.nextLine().charAt(0);
    }
}
