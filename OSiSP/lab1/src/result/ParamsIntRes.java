package result;

public class ParamsIntRes extends ParamsRes<Integer> {

    private int a;
    private int b;
    private int c;

    public ParamsIntRes(int a, int b, int c) {
        this.a = a;
        this.b = b;
        this.c = c;
    }

    @Override
    public String toString() {
        return "ParamsInt.Res {" +
                "a=" + a +
                ", b=" + b +
                ", c=" + c +
                '}';
    }
}