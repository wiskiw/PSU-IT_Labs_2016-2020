(defglobal ?*x* = 0)

(defglobal ?*pi* = 3.14)
(defglobal ?*min* = -1)
(defglobal ?*max* = 1)
(defglobal ?*step* = 1)


(defglobal ?*tempSum* = 0)


(deffunction factorial (?n)
    (if (>= ?n 1)
    then (* ?n (factorial (- ?n 1)))
    else 1)
)

(defrule takex
	(declare (salience 10000))
	=>
	(printout t "Input x step: ")
	(bind ?*step* (read))
	(bind ?*x* ?*min*)
	(assert (run))
)


; Основная функция
; выполняет funYx и funSx пока x в [-1; 1] с шагом ?*step*
(deffunction run
  ?f <- (run)
	=>
	 (while (< ?*x* ?*max*)


    (if (> ?*x* ?*max*) then
      (retract (?f))
      (assert (stop))
    else
        (bind ?*x* (+ ?*x* (?*step*)))
        (retract (?f))
        (assert (funYx))
    )
	)

)


(defrule funYx
	?f <- (funYx)
	=>
	(bind ?*tempSum* (/ (* ?*pi* (sin ?*x*) 4))
	(printout t "Y(x) for X=" ?*x* " is " ?*tempSum* crlf)
	(retract ?f)
  (assert (funSx))
)


(defglobal ?*n* = 1)
(defrule funSx
	?f <- (funSx)
	=>
	(bind ?*n* 1)
	; n изменяется от 1 до 6
	(while (< ?*n* 6)
		(bind ?*tempSum* (+ ?*tempSum*   (* (** -1 ?*n*) (/ (** ?*x* (+ (* 2 ?*x*) 2)) (factorial (+ (* 2 ?*n*) 1)) ))   )
	)
	(bind ?*tempSum* (* (/ ?*pi* 4) ?*tempSum*) )
	(printout t "S(x) for X=" ?*x* " is " ?*tempSum* crlf)
	(retract ?f)
  (assert (run))
)

(defrule end
	(stop)
	=>
	(printout t "S = " ?*S* crlf)
)
