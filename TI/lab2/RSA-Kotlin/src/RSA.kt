import java.math.BigInteger

/*

 */
class RSA(private val keyBuilder :KeyBuilder, bits: Int = 1024) {

    /**
     * Подпись
     */
    fun sign(message: BigInteger, publicKey: PublicKey): BigInteger {
        return message.modPow(keyBuilder.d, publicKey.n)
    }

    /**
     * Проверка подписи
     */
    fun design(message: BigInteger, publicKey: PublicKey): BigInteger {
        // (this^exponent mod m). Unlike pow, this method permits negative exponents.
        return message.modPow(publicKey.e, publicKey.n)
    }

}