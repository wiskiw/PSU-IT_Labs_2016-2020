import sha.SHA1
import java.math.BigInteger

class KCipher(private val sha1: SHA1, private val keyBuilder: KeyBuilder) {

    private val signatureFileName = "Signature.txt"

    // sign
    fun encode(publicKey: PublicKey, contentFileName: String): BigInteger {
        val fileText = fileReadLine(contentFileName)
        println("KCipherE: Текст для зашифрования: $fileText")

        val shaString = sha1.make(fileText)
        println("KCipherE: Хэш-функция (SHA1) : $shaString")

        val rsa = RSA(keyBuilder)
        val plaintext = BigInteger(shaString.toByteArray())
        val signText = rsa.sign(plaintext, publicKey)
        println("KCipherE: Подписанный хэш: $signText")
        fileWrite(signatureFileName, signText.toString())
        return signText
    }

    // chck sign
    fun decode(publicKey: PublicKey, contentFileName: String): String {
        val rsa = RSA(keyBuilder)

        val encodeStr = fileReadLine(signatureFileName, 0)
        val cipherText = BigInteger(encodeStr)

        val plaintext = rsa.design(cipherText, publicKey)
        val text = String(plaintext.toByteArray())
        println("KCipherD: Расшифрованная хэш: $text")


        //val textToDecrypt = fileReadLine(contentFileName)
        //println("KCipherD: Переданный текст: $textToDecrypt")

        //val sha1 = sha1.make(textToDecrypt)
        //println("KCipherD: Хэш-функция переданного текста: $sha1")

        /*
        if (sha1 == text) {
            println("KCipherD: тексты идентичны")
        } else {
            println("KCipherD: тексты не идентичны")
        }
        */

        return ""
    }

}