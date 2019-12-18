import java.util.*

class TransportCollection {

    private val list = arrayListOf<Transport>()

    private fun scannCar(forceInput: Boolean = false): Car? {
        val scanner = Scanner(System.`in`)
        while (true) {
            try {
                return TransportIO.readCar()
            } catch (ex: TransportException) {
                if (!forceInput) {
                    println("Try again? (enter for cancel)")
                    if (scanner.nextLine().isBlank()) {
                        return null
                    }
                } else {
                    println("Try again: ")
                }
            }
        }
    }

    private fun scannExpress(forceInput: Boolean = false): Express? {
        val scanner = Scanner(System.`in`)
        while (true) {
            try {
                return TransportIO.readExpress()
            } catch (ex: TransportException) {
                if (!forceInput) {
                    println("Try again? (enter for cancel)")
                    if (scanner.nextLine().isBlank()) {
                        return null
                    }
                } else {
                    println("Try again: ")
                }
            }
        }
    }

    fun addCar() {
        println("\nInput car: ")
        scannCar()?.let {
            list.add(it)
        }
    }

    fun addExpress() {
        println("\nInput express: ")
        scannExpress()?.let {
            list.add(it)
        }
    }

    private fun find(transport: Transport) = list.find { it == transport }

    fun searchForCar() {
        println(find(scannCar(true)!!) ?: "Car not found")
    }

    fun searchForExpress() {
        println(find(scannExpress(true)!!) ?: "Express not found")
    }

    override fun toString(): String {
        return if (list.isEmpty())
            "TransportCollection : empty"
        else
            "TransportCollection : (\n\t${list.joinToString(",\n\t")}\n)"
    }


}