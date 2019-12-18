interface Brokenable {

    fun isBroken(): Boolean

    suspend fun tryToFix()

}