import java.util.*


fun averageItemLength(lInter: Iterator<String>): Double {
    var count = 0
    var len = 0.0

    while (lInter.hasNext()) {
        count++
        len += lInter.next().length
    }

    return if (count == 0) {
        println("List is empty")
        0.0
    } else {
        val ail = len / count
        println("Average item length: $ail")
        ail
    }
}


fun action(list: ArrayList<String>) {
    val ail = averageItemLength(list.iterator())
    var lSize = list.size
    var k = 0

    while (k < lSize) {
        val item = list[k]
        if (item.length < ail) {
            list.add(k, item)
            lSize++
            k += 2
        } else {
            k++
        }
    }
}

fun main(args: Array<String>) {
    /*
        Осуществляется ввод строк. Следует продублировать строки длина которых меньше
        средней длины всех строк
     */

    val list = arrayListOf<String>()

    val printMsg = { println("Enter new element (enter for continue): ") }
    printMsg()

    val sc = Scanner(System.`in`)
    while (sc.hasNextLine()) {
        val s = sc.nextLine()
        if (s.isBlank()) break
        printMsg()
        list.add(s)
    }

    println("Action!")

    action(list)
    list.forEachIndexed { i, el -> println("$i : $el") }
}