package app.scanner.params;

import app.scanner.SimpleAppScanner;
import param.ParamsDoubleSrc;
import param.ParamsIntSrc;
import param.ParamsSrc;

import java.io.IOException;

public class DoubleParamsScanner extends ParamsScanner<Double> {

    public DoubleParamsScanner(SimpleAppScanner appScanner) {
        super(appScanner);
    }

    @Override
    protected ParamsSrc<Double> newParamsInstance() {
        return new ParamsDoubleSrc();
    }

    @Override
    protected Double scannVar(String varTitle, SimpleAppScanner appScanner) throws IOException {
        return appScanner.readDouble("Enter " + varTitle + " value (Double): ");
    }
}
