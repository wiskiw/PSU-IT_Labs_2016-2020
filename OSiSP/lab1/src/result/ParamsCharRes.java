package result;

public class ParamsCharRes extends ParamsRes<Character> {

    private char a;
    private char b;
    private char c;

    public ParamsCharRes(char a, char b, char c) {
        this.a = a;
        this.b = b;
        this.c = c;
    }

    @Override
    public String toString() {
        return "ParamsCharacter.Res {" +
                "a=" + a +
                ", b=" + b +
                ", c=" + c +
                '}';
    }
}