class Express(carriageCount: Int) : Train(carriageCount) {

    //constructor(carriageCount: Int) : super(carriageCount)

    override var speed = 75
    override var fuel = "ELECTRICITY"

    override fun go() {
        println("Fast express-train is going on trails with $carriageCount carriage(s) " +
                "at $speed km/h on $fuel fuel")
    }

    override fun toString(): String {
        return "Express(speed=$speed, fuel='$fuel')"
    }

    override fun equals(other: Any?): Boolean {
        if (this === other) return true
        if (javaClass != other?.javaClass) return false
        if (!super.equals(other)) return false

        other as Express

        if (speed != other.speed) return false
        if (fuel != other.fuel) return false

        return true
    }

    override fun hashCode(): Int {
        var result = super.hashCode()
        result = 31 * result + speed
        result = 31 * result + fuel.hashCode()
        return result
    }


}