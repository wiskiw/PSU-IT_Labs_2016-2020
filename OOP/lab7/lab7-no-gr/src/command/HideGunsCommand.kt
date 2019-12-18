package command

import Army

class HideGunsCommand(private val army: Army) : Command {

    override fun execute() {
        army.gunsState = "hidden"
        println("Hiding guns")
    }

}