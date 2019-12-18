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

(defrule determine-sd-support ""

   (greeting yes)
   (not (sd-support ?))
   
   =>

   (bind ?answers (create$ no yes))
   (handle-state interview
                 ?*target*
                 (find-text-for-id StartQuestion)
                 sd-support
                 (nth$ 1 ?answers)
                 ?answers
                 ?answers))

;-----------------------

(defrule determine-os-android ""

   (sd-support no)
   (not (os-android ?))
   (not (conclusion))
   
   =>

   (bind ?answers (create$ no yes))
   (handle-state interview
                 ?*target*
                 (find-text-for-id IsOsAndroidQuestion)
                 os-android
                 (nth$ 1 ?answers)
                 ?answers
                 ?answers))
   
(defrule determine-jobs-alive ""

   (os-android no)
   (not (jobs-alive ?))
   (not (conclusion))
   
   =>

   (bind ?answers (create$ no yes))
   (handle-state interview
                 ?*target*
                 (find-text-for-id IsJobsAlive)
                 jobs-alive
                 (nth$ 1 ?answers)
                 ?answers
                 ?answers))
   
(defrule determine-after-2010 ""

   (os-android yes)
   (not (after-2010 ?))
   (not (conclusion))
   
   =>

   (bind ?answers (create$ no yes))
   (handle-state interview
                 ?*target*
                 (find-text-for-id After2010Question)
                 after-2010
                 (nth$ 1 ?answers)
                 ?answers
                 ?answers))

;-------------------

(defrule determine-samsung-developer ""

   (after-2010 no)
   (not (samsung-developer ?))
   (not (conclusion))
   
   =>

   (bind ?answers (create$ no yes))
   (handle-state interview
                 ?*target*
                 (find-text-for-id SamsungDevQuestion)
                 samsung-developer
                 (nth$ 1 ?answers)
                 ?answers
                 ?answers))

(defrule determine-ram-greater2 ""

   (sd-support yes)
   (not (ramGreater2 ?))
   (not (conclusion))
   
   =>

   (bind ?answers (create$ no yes))
   (handle-state interview
                 ?*target*
                 (find-text-for-id RamBigger2Question)
                 ramGreater2
                 (nth$ 1 ?answers)
                 ?answers
                 ?answers))

;-------------------
 

;-------------------


;;;****************
;;;* REPAIR RULES *
;;;****************
 
 ;------
 
(defrule iphone-x-no-conclusions ""
   (declare (salience 10))
   (jobs-alive yes)
   =>
   (handle-state conclusion ?*target* (find-text-for-id IPhoneXRepair)))
  
(defrule jobs-alive-no-conclusions ""
   (declare (salience 10))
   (jobs-alive no)
   =>
   (handle-state conclusion ?*target* (find-text-for-id IPhone4Repair)))
   
(defrule samsung-dev-yes-conclusions ""
   (declare (salience 10))
   (samsung-developer yes)
   =>
   (handle-state conclusion ?*target* (find-text-for-id GalaxyNexusRepair)))
    
(defrule samsung-dev-no-conclusions ""
   (declare (salience 10))
   (samsung-developer no)
   =>
   (handle-state conclusion ?*target* (find-text-for-id Nexus5Repair)))

(defrule after-2010-conclusions ""
   (declare (salience 10))
   (after-2010 yes)
   =>
   (handle-state conclusion ?*target* (find-text-for-id GooglePixelRepair)))
     
(defrule ram-greater-2-yes-conclusions ""
   (declare (salience 10))
   (ramGreater2 yes)
   =>
   (handle-state conclusion ?*target* (find-text-for-id GalaxyS10Repair)))
     
(defrule ram-greater-2-no-conclusions ""
   (declare (salience 10))
   (ramGreater2 no)
   =>
   (handle-state conclusion ?*target* (find-text-for-id GalaxyS10Repair)))
 
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
