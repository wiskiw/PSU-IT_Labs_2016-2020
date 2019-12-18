

// Функции-расширения (extension function)
fun String.getFirstWord(separator: String = " "): String {
    val index = indexOf(separator)

    return if (index < 0) {
        this
    } else {
        substring(0, index)
    }
}


// ***************************************


fun main(args: Array<String>) {
    val fullName = "Ivan Ivanov, Ivanovich"

    println(fullName.getFirstWord())

    println(fullName.getFirstWord(","))
}


