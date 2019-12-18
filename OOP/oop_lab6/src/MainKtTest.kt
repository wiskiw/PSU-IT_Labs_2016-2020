import org.junit.Test
import kotlin.test.assertEquals
import kotlin.test.assertTrue

class MainKtTest {

    @Test
    fun averageItemLength() {
        val arrLen3 = arrayListOf("123", "asd", "asd", "asd", "asd")
        assertEquals(3.0, averageItemLength(arrLen3.iterator()))

        val arrEmpty = arrayListOf<String>()
        assertEquals(0.0, averageItemLength(arrEmpty.iterator()))

        val arrLenAbout3 = arrayListOf<String>("123", "asd", "asd", "asd", "asd", "1234")
        val av = averageItemLength(arrLenAbout3.iterator())
        assertTrue(av > 3.0)
        assertTrue(av < 3.4)
    }

    @Test
    fun actionTest1() {
        val arr1 = arrayListOf("___", "___", "22", "___", "___", "___", "___")
        action(arr1)

        println(arr1.joinToString())

        assertEquals(8, arr1.size)
        assertEquals(arr1[2], arr1[3])
        assertEquals(arr1[2], "22")
    }

    @Test
    fun actionTest2() {
        val arr1 = arrayListOf("___", "___", "1", "___", "1", "___", "___")
        action(arr1)

        println(arr1.joinToString())

        assertEquals(9, arr1.size)
        assertEquals(arr1[2], arr1[3])
        assertEquals(arr1[5], arr1[6])
        assertEquals(arr1[2], "1")
        assertEquals(arr1[5], "1")
    }
}
