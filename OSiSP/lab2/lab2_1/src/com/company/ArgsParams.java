package com.company;

public class ArgsParams {

    private String dirPath = ".";
    private String mask = ".*";


    public ArgsParams(String dirPath, String mask) {
        this.dirPath = dirPath;
        this.mask = mask;
    }

    public ArgsParams() {
    }

    public String getDirPath() {
        return dirPath;
    }

    public String getMask() {
        return mask;
    }

    public void setDirPath(String dirPath) {
        this.dirPath = dirPath;
    }

    public void setMask(String mask) {
        this.mask = mask;
    }

    @Override
    public String toString() {
        return "ArgsParams {" +
                "dirPath='" + dirPath + '\'' +
                ", mask='" + mask + '\'' +
                '}';
    }
}
