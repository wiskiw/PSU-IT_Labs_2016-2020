package app.scanner.params;

import app.scanner.SimpleAppScanner;
import param.ParamsIntSrc;
import param.ParamsSrc;

import java.io.IOException;

public class IntParamsScanner extends ParamsScanner<Integer> {

    public IntParamsScanner(SimpleAppScanner appScanner) {
        super(appScanner);
    }

    @Override
    protected ParamsSrc<Integer> newParamsInstance() {
        return new ParamsIntSrc();
    }

    @Override
    protected Integer scannVar(String varTitle, SimpleAppScanner appScanner) throws IOException {
        return appScanner.readInt("Enter " + varTitle + " value (Char): ");
    }
}
