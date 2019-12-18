import java.io.File
import java.util.*

/*

    В рамках данного задания необходимо переделать задание второй лабораторной работы для
    решения следующей задачи:
    - добавление записей в список,
    - вывод записей,
    - сортировка записей по указанному полю и направлению,
    - запись списка записей в файл и чтение записей из файла в список.
            Для хранения записей используйте бинарный файл.

 */
val list = arrayListOf<Company>()
const val FILENAME = "./database.bin"


private fun prefill(list: ArrayList<Company>) {
    val myCompany = Company()
    myCompany.id = 1223
    myCompany.address = "Pushkina street"
    myCompany.name = "Epam"
    myCompany.owner = "B"
    list.add(myCompany)

    val c2 = Company()
    c2.id = 8
    c2.address = "Lenina street 18"
    c2.name = "Oracle"
    c2.owner = "A"
    list.add(c2)

    val c3 = Company()
    c3.id = 19
    c3.tel = "223 23 42"
    c3.owner = "Mark"
    c3.address = "Skarini street 18"
    c3.name = "Oracle"
    list.add(c3)

    val c4 = Company()
    c4.id = 1
    c4.tel = "223 23 42"
    c4.owner = "Gavin Belson"
    c4.address = "Silicon Vally 1"
    c4.name = "Hooli"
    list.add(c4)

    val piedPiper = Company()
    piedPiper.id = 2
    piedPiper.tel = "223 22 33"
    piedPiper.owner = "Richard Hendricks"
    piedPiper.address = "Silicon Vally 2"
    piedPiper.name = "Pied Piper"
    list.add(piedPiper)
}

fun main(args: Array<String>) {

    //prefill(list)

    val printMsg = { println("Press enter to add (print 'e' to continue): ") }
    printMsg()

    val sc = Scanner(System.`in`)
    while (sc.hasNextLine()) {
        val s = sc.nextLine()
        if (s.toLowerCase().trim() == "e") break
        val c = Company()
        c.readNew()
        list.add(c)

        println()
        printMsg()
    }
    mainMenu(list)
}


fun mainMenu(list: ArrayList<Company>, scanner: Scanner = Scanner(System.`in`)) {
    println("\n 1 - add")
    println(" 2 - sort")
    println(" 3 - print")
    println(" 4 - save")
    println(" 5 - load")
    val ta = {
        println(" Incorrect value, try again")
        mainMenu(list, scanner)
    }

    try {
        when (scanner.nextInt()) {
            1 -> addNew()
            2 -> sortList()
            3 -> printList(list)
            4 -> saveList()
            5 -> loadList()
            else -> ta()
        }
        mainMenu(list, scanner)
    } catch (ex: NumberFormatException) {
        ta()
    }
}

fun loadList() {
    val content = File(FILENAME).readBytes().toString(Charsets.UTF_8)
    list.clear()
    content.split("---\n").forEach {
        val c = Company()
        if (c.stringDecode(it.trim())) {
            list.add(c)
        }
    }
}

fun saveList() {
    var toWrite = ""
    list.forEach {
        println()
        println(it.stringEncode())
        toWrite += it.stringEncode()
        toWrite += "---\n"
    }
    toWrite = toWrite.trim('\n', '-')

    File(FILENAME).writeBytes(toWrite.toByteArray(Charsets.UTF_8))
}


fun addNew() {
    val c = Company()
    c.readNew()
    list.add(c)
}

fun sortList() {
    val scanner = Scanner(System.`in`)
    print("Field ( Id:1 ; Name:2 ; Address:3 ; Tel:4 , Owner:5): ")
    val fId = scanner.nextInt()
    when {
        fId > 5 -> return
        fId < 1 -> return
    }

    print("Direction ( A-z:1 ; Z-a:2 ): ")
    val sId = scanner.nextInt()
    when {
        sId > 2 -> return
        sId < 1 -> return
    }

    when (fId) {
        1 -> list.sortBy { it.id }
        2 -> list.sortBy { it.name }
        3 -> list.sortBy { it.address }
        4 -> list.sortBy { it.tel }
        5 -> list.sortBy { it.owner }
        else -> throw IllegalArgumentException("Unknown field to sort")
    }

    if (sId == 2) {
        list.reverse()
    }

    printList(list)
}

private fun printList(list: List<Any>) {
    println("\n")
    list.forEach { println("=====\n$it") }
}