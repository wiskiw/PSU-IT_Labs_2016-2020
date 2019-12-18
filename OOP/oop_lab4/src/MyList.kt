import java.util.*

class MyList<T : Any> {

    private var list: LinkedList<T> = LinkedList()

    /*
        Operator overloading
        http://kotlinlang.ru/docs/reference/operator-overloading.html

     */

    /*
    10. Класс − множество set. Дополнительно перегрузить следующие операции:
        > − проверка на принадлежность (типа операции in множественного
        типа в языке Pascal);
        * − пересечение множеств;
        < − проверка на подмножество.

     11. Класс − однонаправленный список list. Дополнительно перегрузить следующие операции:
        + − добавить элемент в начало (list+item);
        -- − удалить элемент из начала (--list);
        == − проверка на равенство.

        Реализовать структуру данных - очередь Queue. Дополнительно реализовать
        функции:
        проверка двух структур на неравенство,
        объединение двух структур данных;
    */

    constructor()

    constructor(mList: MyList<T>) {
        this.list = LinkedList(mList.list)
    }

    operator fun compareTo(el: T): Int {
        return if (list.contains(el)) 1 else 0
    }

    fun enqueue(el: T) {
        list.offer(el)
    }

    fun dequeue() = list.poll()

    fun head() = list.peek()

    operator fun compareTo(mList: MyList<T>): Int {
        if (mList.size() == 0 || this.size() == 0) return 0
        return if (list.containsAll(mList.list)) -1 else 0
    }

    fun printAll() {
        println(this.toString())
    }

    // *
    operator fun times(myList: MyList<T>): MyList<T> {
        val resultList = MyList<T>()
        val bigger: MyList<T>
        val smaller: MyList<T>

        if (myList.size() > this.size()) {
            bigger = myList
            smaller = this
        } else {
            bigger = this
            smaller = myList
        }

        bigger.list.forEach {
            if (smaller.list.contains(it)) {
                resultList.add(it)
            }
        }
        return resultList
    }


    fun add(el: T) {
        this.list.add(el)
    }

    operator fun plus(list: MyList<T>) {
        this.list.addAll(list.list)
    }

    fun remove(el: T) {
        this.list.remove(el)
    }

    fun search(el: T): Int {
        return list.indexOf(el)
    }

    fun size() = this.list.size

    operator fun get(i: Int): T = this.list[i]

    operator fun plus(el: T) {
        this.list.add(0, el)
    }

    operator fun dec(): MyList<T> {
        val nList = MyList(this)
        nList.list.removeAt(0)
        return nList
    }


    override fun equals(other: Any?): Boolean {
        if (this === other) return true
        if (javaClass != other?.javaClass) return false

        other as MyList<*>

        if (list != other.list) return false

        return true
    }

    override fun hashCode(): Int {
        return list.hashCode()
    }

    override fun toString(): String {
        var rString = "CUSTOM LIST ::: SIZE ${this.size()}"
        this.list.forEachIndexed { index, el ->
            rString += "\n[$index]: '$el'"
        }
        return rString
    }

}