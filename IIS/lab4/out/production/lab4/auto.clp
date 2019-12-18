(defglobal ?*target* = gui)

;;; ***************************
;;; * DEFTEMPLATES & DEFFACTS *
;;; ***************************

(deftemplate MAIN::text-for-id
   (slot id)
   (slot text))

(deftemplate UI-state
   (slot id (default-dynamic (gensym*)))
   (slot display)
   (slot relation-asserted (default none))
   (slot response (default none))
   (multislot valid-answers)
   (multislot display-answers)
   (slot state (default middle)))
   
;;;***************************
;;;* DEFFUNCTION DEFINITIONS *
;;;***************************

(deffunction MAIN::find-text-for-id (?id)
   ;; Search for the text-for-id fact
   ;; with the same id as ?id
   (bind ?fact
      (find-fact ((?f text-for-id))
                  (eq ?f:id ?id)))
   (if ?fact
      then
        (fact-slot-value (nth$ 1 ?fact) text)
      else
        ?id))


;;; GUI target

(defmethod handle-state ((?state SYMBOL (eq ?state greeting))
                         (?target SYMBOL (eq ?target gui))
                         (?message LEXEME)
                         (?relation-asserted SYMBOL)
                         (?valid-answers MULTIFIELD))
   (assert (UI-state (display ?message)
                     (relation-asserted greeting)
                     (state ?state)
                     (valid-answers yes)
                     (display-answers yes)))
   (halt))

(defmethod handle-state ((?state SYMBOL (eq ?state interview))
                         (?target SYMBOL (eq ?target gui))
                         (?message LEXEME)
                         (?relation-asserted SYMBOL)
                         (?response PRIMITIVE)
                         (?valid-answers MULTIFIELD)
                         (?display-answers MULTIFIELD))
   (assert (UI-state (display ?message)
                     (relation-asserted ?relation-asserted)
                     (state ?state)
                     (response ?response)
                     (valid-answers ?valid-answers)
                     (display-answers ?display-answers)))
   (halt))

(defmethod handle-state ((?state SYMBOL (eq ?state conclusion))
                         (?target SYMBOL (eq ?target gui))
                         (?display LEXEME))
   (assert (UI-state (display ?display)
                     (state ?state)
                     (valid-answers)
                     (display-answers)))
   (assert (conclusion))
   (halt))

;;;****************
;;;* STARTUP RULE *
;;;****************

(defrule system-banner ""
  (not (greeting yes))
  =>
  (handle-state greeting
                ?*target*
                (find-text-for-id WelcomeMessage)
                greeting
                (create$)))
  
;;;***************
;;;* QUERY RULES *
;;;***************

(defrule determine-drama ""

   (greeting yes)
   (not (drama ?))
   
   =>

   (bind ?answers (create$ no yes))
   (handle-state interview
                 ?*target*
                 (find-text-for-id StartQuestion)
                 drama
                 (nth$ 1 ?answers)
                 ?answers
                 ?answers))

;-----------------------

(defrule determine-usa-country ""

   (drama yes)
   (not (usa-country ?))
   (not (conclusion))
   
   =>

   (bind ?answers (create$ no yes))
   (handle-state interview
                 ?*target*
                 (find-text-for-id FromUSAQuestion)
                 usa-country
                 (nth$ 1 ?answers)
                 ?answers
                 ?answers))
   
(defrule determine-duration-60 ""

   (usa-country yes)
   (not (duration-60 ?))
   (not (conclusion))
   
   =>

   (bind ?answers (create$ no yes))
   (handle-state interview
                 ?*target*
                 (find-text-for-id More60MinQuestion)
                 duration-60
                 (nth$ 1 ?answers)
                 ?answers
                 ?answers))
   
(defrule determine-created-by-darabont ""

   (duration-60 yes)
   (not (created-by-darabont ?))
   (not (conclusion))
   
   =>

   (bind ?answers (create$ no yes))
   (handle-state interview
                 ?*target*
                 (find-text-for-id CreatedDarabontQuestion)
                 created-by-darabont
                 (nth$ 1 ?answers)
                 ?answers
                 ?answers))

;-------------------

(defrule determine-historical-drama ""

   (usa-country no)
   (not (historical-drama ?))
   (not (conclusion))
   
   =>

   (bind ?answers (create$ no yes))
   (handle-state interview
                 ?*target*
                 (find-text-for-id HistoricalDramaQuestion)
                 historical-drama
                 (nth$ 1 ?answers)
                 ?answers
                 ?answers))

(defrule determine-italy-country ""

   (historical-drama yes)
   (not (italy-country ?))
   (not (conclusion))
   
   =>

   (bind ?answers (create$ no yes))
   (handle-state interview
                 ?*target*
                 (find-text-for-id FromItalyQuestion)
                 italy-country
                 (nth$ 1 ?answers)
                 ?answers
                 ?answers))

;-------------------

(defrule determine-created-by-benioff ""

   (drama no)
   (not (created-by-benioff ?))
   (not (conclusion))
   
   =>

   (bind ?answers (create$ no yes))
   (handle-state interview
                 ?*target*
                 (find-text-for-id CreatedBenioffQuestion)
                 created-by-benioff
                 (nth$ 1 ?answers)
                 ?answers
                 ?answers))
				 
