package com.company;

import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.util.Arrays;

public class BlinkeredFileExplorer {


    private File path;
    private byte[] fileContent;
    private int tooked = 0;

    public BlinkeredFileExplorer(String filePath) {
        this.path = new File(filePath);
    }

    public BlinkeredFileExplorer(File path) {
        this.path = path;
    }

    private byte[] getFileContent() throws IOException {
        if (fileContent == null) {
            fileContent = Files.readAllBytes(path.toPath());
            System.out.println("Open file '" + path.getName() + "' file, size " + fileContent.length);
        }
        return fileContent;
    }

    public byte[] nextPiece(int pieceSize) {
        try {
            byte[] fileContent = getFileContent();

            if (tooked >= fileContent.length) {
                tooked = 0;
            }

            int rangeFrom = tooked;
            int rangeTo;
            if (fileContent.length - tooked > pieceSize) {
                rangeTo = rangeFrom + pieceSize;
            } else {
                rangeTo = fileContent.length;
            }
            tooked = rangeTo + 1;

            byte[] returnBytes = Arrays.copyOfRange(fileContent, rangeFrom, rangeTo);
            System.out.println(rangeFrom + "-" + rangeTo + " = returnBytes " + returnBytes.length + " : " + Arrays.toString(returnBytes));

            return returnBytes;


        } catch (IOException e) {
            e.printStackTrace();
            return new byte[0];
        }
    }


}
