(defglobal ?*i* = 1)
(defglobal ?*e* = (** 10 -6))
(defglobal ?*S* = 0)
(defglobal ?*a* = 1)
(defglobal ?*x* = 0)

(defglobal ?*power* = 0)
(defglobal ?*sign* = 0)

(defrule takex
	(declare (salience 10000))
	=>
	(printout t "Input x: ")
	(bind ?*x* (read))
	(assert (continue))
)

(defrule calculate
	(continue)
	=>
	(while (> (abs ?*a*) ?*e*)

		(bind ?*sign* (** -1 (+ ?*i* 1)))

		; степень Х
		(bind ?*power* (- (* 2 ?*i*) 1)

		(bind ?*a* (* ?*sign* (/ (- (** ?*x* ?*power*) 1) (+ (* 2 ?*i*) 1))))

		(bind ?*S* (+ ?*S* ?*a*))
		(printout t "a(" ?*i* ")= " ?*a* crlf "S = " ?*S* crlf)
		(bind ?*i* (+ ?*i* 1))
	)
)



(defrule calculate
	?f <- (continue)
	=>
		(bind ?*sign* (** -1 (+ ?*i* 1)))

		; степень Х
		(bind ?*power* (- (* 2 ?*i*) 1)

		(bind ?*a* (* ?*sign* (/ (- (** ?*x* ?*power*) 1) (+ (* 2 ?*i*) 1))))

		(bind ?*S* (+ ?*S* ?*a*))
		(bind ?*i* (+ ?*i* 1))

		(if (< (abs ?*a*) ?*e*) then
				(retract f)
				(assert (continue))
					else
				(assert (end))
		)

)

(defrule end
	(stop)
	=>
	(printout t "S = " ?*S* crlf)
)
