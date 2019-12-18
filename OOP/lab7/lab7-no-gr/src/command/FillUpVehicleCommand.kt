package command

import Army

class FillUpVehicleCommand(private val army: Army) : Command {

    override fun execute() {
        army.vehicleFuelLevel = 10
        println("Filling up army vehicle")
    }

}