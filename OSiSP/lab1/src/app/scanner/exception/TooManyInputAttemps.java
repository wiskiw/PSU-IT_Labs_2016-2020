package app.scanner.exception;

import java.io.IOException;

public class TooManyInputAttemps extends IOException {

    public TooManyInputAttemps(String message) {
        super(message);
    }

}
