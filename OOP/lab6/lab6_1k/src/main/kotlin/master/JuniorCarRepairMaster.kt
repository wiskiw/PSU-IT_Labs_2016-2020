package master

import Brokenable
import kotlinx.coroutines.delay

class JuniorCarRepairMaster : RepairMaster {

    override suspend fun repair(brokenable: Brokenable): Boolean {
        delay(250)
        println("JuniorCarRepairMaster is working")
        return true
    }
}