package compamy

import Brokenable
import kotlinx.coroutines.GlobalScope
import kotlinx.coroutines.Job
import kotlinx.coroutines.delay
import kotlinx.coroutines.launch
import master.RepairMaster
import java.util.*

abstract class RepairCompany {

    private val stuffToRepair = LinkedList<Brokenable>()
    private var onRepairListener: OnRepairListener? = null
    private var isWorking = false

    private lateinit var master: RepairMaster
    private var thread: Thread? = null

    private var coroutine: Job? = null

    fun addToRepair(toRepair: Brokenable) {
        stuffToRepair.add(toRepair)
    }

    fun startWork() {
        println("Company start working...")
        master = callRepairMaster()
        isWorking = true
        onWorkStateChanged()
    }

    fun stopWork() {
        println("Company stop working...")
        isWorking = false
        coroutine?.cancel()
        thread?.interrupt()
        onWorkStateChanged()
    }

    private fun onWorkStateChanged() {
        coroutine = GlobalScope.launch {
            while (isWorking) {
                delay(250)

                // если есть штуки для ремонта
                if (stuffToRepair.isNotEmpty()) {

                    // доставем первую из очереди
                    val toRepair = stuffToRepair.first
                    stuffToRepair.removeFirst()

                    // отправляем к матеру на ремонт
                    if (master.repair(toRepair)) {
                        // если ремонт успешен
                        onRepairListener?.onSuccess(toRepair)
                    } else {
                        // не удалось отремонтировать
                        onRepairListener?.onFailed(toRepair)
                    }
                }
            }
        }
    }

    abstract fun callRepairMaster(): RepairMaster

    interface OnRepairListener {
        fun onSuccess(brokenable: Brokenable)
        fun onFailed(brokenable: Brokenable)
    }

}