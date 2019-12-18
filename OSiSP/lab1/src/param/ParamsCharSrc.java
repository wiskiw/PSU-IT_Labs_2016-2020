package param;

import result.ParamsCharRes;

public class ParamsCharSrc extends ParamsSrc<Character> {

    private char a;
    private char b;
    private char c;

    @Override
    public void setA(Character a) {
        this.a = a;
    }

    @Override
    public void setB(Character b) {
        this.b = b;
    }

    @Override
    public void setC(Character c) {
        this.c = c;
    }

    @Override
    public boolean isStoodByOrder() {
        return a > b && b > c || a < b && b < c;
    }

    @Override
    public ParamsCharRes doubleIt() {
        return new ParamsCharRes(
                (char) (a * 2),
                (char) (b * 2),
                (char) (c * 2)
        );
    }

    @Override
    public ParamsCharRes reverseIt() {
        return new ParamsCharRes(
                (char) (a * -1),
                (char) (b * -1),
                (char) (c * -1)
        );
    }

    @Override
    public String toString() {
        return "ParamsCharacter.Src {" +
                "a=" + a +
                ", b=" + b +
                ", c=" + c +
                '}';
    }
}

