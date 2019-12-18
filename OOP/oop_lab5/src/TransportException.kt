class TransportException(message: String) : Throwable(message) {

    var transport: Transport? = null

    constructor(message: String, transport: Transport) : this(message) {
        this.transport = transport
    }

    override fun toString(): String {
        return "TransportException: $message ${if (transport != null)
            "transport=" + transport else ""}"
    }
}

