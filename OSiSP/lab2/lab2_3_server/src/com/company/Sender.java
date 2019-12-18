package com.company;


import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.UnknownHostException;

class Sender {

    private int port;
    private InetAddress addr;

    Sender(String host, int port) {
        this.port = port;

        try {
            addr = InetAddress.getByName(host);
        } catch (UnknownHostException e) {
            System.err.println(e);
        }
    }

    public Sender(int port, InetAddress addr) {
        this.addr = addr;
        this.port = port;
    }

    public void sendData(byte[] data) {
        try {
            DatagramPacket pack = new DatagramPacket(data, data.length, addr, port);
            DatagramSocket ds = new DatagramSocket();
            ds.send(pack);
            ds.close();
        } catch (IOException e) {
            System.err.println(e);
        }
    }
}