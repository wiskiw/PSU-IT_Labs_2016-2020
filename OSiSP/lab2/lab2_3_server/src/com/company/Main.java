package com.company;

import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.nio.ByteBuffer;

public class Main {

    private static final String FILE_NAME = "./file.txt";
    private static final int PORT_IN = 1050;
    private static final int PORT_OUT = 1060;


    public static void main(String[] args) {
        // write your code here


        BlinkeredFileExplorer blinkeredFileExplorer = new BlinkeredFileExplorer(FILE_NAME);

        try {
            DatagramSocket ds = new DatagramSocket(PORT_IN);
            while (true) {
                DatagramPacket pack = new DatagramPacket(new byte[1024], 1024);
                ds.receive(pack);

                ByteBuffer buf = ByteBuffer.wrap(pack.getData());
                int pieceSize = buf.getInt();

                InetAddress clientAddress = pack.getAddress();
                System.out.println();
                System.out.println("Incomming connection from: " + clientAddress.getHostAddress());

                Thread.sleep(600);
                Sender sender = new Sender(PORT_OUT, clientAddress);
                byte[] dataPiece = blinkeredFileExplorer.nextPiece(pieceSize);
                sender.sendData(dataPiece);
                System.out.println("Sending back " + dataPiece.length + " bytes...");

            }
        } catch (Exception e) {
            System.out.println(e);
        }

    }
}
