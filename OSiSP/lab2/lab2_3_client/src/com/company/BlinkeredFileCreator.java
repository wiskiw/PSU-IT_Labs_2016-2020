package com.company;

import java.io.FileOutputStream;
import java.io.IOException;

public class BlinkeredFileCreator {


    public static final String FILE_PATH = "incomming.txt";


    public void create(byte[] data) {
        try (FileOutputStream fos = new FileOutputStream(FILE_PATH)) {
            fos.write(data);
            //fos.close();
            // There is no more need for this line since you had created the instance of "fos" inside the try.
            // And this will automatically close the OutputStream
        } catch (IOException e) {
            System.err.println(e);
        }
    }


}
