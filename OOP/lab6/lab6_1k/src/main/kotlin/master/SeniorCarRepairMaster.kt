package master

import Brokenable
import kotlinx.coroutines.delay

class SeniorCarRepairMaster : RepairMaster {


    override suspend fun repair(brokenable: Brokenable): Boolean {
        delay(250)
        println("SeniorCarRepairMaster trying to fix")
        brokenable.tryToFix()
        println("SeniorCarRepairMaster finish fixing: ${brokenable.isBroken()}")
        return brokenable.isBroken()
    }
}