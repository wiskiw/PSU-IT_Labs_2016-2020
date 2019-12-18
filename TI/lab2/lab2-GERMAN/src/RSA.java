import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.math.BigInteger;
import java.security.SecureRandom;
import java.util.Scanner;

public class RSA {
    private static BigInteger n, d, e;

    private int bitlen = 1024;

    /**
     * Создание экземпляра, который может шифровать и расшифровывать.
     */
    public RSA(int bits) {
        bitlen = bits;
        SecureRandom r = new SecureRandom();
        BigInteger p = new BigInteger(bitlen / 2, 100, r);
        BigInteger q = new BigInteger(bitlen / 2, 100, r);
        n = p.multiply(q);
        BigInteger m = (p.subtract(BigInteger.ONE)).multiply(q.subtract(BigInteger.ONE));
        e = new BigInteger("3");
        while (m.gcd(e).intValue() > 1) {
            e = e.add(new BigInteger("2"));
        }
        d = e.modInverse(m);
    }

    /**
     * Шифрование сообщения открытого текста.
     */
    public synchronized BigInteger encrypt(BigInteger message) {
        return message.modPow(d, n);
    }

    /**
     * Декодирование сообщение зашифрованного текста.
     */
    public synchronized BigInteger decrypt(BigInteger message, BigInteger e, BigInteger n) {
        return message.modPow(e, n);
    }

    /**
     * Запись данных в файлы
     */
    public static synchronized void WriteFile(BigInteger text) throws IOException {
        FileWriter writer = new FileWriter("PublicKey.txt");
        writer.write(String.valueOf(e));
        writer.append('\n');
        writer.write(String.valueOf(n));
        writer.close();

        writer = new FileWriter("Signature.txt");
        writer.write(String.valueOf(text));
        writer.close();
    }

    /**
     * Основная программа
     */
    public static void main(String[] args) throws IOException {

        /*File file = new File("Genuine Post.txt");
        Scanner scanner = new Scanner(file);
        String text = scanner.nextLine();
        System.out.println("Исходный текст: " + text);
        String sha1 = SHA1.encodeHex(text);
        //System.out.println("Хэш-функциия: " + sha1);

        RSA rsa = new RSA(1024);
        BigInteger plaintext = new BigInteger(sha1.getBytes());
        BigInteger ciphertext = rsa.encrypt(plaintext);
        //System.out.println("Шифртекст: " + ciphertext);
        WriteFile(ciphertext);
        //System.out.println("Закрытый ключ: " + d);*/



        File file2 = new File("PublicKey.txt");
        Scanner scanner2 = new Scanner(file2);
        String e = scanner2.nextLine();
        String n = scanner2.nextLine();
        BigInteger E = new BigInteger(n);
        BigInteger N = new BigInteger(e);

        RSA rsa = new RSA(1024);
        File file3 = new File("Signature.txt");
        Scanner scanner3 = new Scanner(file3);
        String sign = scanner3.nextLine();
        BigInteger ciphertext = new BigInteger(sign);
        //ciphertext = new BigInteger(sign);

        BigInteger plaintext = rsa.decrypt(ciphertext, N, E);
        //plaintext = rsa.decrypt(ciphertext, N, E);
        String text2 = new String(plaintext.toByteArray());
        System.out.println("Расшифрованная подпись: " + text2);

        File file4 = new File("Message.txt");
        Scanner scanner4 = new Scanner(file4);
        String text4 = scanner4.nextLine();
        System.out.println("Переданный текст: " + text4);
        String sha14 = SHA1.encodeHex(text4);
        System.out.println("Хэш-функция переданного текста: " + sha14);

        if (sha14.equals(text2)) {
            System.out.println("Документы аутентичны.");
    } else {
            System.out.println("Документы не аутентичны.");
        }
    }
}