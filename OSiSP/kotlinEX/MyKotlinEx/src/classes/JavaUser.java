package classes;

import java.util.Objects;

public class JavaUser {

    private int id;
    private String name;

    public int getId() {
        return id;
    }

    public void setId(int id) {
        this.id = id;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    @Override
    public String toString() {
        return "JavaUser{" +
                "id=" + id +
                ", name='" + name + '\'' +
                '}';
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        JavaUser javaUser = (JavaUser) o;
        return id == javaUser.id &&
                Objects.equals(name, javaUser.name);
    }

    @Override
    public int hashCode() {
        return Objects.hash(id, name);
    }

}



