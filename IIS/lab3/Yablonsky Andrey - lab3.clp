
; математическая функция
(defglobal ?*res* = 0)
(deffunction mathFunc ( ?a ?b )
	(bind ?*res* (+ 22 (** ?b 2) (- ?a 10)))
	(printRes ?*res*)
)


; функция с использованием while 
(defglobal ?*sum* = 0)
(defglobal ?*i* = 1)
(deffunction whileFunc ()
	( while (<= ?*i* 30)
		(bind ?*i* (+ ?*i* 1)) 
		(bind ?*sum* (+ ?*sum* ?*i*))
		(printout t "iteration: " ?*i* " sum: " ?*sum* crlf)
	)
)


; родовая функция fatherFunc
(defgeneric fatherFunc)

(defglobal ?*statusMsg* = "")
(defmethod fatherFunc((?status INTEGER))
	(if (eq ?status 0)
		then (bind ?*statusMsg* "Status OK!")
		else (if (eq ?status 1)
				then (bind ?*statusMsg* "Status ERROR: RuntimeError!")
				else (bind ?*statusMsg* "Status ERROR: Unknown error!")
			)
	)
	
	(printout t ?*statusMsg* crlf)
)

(defmethod fatherFunc((?name STRING))
		(printout t "Hello " ?name "!" crlf)
)

(defmethod fatherFunc((?name STRING) (?age INTEGER) )
	(if (>= ?age 18)
		then (printout t "Hello " ?name "! You are old enouth." crlf)
		else (printout t "Hello " ?name "! Sorry but you are too young." crlf)
	)
)

(defmethod fatherFunc ((?nick SYMBOL) (?message STRING))
	(printout t "New message from" ?nick ": " ?message crlf)
)



(defmethod fatherFunc ((?a INTEGER) (?b INTEGER))
	(bind ?*res* (** ?a ?b))
	(printRes ?*res*)
)


(deffunction printRes(?res) 
	(printout t "Result: " ?res crlf)
)
