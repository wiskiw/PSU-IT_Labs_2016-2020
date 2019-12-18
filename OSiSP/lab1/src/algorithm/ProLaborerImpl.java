package algorithm;

import param.ParamsSrc;
import result.ParamsRes;

public class ProLaborerImpl implements Laborer {


    /**
     * Основное задание вариант. Если их значения упорядочены по возрастанию или убыванию, то удвоить их;
     * в противном случае заменить значение каждой переменной на противоположное. Метод изменяте значения объекта params
     *
     * @return - ParamsRes - результат работы
     */
    @Override
    public ParamsRes processThreeParams(ParamsSrc paramsSrc, boolean printRes) {
        ParamsRes paramsRes;
        if (paramsSrc.isStoodByOrder()) {
            paramsRes = paramsSrc.doubleIt();
        } else {
            paramsRes = paramsSrc.reverseIt();
        }
        if (printRes) show(paramsRes);
        return paramsRes;
    }

    private void show(ParamsRes paramsRes) {
        System.out.println(paramsRes.toString());
    }
}
