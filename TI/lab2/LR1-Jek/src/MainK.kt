import java.io.*
import java.lang.Math

object Main {

    private val Table = File("et.txt")
    private var mFileWriter: FileWriter
    //public Main() throws IOException {
    //}

    //

    fun lg(x: Double): Int {
        return (Math.log(x) / Math.log(2.0)).toInt()
    }

    init {
        mFileWriter = FileWriter(Table, false)
    }

    fun decode() {
        var n: Int
        try {
            val reader = FileReader(Table)
            val br = BufferedReader(reader)
            val codes = arrayOfNulls<String>(256)

            val result = File("dec.txt")
            mFileWriter = FileWriter(result)

            for (i in 0..255) {
                codes[i] = br.readLine()
            }
            val bufferedReader = BufferedReader(FileReader("my-result.txt"))
            val chr = bufferedReader.read().toChar()

            n = Integer.parseInt(String() + chr)
            var symbyle = bufferedReader.read()
            while (symbyle != -1) {
                symbyle = bufferedReader.read()
                var code = ""
                while (symbyle != -1 && symbyle.toChar() != ' ') {
                    code += symbyle.toChar()
                    symbyle = bufferedReader.read()
                    //System.out.println(code);
                }

                var index = 0
                if (code != "")
                    for (t in 0..255) {
                        index = t
                        if (codes[t] == code) break
                    }
                if (code != "")
                    for (t in 0..index) {
                        print(n)
                        mFileWriter!!.write("" + n)
                        mFileWriter!!.flush()
                    }

                if (n == 0)
                    n = 1
                else
                    n = 0
            }
        } catch (e: FileNotFoundException) {
            e.printStackTrace()
        } catch (e: IOException) {
            e.printStackTrace()
        }

    }

    fun elliasCodeTable() {
        mFileWriter.write("0\n")
        var code: String

        for (i in 2..255) {
            code = Integer.toString(i, 2)
            var n = i
            var play = true
            while (play) {
                when (lg(n.toDouble())) {
                    2 -> {
                        code = "10$code"
                        play = false
                    }
                    3 -> {
                        code = "11$code"
                        play = false
                    }
                    4 -> {
                        code = "100$code"
                        n = lg(n.toDouble())
                    }
                    5 -> {
                        code = "101$code"
                        n = lg(n.toDouble())
                    }
                    6 -> {
                        code = "110$code"
                        n = lg(n.toDouble())
                    }
                    7 -> {
                        code = "111$code"
                        n = lg(n.toDouble())
                    }
                    else -> play = false
                }//n = lg(n);
            }
            code = code + "0\n"
            mFileWriter!!.write(code)
            mFileWriter!!.flush()
        }
    }

    fun compress(SourceName: String, ResultName: String) {
        val sizeBefore: Double
        val sizeAfter: Double
        val koef: Double

        val from = File(SourceName)
        var reader = FileReader(from)
        var br = BufferedReader(reader)
        var line = br.readLine()

        sizeBefore = line.length.toDouble()

        val bin: CharArray
        bin = line.toCharArray()
        line = ""
        val numbers = IntArray(1024)
        var index = 0
        run {
            var i = 0
            while (i < sizeBefore) {
                var serie = 0
                var serie1 = 0
                if (i + 1 > sizeBefore) {
                    break
                }

                while (i < bin.size && bin[i] == '1') {
                    serie1++
                    i++
                }
                if (serie1 > 0) {
                    i--
                    line += serie1
                    numbers[index] = serie1
                    index++
                }
                while (i < bin.size && bin[i] == '0') {
                    serie++
                    i++
                }
                if (serie > 0) {
                    i--
                    line += serie
                    numbers[index] = serie
                    index++
                }
                i++
            }
        }
        numbers[index] = -1


        reader = FileReader(Table)
        br = BufferedReader(reader)
        val codes = arrayOfNulls<String>(256)
        for (i in 0..255) {
            codes[i] = br.readLine()
        }
        val result = File(ResultName)
        mFileWriter = FileWriter(result)
        line = ""
        mFileWriter.write(bin[0] + " ")
        var i = 0
        while (numbers[i] != -1) {

            line += codes[numbers[i] - 1] + " "
            mFileWriter.write(codes[numbers[i] - 1] + " ")
            mFileWriter.flush()
            i++
        }
        sizeAfter = line.length.toDouble()
        koef = sizeAfter / sizeBefore * 100
        println("Коэффициент сжатия")
        println(koef)
    }

}


fun main(args: Array<String>) {
    Main.elliasCodeTable()
    Main.compress("src.txt", "my-result.txt")
    println("\nДекодированный файл:")
    Main.decode()
    println("\nИсходный файл:")
    Main.decode()

    val From = File("src.txt")
    val Reader = FileReader(From)
    val br = BufferedReader(Reader)
    val line = br.readLine()
    val FromD = File("my-result.txt")
    val ReaderD = FileReader(FromD)
    val brD = BufferedReader(ReaderD)
    val lineD = brD.readLine()

    val sizeBefore = line.length.toDouble()
    val sizeBeforeD = lineD.length.toDouble()

    val bin: CharArray
    bin = line.toCharArray()
    var count = 0
    var i = 0
    while (i < sizeBefore) {
        if (bin[i] == bin[i])
            count++
        i++
    }
    if (count.toDouble() == sizeBefore)
        print("\nРезультаты совпадают")
    else
        print("\nРезультаты не совпадают")
}