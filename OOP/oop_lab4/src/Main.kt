fun main(args: Array<String>) {

    println("Bool list: ")
    val mList = MyList<Boolean>()
    mList + true
    mList + false
    mList + false
    mList + true
    mList.printAll()


    val mList2 = MyList<Boolean>()
    mList2.add(false)
    mList2.add(true)
    val list3 = mList + mList2

    println("\nFloat list: ")
    val mListFloat = MyList<Float>()
    mListFloat + 1.2f
    mListFloat + 1.222f
    mListFloat + 222.4f
    mListFloat.printAll()

}