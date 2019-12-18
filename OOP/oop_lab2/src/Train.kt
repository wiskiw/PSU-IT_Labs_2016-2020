abstract class Train(var carriageCount: Int) : Transport() {

    // final - не может быть переопределен далее
    final override fun beep() {
        println("Tuu-Tuu!")
    }

}