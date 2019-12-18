package compamy

import getWeekDateNumber
import master.JuniorCarRepairMaster
import master.RepairMaster
import master.SeniorCarRepairMaster

class CarRepairCompany : RepairCompany() {

    override fun callRepairMaster(): RepairMaster {
        return when (getWeekDateNumber()) {
            in 1..5 -> SeniorCarRepairMaster()
            in 6..7 -> JuniorCarRepairMaster()
            else -> JuniorCarRepairMaster()
        }
    }

}