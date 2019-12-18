package command.moving

import Army
import command.Command

class MoveDownCommand(private val army: Army) : Command {

    override fun execute() {
        army.positionY -= 10
        println("Moving down")
    }

}