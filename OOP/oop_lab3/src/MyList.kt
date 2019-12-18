import java.util.*
import kotlin.collections.ArrayList

class MyList {

    private var arrayList: ArrayList<Char> = arrayListOf()

    /*
        Operator overloading
        http://kotlinlang.ru/docs/reference/operator-overloading.html

     */

    /*
       11. АДТ − однонаправленный список с элементами типа char.
       Дополнительно перегрузить следующие операции:
       [] − доступ к элементу в заданной позиции, например:
       int i; char c;
       list L;
       c=L[i];
       + − объединить два списка;
       != − проверка на неравенство.
    */

    constructor()

    constructor(mList: MyList) {
        this.arrayList = ArrayList(mList.arrayList)
    }


    fun printAll() {
        println(this.toString())
    }

    override fun toString(): String {
        var rString = "CUSTOM LIST ::: SIZE ${this.size()}"
        this.arrayList.forEachIndexed { index, c ->
            rString += "\n[$index]: '$c'"
        }
        return rString
    }

    fun input() {
        val scanner = Scanner(System.`in`)
        var scannedString: String
        println("INPUT")
        while (true) {
            print("char[${this.size()}]: ")
            scannedString = scanner.nextLine()
            if (scannedString.isNotEmpty()) {
                this.arrayList.add(scannedString[0])
            } else {
                break
            }
        }
    }

    fun add(el: Char) {
        this.arrayList.add(el)
    }

    fun remove(el: Char) {
        this.arrayList.remove(el)
    }

    fun size() = this.arrayList.size

    operator fun get(i: Int): Char = this.arrayList[i]

    operator fun plus(list: MyList): MyList {
        val mList = MyList(this)
        mList.arrayList.addAll(list.arrayList)
        return mList
    }


    override fun equals(other: Any?): Boolean {
        if (this === other) return true
        if (javaClass != other?.javaClass) return false

        other as MyList

        if (arrayList != other.arrayList) return false

        return true
    }

    override fun hashCode(): Int {
        return arrayList.hashCode()
    }



}