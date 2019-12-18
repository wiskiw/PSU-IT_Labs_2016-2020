import java.util.*

class Company {

    var id = 0
    var name = ""
    var address = ""
    var tel = ""
    var owner = ""
    var createDate: Long = 0

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


    fun scannOrderId(): Long {
        val scanner = Scanner(System.`in`)
        print("Enter order id: ")
        return scanner.nextLong()
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

    override fun equals(other: Any?): Boolean {
        if (this === other) return true
        if (javaClass != other?.javaClass) return false

        other as Company

        if (id != other.id) return false
        if (name != other.name) return false
        if (address != other.address) return false
        if (tel != other.tel) return false
        if (owner != other.owner) return false
        if (createDate != other.createDate) return false

        return true
    }

    override fun hashCode(): Int {
        var result = id
        result = 31 * result + name.hashCode()
        result = 31 * result + address.hashCode()
        result = 31 * result + tel.hashCode()
        result = 31 * result + owner.hashCode()
        result = 31 * result + createDate.hashCode()
        return result
    }


}