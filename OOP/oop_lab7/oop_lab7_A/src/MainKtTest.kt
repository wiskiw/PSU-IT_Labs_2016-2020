import org.junit.Test
import kotlin.test.assertEquals
import kotlin.test.assertTrue

class MainKtTest {

    @Test
    fun divideBySentenceTestEngSimple() {
        val content1 = "The Box III cements Hooli’s legacy of innovation. " +
                "And my signature — that’s a promise from me to the Hooli user."
        val sents = divideBySentence(content1)

        assertEquals(2, sents.size)

        assertTrue(sents.first().startsWith("The Box III "))
        assertTrue(sents.first().endsWith("of innovation."))

        assertTrue(sents[1].startsWith("And my si"))
        assertTrue(sents[1].endsWith("Hooli user."))
    }

    @Test
    fun divideBySentenceTestRusNumber() {
        val content = "Есть много вариантов Lorem Ipsum. Но большинство " +
                "из них имеет не всегда! 12т приемлемые модификации?"
        val sents = divideBySentence(content)

        assertEquals(3, sents.size)

        assertTrue(sents[0].startsWith("Есть "))
        assertTrue(sents[0].endsWith("Lorem Ipsum."))

        assertTrue(sents[1].startsWith("Но большинс"))
        assertTrue(sents[1].endsWith("не всегда!"))

        assertTrue(sents[2].startsWith("12т приемле"))
        assertTrue(sents[2].endsWith("фикации?"))
    }

    @Test
    fun divideBySentenceTestDiffPunctuation() {
        val content = "Но большинство...    Из них имеет не всегда!?     12т" +
                " приемлемые модификации?"
        val sents = divideBySentence(content)

        assertEquals(3, sents.size)

        assertTrue(sents[0] == "Но большинство...")

        assertTrue(sents[1].startsWith("Из них "))
        assertTrue(sents[1].endsWith("не всегда!?"))

        assertTrue(sents[2].startsWith("12т приемлемые "))
        assertTrue(sents[2].endsWith("модификации?"))
    }

    @Test
    fun sentencePunctuationTest() {
        val content1 = "And, my signature — that’s a promise, " +
                "from; me; to the: Hooli user!"
        val r1 = sentencePunctuation(content1)
        assertEquals(5, r1.size)
        assertTrue(r1.containsKey(','))
        assertTrue(r1.containsKey(';'))
        assertTrue(r1.containsKey(':'))
        assertTrue(r1.containsKey('!'))
        assertTrue(r1.containsKey('—'))


        assertEquals(2, r1[','])
        assertEquals(2, r1[';'])
        assertEquals(1, r1[':'])
        assertEquals(1, r1['!'])
        assertEquals(1, r1['—'])
    }
}