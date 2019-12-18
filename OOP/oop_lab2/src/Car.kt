class Car(val color : String, override var speed : Int) : Transport() {

    override var fuel = "PETROL"

    override fun go() {
        println("$color car riding on the road at $speed km/h on $fuel fuel")
    }


}