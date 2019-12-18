class SomeClass(val id: Int) {

    val name = ""

    fun bark() {
        println("Meow")
    }

    override fun toString(): String {
        return "SomeClass(id=$id, name='$name')"
    }

    override fun equals(other: Any?): Boolean {
        if (this === other) return true
        if (javaClass != other?.javaClass) return false

        other as SomeClass

        if (id != other.id) return false
        if (name != other.name) return false

        return true
    }

    override fun hashCode(): Int {
        var result = id
        result = 31 * result + name.hashCode()
        return result
    }


}