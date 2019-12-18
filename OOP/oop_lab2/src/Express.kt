class Express(carriageCount: Int) : Train(carriageCount) {

    //constructor(carriageCount: Int) : super(carriageCount)

    override var speed = 75
    override var fuel = "ELECTRICITY"

    override fun go() {
        println("Fast express-train is going on trails with $carriageCount carriage(s) " +
                "at $speed km/h on $fuel fuel")
    }
}