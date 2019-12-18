object KotlinRepairCompany {

    private const val name = "KotlinRepairCompany"
    private var address = "Belarus, Minsk"
    private var tel = ""

    fun startWork() {
        println(getName() + " start working in " + getAddress())
    }

    fun getName(): String {
        return name
    }

    fun getAddress(): String {
        return address
    }

    fun getTel(): String {
        return tel
    }

    fun changeTel(tel: String) {
        this.tel = tel
    }

    fun changeAddress(address: String) {
        this.address = address
    }

}