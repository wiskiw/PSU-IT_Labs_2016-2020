package by.pdu.dormitory.util;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;

public class ApplicationContextImpl implements ApplicationContext {

    private Map<Class, ArrayList<String>> beansClass;
    private Map<String, ArrayList<Object>> beans;

    public ApplicationContextImpl() {
        beansClass = new HashMap<>();
        beans = new HashMap<>();
    }

    public void inject(final Class clazz, final String name, final Object obj) {
        if (!beansClass.containsKey(clazz)) {
            ArrayList<String> arr = new ArrayList<>();
            arr.add(name);
            beansClass.put(clazz, arr);
        } else {
            ArrayList<String> arr = beansClass.get(clazz);
            arr.add(name);
        }

        if (!beans.containsKey(name)) {
            ArrayList<Object> arr = new ArrayList<>();
            arr.add(obj);
            beans.put(name, arr);

        } else {
            ArrayList<Object> arr = beans.get(name);
            arr.add(obj);
        }

        if (clazz.getSuperclass() != null && !Object.class.equals(clazz.getSuperclass()))
            inject(clazz.getSuperclass(), name, obj);
    }

    @Override
    public <T> T getBean(final String name, final Class<T> clazz) {

        if (!beansClass.containsKey(clazz)) return null;
        for (Object bean : beans.get(name)) {
            if (bean == null) continue;
            try {
                return clazz.cast(bean);
            } catch (ClassCastException ex) {
            }
        }
        return null;

    }

    public <T> ArrayList<T> getBeans(final Class<T> clazz) {
        if (!beansClass.containsKey(clazz)) return null;
        ArrayList<T> arr = new ArrayList<>();
        for (String name : beansClass.get(clazz))
            arr.add(getBean(name, clazz));
        return arr;
    }
}
