package app.scanner.params;

import app.scanner.SimpleAppScanner;
import param.ParamsSrc;

import java.io.IOException;

public abstract class ParamsScanner<T> {

    private SimpleAppScanner appScanner;

    public ParamsScanner(SimpleAppScanner appScanner) {
        this.appScanner = appScanner;
    }

    protected abstract ParamsSrc<T> newParamsInstance();

    protected abstract T scannVar(String varTitle, SimpleAppScanner appScanner) throws IOException;

    public ParamsSrc<T> scannParams() {
        System.out.println("Input ...");

        try {
            ParamsSrc<T> params = newParamsInstance();
            params.setA(scannVar("A", appScanner));
            params.setB(scannVar("B", appScanner));
            params.setC(scannVar("C", appScanner));
            return params;
        } catch (IOException ioe) {
            System.out.println("Input error! " + ioe.getLocalizedMessage());
            return null;
        }

    }


}
