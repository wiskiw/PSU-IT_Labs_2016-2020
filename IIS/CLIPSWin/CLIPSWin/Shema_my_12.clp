;;;======================================================
;;;
;;; LEGEND
;;; ------------
;;; S = Source
;;; P = Splitter
;;; A = AND Gate
;;; N = NOT Gate
;;; O = OR Gate
;;; X = XOR Gate
;;; L = LED
;;;
;;;               +--------------------+
;;;	          |		       A1--------+	
;;;		  | 		       |         |		   		
;;;	s1>------p1  		       |         A3----------------+
;;;		  |  		       |         | 		   |
;;;		  |  		       |         | 		   |		
;;;		  +--------------------)---------)------+	   |		
;;;	                               |         |      |          X1-----L1 
;;;	          +--------------------+         |      |          |
;;;	s2>------p2                              |      |          |
;;;		  +------------------------------)-----O1----+	   |	
;;;	                                         |           03----+
;;;	          +------N1----------------------)-----02----+
;;;	s3>------p3	                         |      |
;;;		  +--------------------+         |      |
;;;			               A2--------+      |
;;;     s4>----------------------------+                |
;;;						        |
;;;	s5>--------------N2-----------------------------+
;;;
;;;
;;;======================================================

(definstances circuit
  (S-1 of SOURCE)
  (S-2 of SOURCE)
  (S-3 of SOURCE)
  (S-4 of SOURCE)
  (S-5 of SOURCE)
  (P-1 of SPLITTER)
  (P-2 of SPLITTER)
  (P-3 of SPLITTER)
  (A-1 of AND-GATE)
  (A-2 of AND-GATE)
  (A-3 of AND-GATE)
  (N-1 of NOT-GATE)
  (N-2 of NOT-GATE)
  (X-1 of XOR-GATE)
  (O-1 of OR-GATE)
  (O-2 of OR-GATE)
  (O-3 of OR-GATE)
  (L-1 of LED))

(deffunction connect-circuit ()
  (connect [S-1] [P-1])
  (connect [S-2] [P-2])
  (connect [S-3] [P-3])
  (connect [S-4] [A-2] 2)
  (connect [S-5] [N-2])
  (connect [P-1] 1 [A-1] 1)
  (connect [P-1] 2 [O-1] 1)
  (connect [P-2] 1 [A-1] 2)
  (connect [P-2] 2 [O-1] 2)
  (connect [P-3] 1 [N-1])
  (connect [P-3] 2 [A-2] 1)
  (connect [N-1] [O-2] 1)
  (connect [N-2] [O-2] 2)
  (connect [A-1] [A-3] 1)
  (connect [A-2] [A-3] 2)  
  (connect [O-1] [O-3] 1)
  (connect [O-2] [O-3] 2)
  (connect [A-3] [X-1] 1)
  (connect [O-3] [X-1] 2)
  (connect [X-1] [L-1]))