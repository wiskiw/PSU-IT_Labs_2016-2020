import java.io.FileReader
import java.io.FileWriter
import java.math.BigInteger

fun fileWrite(fileName: String, content: String) {
    val fileWriter = FileWriter(fileName)
    fileWriter.write(content)
    fileWriter.close()
}

fun fileReadLine(fileName: String, lineIndex: Int = 0): String {
    val fileReader = FileReader(fileName)
    return fileReader.readLines()[lineIndex].also {
        fileReader.close()
    }
}

object PublicKeyWriter {

    private val fileName = "PublicKey.txt"

    fun read(fName: String = fileName): PublicKey {
        val fileReader = FileReader(fName)
        val lines = fileReader.readLines()
        val eStr = lines[0]
        val nStr = lines[1]
        return PublicKey(BigInteger(nStr), BigInteger(eStr))


    }

    fun write(fName: String = fileName, publicKey: PublicKey) {
        val fileWriter = FileWriter(fName)
        fileWriter.write((publicKey.e.toString() + "\n" + publicKey.n.toString()))
        fileWriter.close()
    }

}