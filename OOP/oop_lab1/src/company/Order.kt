package company

import java.util.*

class Order() {

    var name = ""
    var price = 0
    var state: ProgressState = ProgressState.IN_QUEUE
    var customer = ""
    var executor: Company? = null

    constructor(name: String, price: Int) : this() {
        this.name = name
        this.price = price
    }

    enum class ProgressState {
        NONE, IN_QUEUE, IN_PROGRESS, COMPLETE
    }

    companion object {
        fun scannNewOrder(): Order {
            val o = Order()
            val scanner = Scanner(System.`in`)
            o.customer = o.readStringField("customer")
            o.name = o.readStringField("name")
            print("Enter order price: ")
            o.price = scanner.nextInt()
            return o
        }
    }

    private fun readStringField(fieldName: String): String {
        val scanner = Scanner(System.`in`)
        print("Enter order $fieldName: ")
        var result = scanner.nextLine() ?: ""
        while (result.isEmpty()) {
            print("company.Company $fieldName cannot be empty! Try again: ")
            result = scanner.nextLine() ?: ""
        }
        return result
    }


    override fun toString(): String {
        return "Order (name='$name', price=$price, state=${state.name}" +
                executor?.let { " executor=" + it.name } + ")"
    }
}