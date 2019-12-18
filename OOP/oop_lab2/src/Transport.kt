abstract class Transport {

    companion object {
        // java static fields

        @JvmStatic
        val transportList = mutableListOf<Transport>()

        @JvmStatic
        fun printList() {
            for (t in transportList) {
                println("=======")
                t.go()
                t.beep()
            }
        }
    }

    open var speed = 0
    open var fuel = "none"

    abstract fun go() // ехать

    // гудеть
    open fun beep() {
        println("Beep-Beep!")
    }




}