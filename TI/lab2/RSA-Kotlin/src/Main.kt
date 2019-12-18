import sha.SHA1J
import java.math.BigInteger

// https://ru.wikipedia.org/wiki/RSA
fun main(args: Array<String>) {


    val keyBuilder = KeyBuilder()
    val cipher = KCipher(SHA1J(), keyBuilder)


    // todo change filename
    cipher.encode(keyBuilder.publicKey, "MessageOrg.txt")
    keyBuilder.savePublicKeyToFile()

    println("---------------------------------")
    val decodeKey = PublicKeyWriter.read()
    val decodedOk = cipher.decode(keyBuilder.publicKey, "MessageToCheck.txt")
    //val decodedError = cipher.decode(PublicKey(BigInteger.ONE, BigInteger("12452351")), "MessageToCheck.txt")


}


