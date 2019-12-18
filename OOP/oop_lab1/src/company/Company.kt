package company

import java.util.*

class Company {

    var id = 0
    var name = ""
    var address = ""
    var tel = ""
    var owner = ""
    var createDate: Long = 0
    val orderList = mutableMapOf<Long, Order>()


    /*

        список заказов для компаний



     */


    constructor()

    constructor(company: Company) {
        this.id = company.id
        this.name = company.name
        this.address = company.address
        this.tel = company.tel
        this.owner = company.owner
        this.createDate = company.createDate
    }

    constructor(id: Int, name: String) {
        this.id = id
        this.name = name
    }

    fun printOrderList() {
        if (orderList.isEmpty()) {
            println("Orders not found")
        } else {
            println("Found orders: ${orderList.size}")
            orderList.forEach { o -> print(o.toString()) }
        }
    }

    fun addOrder(order: Order): Long {
        order.executor = this
        val orderId = System.currentTimeMillis() % 10000
        orderList[orderId] = order
        return orderId
    }

    fun removeOrder(orderId: Long) {
        orderList.remove(orderId)
    }

    fun mainLoop() {
        val scanner = Scanner(System.`in`)
        while (true) {
            println("\n====Company menu====")
            println("1. add order")
            println("2. update order")
            println("3. remove order")
            println("4. print list")
            println("0. exit")
            when (scanner.nextInt()) {
                1 -> {
                    val orderId = addOrder(Order.scannNewOrder())
                    print("Your order id: $orderId ")
                }
                2 -> {
                    val state = updateOrderProgressState(scannOrderId())
                    if (state == Order.ProgressState.NONE) {
                        println("This company do not working on this order")
                    } else {
                        println("Order state update: ${state.name}")
                    }
                }
                3 -> removeOrder(scannOrderId())
                4 -> printOrderList()
                else -> return
            }
        }

    }


    fun scannOrderId(): Long {
        val scanner = Scanner(System.`in`)
        print("Enter order id: ")
        return scanner.nextLong()
    }


    private fun updateOrderProgressState(orderId: Long): Order.ProgressState {
        val order = orderList[orderId] ?: return Order.ProgressState.NONE
        when (order.state) {
            Order.ProgressState.IN_QUEUE -> order.state = Order.ProgressState.IN_PROGRESS
            Order.ProgressState.IN_PROGRESS -> order.state = Order.ProgressState.COMPLETE
        }
        if (order.state == Order.ProgressState.COMPLETE) {
            orderList.remove(orderId)
        }
        return order.state
    }

    private fun readStringField(fieldName: String): String {
        val scanner = Scanner(System.`in`)
        print("Enter company $fieldName: ")
        var result = scanner.nextLine() ?: ""
        while (result.isEmpty()) {
            print("company.Company $fieldName cannot be empty! Try again: ")
            result = scanner.nextLine() ?: ""
        }
        return result
    }

    fun readId() {
        val scanner = Scanner(System.`in`)
        print("Enter company ID: ")
        this.id = scanner.nextInt()
    }

    fun printId() {
        println("company.Company ID: ${this.id}")
    }

    fun readName() {
        this.name = readStringField("name")
    }

    fun printName() {
        println("company.Company name: ${this.name}")
    }

    fun readAddress() {
        this.address = readStringField("address")
    }

    fun printAddress() {
        println("company.Company address: ${this.address}")
    }


    fun readTel() {
        this.address = readStringField("phone number")
    }

    fun printTel() {
        println("company.Company phone number: ${this.tel}")
    }

    fun readOwner() {
        this.address = readStringField("owner")
    }

    fun printOwner() {
        println("company.Company owner: ${this.owner}")
    }

    fun printCreateDate() {
        println("company.Company create date: ${this.createDate}ms")
    }


}