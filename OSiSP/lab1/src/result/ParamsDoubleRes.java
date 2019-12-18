package result;

public class ParamsDoubleRes extends ParamsRes<Double> {

    private double a;
    private double b;
    private double c;

    public ParamsDoubleRes(double a, double b, double c) {
        this.a = a;
        this.b = b;
        this.c = c;
    }

    @Override
    public String toString() {
        return "ParamsDouble.Res {" +
                "a=" + a +
                ", b=" + b +
                ", c=" + c +
                '}';
    }
}