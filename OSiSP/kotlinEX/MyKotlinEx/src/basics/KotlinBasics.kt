package basics

@SuppressWarnings("ALL")
@Suppress("UNREACHABLE_CODE", "CanBeVal")
class KotlinBasics {


    private fun stringConcatenation() {
        val firstName = "Amit"
        val lastName = "Shekhar"

        println("My name is: $firstName $lastName")
    }

    private fun smartCasting(obj: Any) {
        if (obj is Car) {
            println("Speed : " + obj.speed)
        }
    }


    private fun multipleConditions(n: Int) {
        if (n in 0..150) {
            // do something
        }


        for (i in 0..19) {
            println("id: $i")
        }


        when (n) {
            1 -> println("One")
            2 -> println("Two")
            3 -> println("Three")
            4, 5, 6 -> println(" 3 < n < 7 ")
            else -> println(" n >= 7 ")
        }
    }


    private fun nullSafety() {


        var msg0: String = null // ошибка компиляции
        // но если сильно хочется, то можно (но так делать не надо)
        msg0 = null!!


        var msg1: String? = null


        msg1?.let {
            println("len: ${msg1.length}")
        }

        // Еще проще
        println("len: ${msg1?.length ?: 0}")

    }


    // Вариант 1
    private fun method0(value: Int): Int {
        return 2 * value
    }

    // Вариант 2
    private fun method1(value: Int): Int = 2 * value


    // Вариант 3
    private fun method2(value: Int) = 2 * value


    // Вариант 4
    // Значение по умолчанию: value = 0
    private fun method3(value: Int = 0) = 2 * value


    private fun concatinate(prefix: Char = '.', str: String, postfix: Char = '.'): String {
        return prefix + str + postfix
    }


    private fun callConcatinatin() {
        println(concatinate('+', "hello", '-'))

        println(concatinate(prefix = '+', str = "hello"))
        println(concatinate(postfix = '-', str = "Hello"))
    }


}
