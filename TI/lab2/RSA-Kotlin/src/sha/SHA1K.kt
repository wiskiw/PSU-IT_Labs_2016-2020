package sha

class SHA1K : SHA1 {


    /*
     * Побитовое вращение 32-битного числа влево
     */
    private fun rol(num: Int, cnt: Int): Int {
        return num shl cnt or num.ushr(32 - cnt)
    }

    /*
   * Берет строку и возвращает представление base64 своего sha.SHA1K-1.
   */
    override fun make(str: String): String {

        // Преобразование строки в последовательность блоков из 16 слов, хранящихся в виде массива.
        // Добавляем биты заполнения и длину, как описано в стандарте sha.SHA1K

        val x = str.toByteArray()
        val blks = IntArray(((x.size + 8 shr 6) + 1) * 16)


        var i = 0
        while (i < x.size) {
            blks[i shr 2] = blks[i shr 2] or ((x[i]).toInt() shl 24 - i % 4 * 8)
            i++
        }

        blks[i shr 2] = blks[i shr 2] or (0x80 shl 24 - i % 4 * 8)
        blks[blks.size - 1] = x.size * 8

        // вычислить 160-битный sha.SHA1K-хэш последовательности блоков

        val w = IntArray(80)

        var a = 1732584193
        var b = -271733879
        var c = -1732584194
        var d = 271733878
        var e = -1009589776

        i = 0
        while (i < blks.size) {
            val olda = a
            val oldb = b
            val oldc = c
            val oldd = d
            val olde = e

            for (j in 0..79) {
                w[j] = if (j < 16)
                    blks[i + j]
                else
                    rol(w[j - 3] xor w[j - 8] xor w[j - 14] xor w[j - 16], 1)

                val t = (rol(a, 5) + e + w[j] +
                        when {
                            j < 20 -> 1518500249 + (b and c or (b.inv() and d))
                            j < 40 -> 1859775393 + (b xor c xor d)
                            j < 60 -> -1894007588 + (b and c or (b and d) or (c and d))
                            else -> -899497514 + (b xor c xor d)
                        })
                e = d
                d = c
                c = rol(b, 30)
                b = a
                a = t
            }

            a += olda
            b += oldb
            c += oldc
            d += oldd
            e += olde
            i += 16
        }

        // Преобразовать 160-битный хэш в base64

        val words = intArrayOf(a, b, c, d, e)
        val sb = StringBuilder()

        for (word in words) {
            var hexWord = Integer.toHexString(word)
            while (hexWord.length < 8) {
                hexWord = "0$hexWord"
            }
            sb.append(hexWord)
        }
        return sb.toString()
    }

}