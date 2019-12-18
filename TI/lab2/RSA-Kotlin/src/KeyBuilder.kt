import java.math.BigInteger
import java.security.SecureRandom


data class PublicKey(val n: BigInteger, val e: BigInteger)
// n - произведение
// e - открытая экспонента (выбирается)


/**
 * Генерирует ключ:
1. Выбрать два простых различных числа
2. Вычислить произведение
3. Вычислить функцию Эйлера
4. Выбрать открытую экспоненту
5. Вычислить секретную экспоненту
6. Опубликовать открытый ключ
7. Сохранить закрытый ключ
 */


class KeyBuilder(private val bits: Int = 1024) {


    // секретная экспонента
    val d: BigInteger

    val publicKey: PublicKey

    init {
        val r = SecureRandom()
        val p = BigInteger(this.bits / 2, 100, r)
        val q = BigInteger(this.bits / 2, 100, r)
        val n = p.multiply(q) // *

        val m = p.subtract(BigInteger.ONE).multiply(q.subtract(BigInteger.ONE))
        var e = BigInteger("3")
        while (m.gcd(e).toInt() > 1) {
            e = e.add(BigInteger("2"))
        }
        publicKey = PublicKey(n, e)

        d = e.modInverse(m)
        println("KeyBuilder: Закрытый ключ d: $d")
        println("KeyBuilder: Закрытый ключ n: $n")

        println("KeyBuilder: Открытый ключ n: ${publicKey.n}")
        println("KeyBuilder: Открытый ключ e: ${publicKey.e}")

    }

    fun savePublicKeyToFile(){
        PublicKeyWriter.write(publicKey = publicKey)
    }


}