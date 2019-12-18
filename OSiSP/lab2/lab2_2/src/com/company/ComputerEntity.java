package com.company;

import java.io.Serializable;

public class ComputerEntity implements Serializable {

    private int ramSize = 0;
    private int storageSize = 0;
    private String CPU = "";
    private String GPU = "";

    public ComputerEntity() {
    }

    public ComputerEntity(int ramSize, int storageSize, String CPU, String GPU) {
        this.ramSize = ramSize;
        this.storageSize = storageSize;
        this.CPU = CPU;
        this.GPU = GPU;
    }

    public int getRamSize() {
        return ramSize;
    }

    public void setRamSize(int ramSize) {
        this.ramSize = ramSize;
    }

    public int getStorageSize() {
        return storageSize;
    }

    public void setStorageSize(int storageSize) {
        this.storageSize = storageSize;
    }

    public String getCPU() {
        return CPU;
    }

    public void setCPU(String CPU) {
        this.CPU = CPU;
    }

    public String getGPU() {
        return GPU;
    }

    public void setGPU(String GPU) {
        this.GPU = GPU;
    }

    @Override
    public String toString() {
        return "ComputerEntity {" +
                "ramSize=" + ramSize +
                ", storageSize=" + storageSize +
                ", CPU='" + CPU + '\'' +
                ", GPU='" + GPU + '\'' +
                '}';
    }
}
