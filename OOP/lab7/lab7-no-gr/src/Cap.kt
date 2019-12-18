import command.Command
import java.util.*


// invoker
class Cap {

    var commandQueue = LinkedList<Command>()

    fun add(command: Command) {
        commandQueue.add(command)
    }

    fun work() {
        val iter = commandQueue.iterator()
        var command: Command
        while (iter.hasNext()) {
            command = iter.next()
            command.execute()
        }
        commandQueue.clear()
    }

}