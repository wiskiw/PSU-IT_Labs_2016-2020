import java.util.*

/*
    3) Создать класс осуществляющий чтение и запись объектов классов из потоков ввода и вывода.
    Во время ввода информации следует осуществлять проверку правильности ввода,
    в противном случае метод должен генерировать реализованное исключение.
 */


class TransportIO {

    companion object {

        @Throws(TransportException::class)
        fun readCar(): Car {
            val speed: Int
            val color: String

            print("Input car's speed: ")
            val scanner = Scanner(System.`in`)
            try {
                speed = scanner.nextInt()
            } catch (ex: Throwable) {
                throw TransportException("Incorrect car speed!")
            }

            print("Input car's color type: ")
            scanner.nextLine()
            try {
                color = scanner.nextLine()
            } catch (ex: Throwable) {
                throw TransportException("Incorrect car's color type!")
            }

            val car = Car(color, speed)

            print("Input car's fuel type (enter to set default): ")
            try {
                val fuel = scanner.nextLine()
                if (fuel.isNotBlank()) {
                    car.fuel = fuel
                }
            } catch (ex: Throwable) {
                throw TransportException("Incorrect car's fuel type!")
            }

            return car
        }

        @Throws(TransportException::class)
        fun readExpress(): Express {
            print("Input express's carriage count: ")
            val scanner = Scanner(System.`in`)
            try {
                return Express(scanner.nextInt())
            } catch (ex: Throwable) {
                throw TransportException("Incorrect express's carriage count!")
            }
        }

        fun print(t: Transport) {
            println(t.toString())
        }


    }


}