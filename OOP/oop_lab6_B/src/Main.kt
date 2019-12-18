import company.Company
import java.util.*
import kotlin.collections.ArrayList


/*

    В рамках данного задания необходимо переделать задание первой лабораторной работы.
Пользователь выбирает поле и направление сортировки, осуществляет ввод данных, по которым
создаются элементы класса, которые заносятся в коллекцию. Отсортированная коллекция выводится
на экран. Так же пользователю должна быть предоставлена возможность осуществлять поиск по
коллекции, который должен быть реализован с использование итераторов.

 */

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
    val list = arrayListOf<Company>()

    prefill(list)

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
    println(" 1 - sort")
    println(" 2 - search")
    println(" 3 - print")
    val ta = {
        println(" Incorrect value, try again")
        mainMenu(list, scanner)
    }

    try {
        when (scanner.nextInt()) {
            1 -> sortList(list)
            2 -> findInList(list)
            3 -> printList(list)
            else -> ta()
        }
        mainMenu(list, scanner)
    } catch (ex: NumberFormatException) {
        ta()
    }
}


fun sortList(list: ArrayList<Company>) {
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

fun findInList(list: ArrayList<Company>) {
    val scanner = Scanner(System.`in`)

    print("Find: ")
    val searchVal = scanner.nextLine()

    println("Searching for '$searchVal'...")

    val listCopy = ArrayList(list)
    val iter = listCopy.iterator()
    while (iter.hasNext()) {
        if (!iter.next().contains(searchVal)) {
            iter.remove()
        }
    }


    if (listCopy.size > 0) {
        print("Results [${listCopy.size}]: ")
        printList(listCopy)
    } else {
        println("Nothing was found")
    }
}

private fun printList(list: List<Any>) {
    println("\n")
    list.forEach { println("=====\n$it") }
}