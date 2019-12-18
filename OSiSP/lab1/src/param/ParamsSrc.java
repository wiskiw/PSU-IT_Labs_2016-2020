package param;

import result.ParamsRes;

/**
 * Класс для хранения входных значений переменных A, B, C
 *
 * @author Andrew Yablonski
 */
public abstract class ParamsSrc<T> {

    public abstract void setA(T a);

    public abstract void setB(T b);

    public abstract void setC(T c);

    public abstract boolean isStoodByOrder();

    public abstract ParamsRes<T> doubleIt();

    public abstract ParamsRes<T> reverseIt();

    public abstract String toString();


}
