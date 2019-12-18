package param;

import result.ParamsDoubleRes;

public class ParamsDoubleSrc extends ParamsSrc<Double> {

    private double a;
    private double b;
    private double c;

    @Override
    public void setA(Double a) {
        this.a = a;
    }

    @Override
    public void setB(Double b) {
        this.b = b;
    }

    @Override
    public void setC(Double c) {
        this.c = c;
    }

    @Override
    public boolean isStoodByOrder() {
        return a > b && b > c || a < b && b < c;
    }

    @Override
    public ParamsDoubleRes doubleIt() {
        return new ParamsDoubleRes(
                this.a * 2,
                this.b * 2,
                this.c * 2
        );
    }

    @Override
    public ParamsDoubleRes reverseIt() {
        return new ParamsDoubleRes(
                this.a * -1,
                this.b * -1,
                this.c * -1
        );
    }

    @Override
    public String toString() {
        return "ParamsDouble.Src {" +
                "a=" + a +
                ", b=" + b +
                ", c=" + c +
                '}';
    }
}

