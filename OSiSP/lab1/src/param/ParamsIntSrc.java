package param;

import result.ParamsIntRes;

public class ParamsIntSrc extends ParamsSrc<Integer> {

    private int a;
    private int b;
    private int c;

    @Override
    public void setA(Integer a) {
        this.a = a;
    }

    @Override
    public void setB(Integer b) {
        this.b = b;
    }

    @Override
    public void setC(Integer c) {
        this.c = c;
    }

    @Override
    public boolean isStoodByOrder() {
        return a > b && b > c || a < b && b < c;
    }

    @Override
    public ParamsIntRes doubleIt() {
        return new ParamsIntRes(
                this.a * 2,
                this.b * 2,
                this.c * 2
        );
    }

    @Override
    public ParamsIntRes reverseIt() {
        return new ParamsIntRes(
                this.a * -1,
                this.b * -1,
                this.c * -1
        );
    }

    @Override
    public String toString() {
        return "ParamsInt.Src {" +
                "a=" + a +
                ", b=" + b +
                ", c=" + c +
                '}';
    }
}

