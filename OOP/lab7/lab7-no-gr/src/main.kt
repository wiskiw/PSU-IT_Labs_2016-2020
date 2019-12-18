import command.*
import command.moving.MoveDownCommand
import command.moving.MoveLeftCommand
import command.moving.MoveRightCommand
import command.moving.MoveUpCommand
import java.util.*

// 6. Командование армией (Команда)
// лаба 7

fun printCommands() {
    println("0 - army report")
    println("1 - take guns")
    println("2 - hide guns")
    println("3 - go up")
    println("4 - go down")
    println("5 - go right")
    println("6 - go left")
    println("7 - fill up vehicle")
}

fun getCommandByN(n: Int, army: Army): Command {
    return when (n) {
        0 -> ArmyReportCommand(army)
        1 -> TakeGunsCommand(army)
        2 -> HideGunsCommand(army)
        3 -> MoveUpCommand(army)
        4 -> MoveDownCommand(army)
        5 -> MoveRightCommand(army)
        6 -> MoveLeftCommand(army)
        7 -> FillUpVehicleCommand(army)
        else -> throw RuntimeException("Unknown command")
    }
}

fun getCommandsQueue(): IntArray {
    val scanner = Scanner(System.`in`)
    val input = scanner.nextLine()

    val result = IntArray(input.trim().length)

    input.forEachIndexed { index, c ->
        result[index] = (c - 48).toInt()
    }
    return result
}


fun main(args: Array<String>) {
    printCommands()
    val commandsQueue = getCommandsQueue()
    println("Commands: " + commandsQueue.joinToString { i -> i.toString() })

    val army = Army()
    val cap = Cap()

    commandsQueue.forEach {
        cap.add(getCommandByN(it, army))
    }
    cap.work()
}