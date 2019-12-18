package command.moving

import Army
import command.Command

class MoveUpCommand(private val army: Army) : Command {

    override fun execute() {
        army.positionY += 10
        println("Moving Up")
    }

}