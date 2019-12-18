import org.junit.Test
import kotlin.test.assertEquals
import kotlin.test.assertFalse
import kotlin.test.assertNotEquals
import kotlin.test.assertTrue

class MyListTest {

    @Test
    fun addSizeTest() {
        val mList = MyList<Char>()
        mList.add('A')
        mList.add('B')
        mList.add('C')
        assertEquals(3, mList.size())
    }

    @Test
    fun getTest() {
        val mList = MyList<Char>()
        mList.add('A')
        mList.add('B')
        mList.add('C')
        assertEquals('A', mList[0])
        assertEquals('B', mList[1])
        assertEquals('C', mList[2])
    }

    @Test
    fun equalsTest() {
        val mListA = MyList<Char>()
        mListA.add('A')
        mListA.add('B')
        mListA.add('C')

        val mListB = MyList<Char>()
        mListB.add('A')
        mListB.add('B')
        mListB.add('C')

        assertTrue(mListA == mListB)
        assertFalse(mListA != mListB)

        val mListC = MyList<Int>()
        mListC.add(1)
        mListC.add(2)
        mListC.add(3)
        assertFalse(mListA == mListC)
    }

    @Test
    fun plusElementTest() {
        val mList = MyList<Int>()
        mList.add(1)
        mList.add(2)
        mList.add(3)

        mList + 999

        assertEquals(4, mList.size())
        assertEquals(999, mList[0])
        assertEquals(1, mList[1])
        assertEquals(3, mList[3])
    }

    @Test
    fun decTest() {
        var mList = MyList<Int>()
        mList.add(1)
        mList.add(2)
        mList.add(3)

        --mList

        assertEquals(2, mList.size())

        assertEquals(2, mList[0])
        assertEquals(3, mList[1])
    }

    @Test
    fun intMyListTest() {
        val mList = MyList<Int>()
        mList.add(2)
        mList.add(3)
        mList + 1

        assertEquals(3, mList.size())
        assertEquals(1, mList[0])
        assertEquals(2, mList[1])
        assertEquals(3, mList[2])
    }

    @Test
    fun boolMyListTest() {
        val mList = MyList<Boolean>()
        mList.add(false)
        mList.add(false)
        mList + true

        assertEquals(3, mList.size())
        assertEquals(true, mList[0])
        assertEquals(false, mList[1])
        assertEquals(false, mList[2])
    }

    @Test
    fun doubleMyListTest() {
        val mList = MyList<Double>()
        mList.add(2.5)
        mList + 333.0
        mList.add(1.3)

        assertEquals(3, mList.size())
        assertEquals(333.0, mList[0])
        assertEquals(2.5, mList[1])
        assertEquals(1.3, mList[2])
    }

    @Test
    fun myClassMyListTest() {
        val mList = MyList<SomeClass>()
        mList.add(SomeClass(11))
        mList.add(SomeClass(22))
        mList + SomeClass(33)
        mList + SomeClass(44)

        assertEquals(4, mList.size())
        assertEquals(SomeClass(44), mList[0])
        assertEquals(SomeClass(33), mList[1])
        assertEquals(SomeClass(11), mList[2])
        assertEquals(SomeClass(22), mList[3])
    }

    @Test
    fun companyClassMyListTest() {
        val mList = MyList<Company>()
        mList.add(Company(11, "AAA"))
        mList.add(Company(22, "BBB"))
        mList + Company(33, "CCC")
        mList + Company(44, "DDD")

        assertEquals(4, mList.size())
        assertEquals(Company(44, "DDD"), mList[0])
        assertEquals(Company(33, "CCC"), mList[1])
        assertEquals(Company(11, "AAA"), mList[2])
        assertEquals(Company(22, "BBB"), mList[3])
    }


    @Test
    fun searchCompanyClassTest() {
        val mList = MyList<Company>()
        mList.add(Company(11, "AAA"))
        mList.add(Company(22, "BBB"))

        // метод search вернет индекс такого элемента в списке

        // тесто проверяет, что объект Company(11, "AAA") находится по индексу 0
        assertEquals(0, mList.search(Company(11, "AAA")))
    }

    @Test
    fun intSearchTest() {
        val mList = MyList<Int>()
        mList.add(111)
        mList.add(222)
        mList.add(333)

        assertEquals(1, mList.search(222))
        assertEquals(2, mList.search(333))
    }

    @Test // * − пересечение множеств;
    fun timesTest() {
        val listA = MyList<Int>()
        listA.add(111)
        listA.add(222)
        listA.add(333)
        listA.add(444)
        listA.add(555)

        val listB = MyList<Int>()
        listB.add(444)
        listB.add(222)

        val rList = listA * listB
        assertEquals(2, rList.size())
        assertNotEquals(-1, rList.search(444))
        assertNotEquals(-1, rList.search(222))
    }

    @Test // > − проверка на принадлежность
    fun greaterThanItemTest() {
        val listA = MyList<Int>()
        listA.add(111)
        listA.add(222)
        listA.add(333)
        listA.add(444)
        listA.add(555)

        assertEquals(true, listA > 111)
        assertEquals(true, listA > 333)
        assertEquals(false, listA > 1)
        assertEquals(false, listA > 999)
    }

    @Test // < − проверка на подмножество.
    fun lowerThanListTest() {
        val listA = MyList<Int>()
        listA.add(111)
        listA.add(222)
        listA.add(333)
        listA.add(444)
        listA.add(555)

        val listB = MyList<Int>()
        listB.add(222)
        listB.add(444)

        assertEquals(true, listA < listB)
        assertEquals(false, listB < listA)
        assertEquals(false, listA < MyList())
    }

    @Test
    fun queueTest(){
        val listA = MyList<Int>()
        listA.add(111)
        listA.add(222)
        listA.add(333)
        listA.add(444)
        listA.add(555)

        val listB = MyList<Int>()
        listB.add(222)
        listB.add(444)


        listA + listB
        assertEquals(7, listA.size())
        assertEquals(111, listA[0])
        assertEquals(444, listA[6])

    }

}