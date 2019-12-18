package com.company.file;

import java.io.File;
import java.io.FilenameFilter;

public class CustomFileFilter implements FilenameFilter {

    private String regexpMask;

    public CustomFileFilter(String regexpMask) {
        this.regexpMask = regexpMask;
    }

    // accept( ) для определения, какое имя файла должно включаться в список.
    @Override
    public boolean accept(File dir, String name) {
        // Получение информации о пути:
        String fileName = new File(name).getName();
        return
                new File(dir.getPath() + "/" + name).isDirectory() || fileName.matches(regexpMask);
    }
}