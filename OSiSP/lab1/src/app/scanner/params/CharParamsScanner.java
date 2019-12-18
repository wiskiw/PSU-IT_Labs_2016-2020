package app.scanner.params;

import app.scanner.SimpleAppScanner;
import param.ParamsCharSrc;
import param.ParamsIntSrc;
import param.ParamsSrc;

import java.io.IOException;

public class CharParamsScanner extends ParamsScanner<Character> {

    public CharParamsScanner(SimpleAppScanner appScanner) {
        super(appScanner);
    }

    @Override
    protected ParamsSrc<Character> newParamsInstance() {
        return new ParamsCharSrc();
    }

    @Override
    protected Character scannVar(String varTitle, SimpleAppScanner appScanner) throws IOException {
        return appScanner.readChar("Enter " + varTitle + " value (Char): ");
    }
}