(defrule determine-horror ""

   (created-by-benioff no)
   (not (horror ?))
   (not (conclusion))
   
   =>

   (bind ?answers (create$ no yes))
   (handle-state interview
                 ?*target*
                 (find-text-for-id horrorQuestion)
                 horror
                 (nth$ 1 ?answers)
                 ?answers
                 ?answers))

;-------------------

(defrule determine-has-8-seasons ""

   (duration-60 no)
   (not (has-8-seasons ?))
   (not (conclusion))
   
   =>

   (bind ?answers (create$ no yes))
   (handle-state interview
                 ?*target*
                 (find-text-for-id has8SeasonsQuestion)
                 has-8-seasons
                 (nth$ 1 ?answers)
                 ?answers
                 ?answers))

(defrule determine-after-2010 ""

   (has-8-seasons yes)
   (not (after-2010 ?))
   (not (conclusion))
   
   =>

   (bind ?answers (create$ no yes))
   (handle-state interview
                 ?*target*
                 (find-text-for-id after2010Question)
                 after-2010
                 (nth$ 1 ?answers)
                 ?answers
                 ?answers))

(defrule determine-created-by-gilligan ""

   (has-8-seasons no)
   (not (created-by-gilligan ?))
   (not (conclusion))
   
   =>

   (bind ?answers (create$ no yes))
   (handle-state interview
                 ?*target*
                 (find-text-for-id CreatedGilliganQuestion)
                 created-by-gilligan
                 (nth$ 1 ?answers)
                 ?answers
                 ?answers))

(defrule determine-ended ""

   (created-by-gilligan yes)
   (not (ended ?))
   (not (conclusion))
   
   =>

   (bind ?answers (create$ no yes))
   (handle-state interview
                 ?*target*
                 (find-text-for-id endedQuestion)
                 ended
                 (nth$ 1 ?answers)
                 ?answers
                 ?answers))

;;;****************
;;;* REPAIR RULES *
;;;****************
 
 ;------

(defrule created-by-darabont-yes-conclusions ""
   (declare (salience 10))
   (or 
		(created-by-darabont yes)
		(horror yes))
   
   =>
   (bind ?answers (create$ restart))
   (handle-state conclusion
                 ?*target*
                 (find-text-for-id WalkingDeadRepair)
                 restart-end
                 (nth$ 1 ?answers)
                 ?answers
                 ?answers)
   ;;(handle-state interview ?*target* (find-text-for-id WalkingDeadRepair))
   
)
 
(defrule created-by-darabont-no-conclusions ""
   (declare (salience 10))
   (created-by-darabont no)
   =>
   (handle-state conclusion ?*target* (find-text-for-id WestworldRepair)))
  
(defrule from-italy-yes-conclusions ""
   (declare (salience 10))
   (italy-country yes)
   =>
   (handle-state conclusion ?*target* (find-text-for-id MediciRepair)))
   
(defrule from-italy-no-conclusions ""
   (declare (salience 10))
   (italy-country no)
   =>
   (handle-state conclusion ?*target* (find-text-for-id VikingsRepair)))
    
(defrule created-by-benioff-conclusions ""
   (declare (salience 10))
   (created-by-benioff yes)
   =>
   (handle-state conclusion ?*target* (find-text-for-id GOTRepair)))
     
(defrule after-2010-yes-conclusions ""
   (declare (salience 10))
   (after-2010 yes)
   =>
   (handle-state conclusion ?*target* (find-text-for-id HouseOfCardsRepair)))
     
(defrule after-2010-no-conclusions ""
   (declare (salience 10))
   (after-2010 no)
   =>
   (handle-state conclusion ?*target* (find-text-for-id HouseMDRepair)))
      
(defrule ended-yes-conclusions ""
   (declare (salience 10))
   (ended yes)
   =>
   (handle-state conclusion ?*target* (find-text-for-id BreakingBadRepair)))
       
(defrule ended-no-conclusions ""
   (declare (salience 10))
   (ended no)
   =>
   (handle-state conclusion ?*target* (find-text-for-id BatterCallSoulRepair)))
        
(defrule created-by-gilligan-conclusions ""
   (declare (salience 10))
   (created-by-gilligan no)
   =>
   (handle-state conclusion ?*target* (find-text-for-id MrRobotRepair)))
 
(defrule ended-no-conclusions ""
   (declare (salience 10))
   (or
		(historical-drama no)
		(horror no))
   =>
   (handle-state conclusion ?*target* (find-text-for-id FuckingWorldRepair)))
 
 ;------
                     
(defrule no-repairs ""
   (declare (salience -10))
   (not (conclusion))
   =>
   (handle-state conclusion ?*target* (find-text-for-id NoRepair)))

(defrule restart-conclusions ""
   (declare (salience 10))
   (restart-end restart)
   =>
    (reset)
    (run)
 ;; (handle-state greeting
 ;;              ?*target*
 ;;              (find-text-for-id WelcomeMessage)
 ;;              greeting
 ;;              (create$))
    )
