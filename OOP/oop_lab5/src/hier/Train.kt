abstract class Train(var carriageCount: Int) : Transport() {

    // final - не может быть переопределен далее
    final override fun beep() {
        println("Tuu-Tuu!")
    }

    override fun toString(): String {
        return "Train(carriageCount=$carriageCount)"
    }

    override fun equals(other: Any?): Boolean {
        if (this === other) return true
        if (javaClass != other?.javaClass) return false
        if (!super.equals(other)) return false

        other as Train

        if (carriageCount != other.carriageCount) return false

        return true
    }

    override fun hashCode(): Int {
        var result = super.hashCode()
        result = 31 * result + carriageCount
        return result
    }


}