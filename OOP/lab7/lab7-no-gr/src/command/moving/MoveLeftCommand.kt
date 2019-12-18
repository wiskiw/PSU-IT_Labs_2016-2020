package command.moving

import Army
import command.Command

class MoveLeftCommand(private val army: Army) : Command {

    override fun execute() {
        army.positionX -= 10
        println("Moving Left")
    }

}