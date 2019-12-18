package com.company;

import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.nio.ByteBuffer;
import java.util.Arrays;

public class Main {

    /*
    22. Реализовать программу по созданию множества мелких файлов из одного большого, размер маленьких
    файлов произвольныйю Сервер получает запрос от клиента и возращает ему кусочек файла. Протокол взаимодействия UDP;
     */

    private static final int PIECE_SIZE = 12;
    public static final String IP = "localhost";
    private static final int PORT_IN = 1060;
    private static final int PORT_OUT = 1050;


    public static void main(String[] args) {

        BlinkeredFileCreator blinkeredFileCreator = new BlinkeredFileCreator();

        byte[] requestData = ByteBuffer.allocate(4).putInt(PIECE_SIZE).array();
        Sender sndr = new Sender(IP, PORT_OUT);
        sndr.sendData(requestData);

        try {
            DatagramSocket ds = new DatagramSocket(PORT_IN);

            DatagramPacket pack = new DatagramPacket(new byte[PIECE_SIZE], PIECE_SIZE);
            ds.receive(pack);

            System.out.println("Response from: " + pack.getAddress().getHostAddress());
            System.out.println("     data: " + new String(pack.getData()).replace("\n", ""));
            System.out.println("    bytes: " + Arrays.toString(pack.getData()));
            blinkeredFileCreator.create(pack.getData());

        } catch (Exception e) {
            System.out.println(e);
        }
    }
}
