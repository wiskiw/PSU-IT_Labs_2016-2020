package com.company;


import com.company.file.CustomFileFilter;

import java.io.File;
import java.io.FileFilter;
import java.io.FilenameFilter;

public class Main {

    /*
        1) Написать программу для поиска файлов по маске используя FilenameFilter.
        Маска и директория передаются в качестве парметра, рекурсивно искать во всех подкаталогах.*/


    private static ArgsParams parseArgs(String[] args) {
        ArgsParams argsParams = new ArgsParams();

        if (args.length >= 1) {
            argsParams.setDirPath(args[0]);
        }

        if (args.length >= 2) {
            argsParams.setMask(args[1]);
        }

        System.out.println("argsParams: " + argsParams);
        return argsParams;
    }

    public static void main(String[] args) {
        ArgsParams argsParams = parseArgs(args);
        CustomFileFilter customFileFilter = new CustomFileFilter(argsParams.getMask());

        File path = new File(argsParams.getDirPath());
        showFilesRecursive(path, customFileFilter);
    }

    private static int showFilesRecursive(File path, FilenameFilter fileFilter) {
        return showFilesRecursive(path, fileFilter, 0, 0);
    }

    private static int showFilesRecursive(File path, FilenameFilter fileFilter, int count, int subLevel) {
        File[] fileList = path.listFiles(fileFilter);
        if (fileList == null) return count;

        File f;
        for (int i = 0; i < fileList.length; i++) {
            f = fileList[i];

            if (f.isDirectory()) {
                subLevel++;
                showFilesRecursive(f, fileFilter, count, subLevel);
            } else {
                StringBuilder subLevelPrefix = new StringBuilder();
                for (int k = 0; k < subLevel; k++) {
                    subLevelPrefix.append("   ");
                }

                if (i == 0) System.out.println(" === '" + path.getName() + "'");
                System.out.println(subLevelPrefix + "[" + i + "]: " + f.getName());
                count++;
            }

        }
        return count;
    }


}
