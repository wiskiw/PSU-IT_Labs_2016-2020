package com.company;

public class ComputerEntityIO {

    /*
        https://stackoverflow.com/questions/1552156/is-it-possible-to-print-text-that-can-be-edited-by-the-user-for-console-program
     */

    private SimpleAppScanner simpleAppScanner;

    public ComputerEntityIO(SimpleAppScanner simpleAppScanner) {
        this.simpleAppScanner = simpleAppScanner;
    }


    public ComputerEntity readNewOne() {
        ComputerEntity computerEntity = new ComputerEntity();

        System.out.println("Enter new computer: ");
        computerEntity.setRamSize(simpleAppScanner.readInt("RAM size: ", false, 0));
        computerEntity.setStorageSize(simpleAppScanner.readInt("Storage size: ", false, 0));
        computerEntity.setCPU(simpleAppScanner.readString("CPU: ", false, ""));
        computerEntity.setGPU(simpleAppScanner.readString("GPU: ", false, ""));

        return computerEntity;
    }

    public void editOne(ComputerEntity computerEntity) {
        System.out.println("Edit the computer(press enter to skip): ");
        computerEntity.setRamSize(
                simpleAppScanner.readInt("Edit RAM size ('" + computerEntity.getRamSize() + "'): ",
                        true, computerEntity.getRamSize())
        );
        computerEntity.setStorageSize(
                simpleAppScanner.readInt("Edit Storage size ('" + computerEntity.getStorageSize() + "'): ",
                        true, computerEntity.getStorageSize())
        );
        computerEntity.setCPU(
                simpleAppScanner.readString("Edit CPU ('" + computerEntity.getCPU() + "'): ",
                        true, computerEntity.getCPU())
        );
        computerEntity.setGPU(
                simpleAppScanner.readString("Edit GPU ('" + computerEntity.getGPU() + "'): ",
                        true, computerEntity.getGPU())
        );
    }
}
