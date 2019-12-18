package result;

/**
 * Класс для хранения результатов вычисления
 *
 * @author Andrew Yablonski
 */

public class ThreeParamsResOld {

    private boolean isStoodByOrder = false;

    private Double a;
    private Double b;
    private Double c;


    public Double getA() {
        return a;
    }

    public Double getB() {
        return b;
    }

    public Double getC() {
        return c;
    }

    public boolean isStoodByOrder() {
        return isStoodByOrder;
    }

    public void setStoodByOrder(boolean stoodByOrder) {
        isStoodByOrder = stoodByOrder;
    }

    /**
     * Метод проверки атрибутов
     *
     * @return true если верно (A>B>C или A<B<C) и isStoodByOrder = true
     */
    private boolean isAttrsCorrect() {
        boolean localParamsCheck = isParamsStoodByOrder();
        return localParamsCheck == isStoodByOrder;
    }

    /**
     * Проверяет отсортированы ли A, B и C
     *
     * @return true если верно A>B>C или A<B<C
     */
    private boolean isParamsStoodByOrder() {
        return isLowerToUpper() || isUpperToLower();
    }

    /**
     * Проверяет стоят ли числа  в порядке возрастания
     *
     * @return true - если A<B<C
     */
    private boolean isLowerToUpper() {
        return getA() < getB() && getB() < getC();
    }

    /**
     * Проверяет стоят ли числа в порядке убывания
     *
     * @return true - если A>B>C
     */
    private boolean isUpperToLower() {
        return getA() > getB() && getB() > getC();
    }

    @Override
    public String toString() {
        return "ParamsRes (isStoodByOrder: " + isStoodByOrder + ") {" +
                "a=" + a +
                ", b=" + b +
                ", c=" + c +
                '}';
    }
}
