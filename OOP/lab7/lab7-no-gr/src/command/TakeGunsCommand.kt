package command

import Army

class TakeGunsCommand(private val army: Army) : Command {

    override fun execute() {
        army.gunsState = "shown"
        println("Taking guns")
    }

}