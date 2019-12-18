import java.io.Serializable
import java.util.*

class Company : Serializable {

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


    fun readNew() {
        readId()
        readName()
        readAddress()
        readTel()
        readOwner()
    }

    private fun readStringField(fieldName: String): String {
        val scanner = Scanner(System.`in`)
        print("Enter company $fieldName: ")
        var result = scanner.nextLine() ?: ""
        while (result.isEmpty()) {
            print("Company $fieldName cannot be empty! Try again: ")
            result = scanner.nextLine() ?: ""
        }
        return result
    }

    private fun readIntField(fieldName: String): Int {
        var strInt: String
        fun tryReturn(): Int {
            return try {
                strInt = readStringField(fieldName)
                strInt.trim().toInt()
            } catch (ex: NumberFormatException) {
                print("Incorrect value for company $fieldName! Try again: ")
                tryReturn()

            }
        }
        return tryReturn()
    }

    fun readId() {
        this.id = readIntField("ID")
    }

    fun printId() {
        println("Company ID: ${this.id}")
    }

    fun readName() {
        this.name = readStringField("name")
    }

    fun printName() {
        println("Company name: ${this.name}")
    }

    fun readAddress() {
        this.address = readStringField("address")
    }

    fun printAddress() {
        println("Company address: ${this.address}")
    }


    fun readTel() {
        this.address = readStringField("phone number")
    }

    fun printTel() {
        println("Company phone number: ${this.tel}")
    }

    fun readOwner() {
        this.address = readStringField("owner")
    }

    fun printOwner() {
        println("Company owner: ${this.owner}")
    }

    fun printCreateDate() {
        println("Company create date: ${this.createDate}ms")
    }

    override fun toString(): String {
        var s = "Company '$name' [id:$id]:"
        s += "\n\taddress: $address"
        s += "\n\ttel: $tel"
        s += "\n\towner: $owner"
        s += "\n\tcreate date: ${Date(createDate)}"
        return s
    }

    fun contains(string: String): Boolean {
        return when {
            id.toString().contains(string, true) -> true
            name.contains(string, true) -> true
            tel.contains(string, true) -> true
            address.contains(string, true) -> true
            owner.contains(string, true) -> true
            createDate.toString().contains(string, true) -> true
            Date(createDate).toString().contains(string, true) -> true
            else -> false
        }
    }

    fun stringEncode(): String {
        var s = ""
        s += "$id\n"
        s += "$name\n"
        s += "$address\n"
        s += "$tel\n"
        s += "$owner\n"
        s += "$createDate\n"
        s.trim()
        return s
    }

    fun stringDecode(encoded: String): Boolean {
        val arr = encoded
                .split("\n")
                .map { it.trim() }
        if (arr.size != 6) return false
        return try {
            arr.forEachIndexed { index, s ->
                when (index) {
                    0 -> id = s.toInt()
                    1 -> name = s
                    2 -> address = s
                    3 -> tel = s
                    4 -> owner = s
                    5 -> createDate = s.toLong()
                }
            }
            true
        } catch (ex: NumberFormatException) {
            throw ex
            false
        }
    }

}