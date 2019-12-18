import compamy.CarRepairCompany
import kotlinx.coroutines.delay
import kotlinx.coroutines.runBlocking

// https://refactoring.guru/ru/design-patterns/factory-method/java/example

fun main(args: Array<String>) {


    val brokenStaffA = object : Brokenable {
        var fixed = false
        override fun isBroken() = fixed

        override suspend fun tryToFix() {
            println("tryToFix brokenStaffA...")
            delay(100)
            fixed = Math.random() < 0.5
        }
    }

    val brokenStaffB = object : Brokenable {
        var fixed = false
        override fun isBroken() = fixed

        override suspend fun tryToFix() {
            println("tryToFix brokenStaffB...")
            delay(100)
            fixed = Math.random() < 0.5
        }
    }

    // создаем компанию
    val carRepairCompany = CarRepairCompany()

    // запускаем работу компании
    carRepairCompany.startWork()

    // добавляем сломаный премдметы на ремонт
    carRepairCompany.addToRepair(brokenStaffA)
    carRepairCompany.addToRepair(brokenStaffB)

    runBlocking {
        // останавливаем работу компании через 5 секунды
        Thread.sleep(5000)
    }
    carRepairCompany.stopWork()

}