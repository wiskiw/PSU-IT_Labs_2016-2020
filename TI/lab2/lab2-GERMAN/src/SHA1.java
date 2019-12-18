public class SHA1 {

    /*
     * Побитовое вращение 32-битного числа влево
     */
    private static int rol(int num, int cnt) {
        return (num << cnt) | (num >>> (32 - cnt));
    }

    /*
     * Берет строку и возвращает представление base64 своего SHA-1.
     */
    public static String encodeHex(String str) {

        // Преобразование строки в последовательность блоков из 16 слов, хранящихся в виде массива.
        // Добавляем биты заполнения и длину, как описано в стандарте SHA1

        byte[] x = str.getBytes();
        int[] blks = new int[(((x.length + 8) >> 6) + 1) * 16];
        int i;

        for (i = 0; i < x.length; i++) {
            blks[i >> 2] |= x[i] << (24 - (i % 4) * 8);
        }

        blks[i >> 2] |= 0x80 << (24 - (i % 4) * 8);
        blks[blks.length - 1] = x.length * 8;

        // вычислить 160-битный SHA1-хэш последовательности блоков

        int[] w = new int[80];

        int a = 1732584193;
        int b = -271733879;
        int c = -1732584194;
        int d = 271733878;
        int e = -1009589776;

        for (i = 0; i < blks.length; i += 16) {
            int olda = a;
            int oldb = b;
            int oldc = c;
            int oldd = d;
            int olde = e;

            for (int j = 0; j < 80; j++) {
                w[j] = (j < 16) ? blks[i + j] :
                        (rol(w[j - 3] ^ w[j - 8] ^ w[j - 14] ^ w[j - 16], 1));

                int t = rol(a, 5) + e + w[j] +
                        ((j < 20) ? 1518500249 + ((b & c) | ((~b) & d))
                                : (j < 40) ? 1859775393 + (b ^ c ^ d)
                                : (j < 60) ? -1894007588 + ((b & c) | (b & d) | (c & d))
                                : -899497514 + (b ^ c ^ d));
                e = d;
                d = c;
                c = rol(b, 30);
                b = a;
                a = t;
            }

            a = a + olda;
            b = b + oldb;
            c = c + oldc;
            d = d + oldd;
            e = e + olde;
        }

        // Преобразовать 160-битный хэш в base64


        int[] words = {a, b, c, d, e};
        StringBuilder sb = new StringBuilder();

        for (int word : words) {
            String hexWord = Integer.toHexString(word);
            while (hexWord.length() < 8) {
                hexWord = "0" + hexWord;
            }
            sb.append(hexWord);
        }
        return sb.toString();
    }
}