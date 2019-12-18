import org.junit.Assert.*
import org.junit.Test

class MyListTest {

    @Test
    fun addSizeTest() {
        val mList = MyList()
        mList.add('A')
        mList.add('B')
        mList.add('C')
        assertEquals(3, mList.size())
    }

    @Test
    fun getTest() {
        val mList = MyList()
        mList.add('A')
        mList.add('B')
        mList.add('C')
        assertEquals('A', mList[0])
        assertEquals('B', mList[1])
        assertEquals('C', mList[2])
    }

    @Test
    fun concatTest() {
        val mListA = MyList()
        mListA.add('a')
        mListA.add('b')
        mListA.add('c')

        val mListB = MyList()
        mListB.add('A')
        mListB.add('B')
        mListB.add('C')


        val resultList = mListA + mListB
        assertEquals(3, mListA.size())
        assertEquals(3, mListB.size())
        assertEquals(6, resultList.size())

        assertEquals('a', resultList[0])
        assertEquals('c', resultList[2])
        assertEquals('A', resultList[3])
        assertEquals('C', resultList[5])
    }

    @Test
    fun equalsTest() {
        val mListA = MyList()
        mListA.add('A')
        mListA.add('B')
        mListA.add('C')

        val mListB = MyList()
        mListB.add('A')
        mListB.add('B')
        mListB.add('C')

        assertTrue(mListA == mListB)
        assertFalse(mListA != mListB)
    }


}