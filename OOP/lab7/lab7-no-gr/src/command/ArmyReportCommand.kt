package command

import Army

class ArmyReportCommand(private val army: Army) : Command {

    override fun execute() {
        println("\tPOS: x:${army.positionX} y:${army.positionY}")
        println("\tgunsState: ${army.gunsState}")
        println("\tvehicleFuelLevel: ${army.vehicleFuelLevel}")
    }

}