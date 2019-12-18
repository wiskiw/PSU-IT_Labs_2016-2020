package app.scanner;

import java.io.IOException;

public interface SimpleAppScanner {

    int readInt(String msg, int maxAttempts) throws IOException;

    int readInt(String msg) throws IOException;

    double readDouble(String msg, int maxAttempts) throws IOException;

    double readDouble(String msg) throws IOException;

    char readChar(String msg, int maxAttempts) throws IOException;

    char readChar(String msg) throws IOException;

}
