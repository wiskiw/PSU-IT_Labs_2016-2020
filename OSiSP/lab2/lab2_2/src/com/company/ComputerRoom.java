package com.company;

import java.io.*;
import java.util.ArrayList;

public class ComputerRoom {

    private static final String filePath = "database.db";
    private static File file = null;


    public static File getDefaultFile() {
        if (file == null) {
            file = new File(filePath);
        }
        return file;
    }

    public static void save(File path, ArrayList<ComputerEntity> computerEntities) {
        try {
            FileOutputStream fos = new FileOutputStream(path);
            ObjectOutputStream oos = new ObjectOutputStream(fos);
            oos.writeObject(computerEntities);
            oos.close();
            fos.close();
        } catch (IOException ioe) {
            ioe.printStackTrace();
        }
    }

    public static ArrayList<ComputerEntity> read(File path) {
        ArrayList<ComputerEntity> arraylist = new ArrayList<>();
        try {
            FileInputStream fis = new FileInputStream(path);
            ObjectInputStream ois = new ObjectInputStream(fis);
            arraylist = (ArrayList) ois.readObject();
            ois.close();
            fis.close();
        } catch (IOException ioe) {
            ioe.printStackTrace();
        } catch (ClassNotFoundException c) {
            System.err.println("Class not found");
            c.printStackTrace();
        }
        return arraylist;
    }


}
