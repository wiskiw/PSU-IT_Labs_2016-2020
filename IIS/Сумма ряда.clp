(defglobal ?*i* = 1)
(defglobal ?*e* = (** 10 -6))
(defglobal ?*S* = 0)
(defglobal ?*a* = 0)
(defglobal ?*x* = 0)

(defrule takex
	(declare (salience 10000))
	=>
	(printout t "Input x: ")
	(bind ?*x* (read))
	(assert (continue))
)

(defrule calculate
	?c <-(continue)
	=>
	(bind ?*a* (/ (+ (* (** ?*x* (+ ?*i* 1)) (+ ?*i* 1)) 1) (** (+ ?*i* 1) 2)))
	(if (= (mod ?*i* 2) 1)
		then
			(bind ?*S* (+ ?*S* ?*a*))
		else
			(bind ?*S* (- ?*S* ?*a*))
	)
	(if (< ?*a* ?*e*)
		then
			(assert (stop))
		else
			(retract ?c)
			(assert (continue))
			(bind ?*i* (+ ?*i* 1))
	)
	(printout t "a(" ?*i* ")= " ?*a* crlf "S = " ?*S* crlf)
	;(readline)
)

(defrule end
	(stop)
	=>
	(printout t "S = " ?*S* crlf)
)