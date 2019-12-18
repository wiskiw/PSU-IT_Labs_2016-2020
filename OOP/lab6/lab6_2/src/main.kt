fun main(args: Array<String>) {

    val javaRepairCompany = JavaRepairCompany.getInstance()
    javaRepairCompany.changeTel("+229 (30) 55 30 64")
    javaRepairCompany.startWork()


    KotlinRepairCompany.startWork()
    KotlinRepairCompany.changeTel("+229 (30) 55 30 64")
    KotlinRepairCompany.startWork()

}