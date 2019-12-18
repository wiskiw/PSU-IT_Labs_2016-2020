abstract class Transport {

    open var speed = 0
    open var fuel = "none"

    abstract fun go() // ехать

    // гудеть
    open fun beep() {
        println("Beep-Beep!")
    }

    override fun toString(): String {
        return "Transport(speed=$speed, fuel='$fuel')"
    }

    override fun equals(other: Any?): Boolean {
        if (this === other) return true
        if (javaClass != other?.javaClass) return false

        other as Transport

        if (speed != other.speed) return false
        if (fuel != other.fuel) return false

        return true
    }

    override fun hashCode(): Int {
        var result = speed
        result = 31 * result + fuel.hashCode()
        return result
    }


}