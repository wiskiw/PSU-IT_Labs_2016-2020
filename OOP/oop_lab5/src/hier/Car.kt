class Car(val color : String, override var speed : Int) : Transport() {

    override var fuel = "PETROL"

    override fun go() {
        println("$color car riding on the road at $speed km/h on $fuel fuel")
    }

    override fun toString(): String {
        return "Car(color='$color', speed=$speed, fuel='$fuel')"
    }

    override fun equals(other: Any?): Boolean {
        if (this === other) return true
        if (javaClass != other?.javaClass) return false
        if (!super.equals(other)) return false

        other as Car

        if (color != other.color) return false
        if (speed != other.speed) return false
        if (fuel != other.fuel) return false

        return true
    }

    override fun hashCode(): Int {
        var result = super.hashCode()
        result = 31 * result + color.hashCode()
        result = 31 * result + speed
        result = 31 * result + fuel.hashCode()
        return result
    }


}