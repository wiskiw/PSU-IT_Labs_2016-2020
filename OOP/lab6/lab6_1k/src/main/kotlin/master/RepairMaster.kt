package master

import Brokenable

interface RepairMaster {

    suspend fun repair(brokenable: Brokenable): Boolean

}