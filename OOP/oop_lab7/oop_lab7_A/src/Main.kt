import java.io.File

/*
    VAR 11
    Разделить текст файла на предложения, и для каждого предложения вывести длину
    и используемые в нем знаки пунктуации.
 */

const val FILENAME = "./content.txt"






val PUNCTUATION_LIST = listOf('.', ',', '!', '?', '-', ':', ';', '—')

fun main(args: Array<String>) {
    val content = readContent(FILENAME)
    val sentences = divideBySentence(content)

    sentences.forEachIndexed { index, s ->
        println(" ${index + 1}: '$s'")
        sentencePunctuation(s).forEach { char, count ->
            println("\t\t [$char]: $count")
        }
        println()
    }
}


fun sentencePunctuation(sentence: String): Map<Char, Int> {
    val resultMap = mutableMapOf<Char, Int>()
    PUNCTUATION_LIST.forEach { char ->
        sentence.count { it == char }.apply {
            if (this > 0) {
                // возвращать только не-нулевые значения
                resultMap[char] = this
            }
        }
    }
    return resultMap
}


fun divideBySentence(content: String) =
        content.split("(?<=[.?!])\\s+(?=[0-9\\wА-ЯЁ])".toRegex())


fun readContent(fileName: String) =
        File(fileName).inputStream().readBytes().toString(Charsets.UTF_8)