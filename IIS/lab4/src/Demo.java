
import net.sf.clipsrules.jni.*;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.FileNotFoundException;
import java.text.BreakIterator;
import java.util.*;

class AutoDemo implements ActionListener {
    private enum InterviewState {
        GREETING,
        INTERVIEW,
        CONCLUSION
    }


    private JLabel displayLabel;
    private JButton nextButton;
    private JButton prevButton;
    private JPanel choicesPanel;
    private ButtonGroup choicesButtons;

    private Environment clips;
    private boolean isExecuting = false;
    private Thread executionThread;

    private String lastAnswer;
    private String relationAsserted;
    private ArrayList<String> variableAsserts;
    private ArrayList<String> priorAnswers;

    private InterviewState interviewState;

    AutoDemo() {

        /*================================*/
        /* Create a new JFrame container. */
        /*================================*/

        JFrame jfrm = new JFrame("AutoDemo");

        /*=============================*/
        /* Specify FlowLayout manager. */
        /*=============================*/

        jfrm.getContentPane().setLayout(new GridLayout(3, 1));

        /*=================================*/
        /* Give the frame an initial size. */
        /*=================================*/

        jfrm.setSize(350, 200);

        /*=============================================================*/
        /* Terminate the program when the user closes the application. */
        /*=============================================================*/

        jfrm.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        /*===========================*/
        /* Create the display panel. */
        /*===========================*/

        JPanel displayPanel = new JPanel();
        displayLabel = new JLabel();
        displayPanel.add(displayLabel);

        /*===========================*/
        /* Create the choices panel. */
        /*===========================*/

        choicesPanel = new JPanel();
        choicesButtons = new ButtonGroup();

        /*===========================*/
        /* Create the buttons panel. */
        /*===========================*/

        JPanel buttonPanel = new JPanel();

        prevButton = new JButton("Prev");
        prevButton.setActionCommand("Prev");
        buttonPanel.add(prevButton);
        prevButton.addActionListener(this);

        nextButton = new JButton("Next");
        nextButton.setActionCommand("Next");
        buttonPanel.add(nextButton);
        nextButton.addActionListener(this);

        /*=====================================*/
        /* Add the panels to the content pane. */
        /*=====================================*/

        jfrm.getContentPane().add(displayPanel);
        jfrm.getContentPane().add(choicesPanel);
        jfrm.getContentPane().add(buttonPanel);

        /*===================================*/
        /* Initialize the state information. */
        /*===================================*/

        variableAsserts = new ArrayList<>();
        priorAnswers = new ArrayList<>();

        /*================================*/
        /* Load and run the auto program. */
        /*================================*/

        clips = new Environment();

        try {
            clips.loadFromResource("/auto.clp");

            try {
                clips.loadFromResource("/auto-en.clp");
            } catch (FileNotFoundException fnfe) {
                fnfe.printStackTrace();
                System.exit(1);
            }

            processRules();
        } catch (Exception e) {
            e.printStackTrace();
            System.exit(1);
            return;
        }

        /*====================*/
        /* Display the frame. */
        /*====================*/

        jfrm.setVisible(true);
    }

    /*******************/
    /* handleResponse: */

    /*******************/
    private void handleResponse() throws Exception {
        /*===========================*/
        /* Get the current UI state. */
        /*===========================*/

        FactAddressValue fv = clips.findFact("UI-state");

        /*========================================*/
        /* Determine the Next/Prev button states. */
        /*========================================*/

        if (fv.getSlotValue("state").toString().equals("conclusion")) {
            interviewState = InterviewState.CONCLUSION;
            nextButton.setActionCommand("Restart");
            nextButton.setText("Restart");
            prevButton.setVisible(true);
            choicesPanel.setVisible(false);
        } else if (fv.getSlotValue("state").toString().equals("greeting")) {
            interviewState = InterviewState.GREETING;
            nextButton.setActionCommand("Next");
            nextButton.setText("Next");
            prevButton.setVisible(false);
            choicesPanel.setVisible(false);
        } else {
            interviewState = InterviewState.INTERVIEW;
            nextButton.setActionCommand("Next");
            nextButton.setText("Next");
            prevButton.setVisible(true);
            choicesPanel.setVisible(true);
        }

        /*=====================*/
        /* Set up the choices. */
        /*=====================*/

        choicesPanel.removeAll();
        choicesButtons = new ButtonGroup();

        MultifieldValue damf = (MultifieldValue) fv.getSlotValue("display-answers");
        MultifieldValue vamf = (MultifieldValue) fv.getSlotValue("valid-answers");

        String selected = fv.getSlotValue("response").toString();
        JRadioButton firstButton = null;

        for (int i = 0; i < damf.size(); i++) {
            LexemeValue da = (LexemeValue) damf.get(i);
            LexemeValue va = (LexemeValue) vamf.get(i);
            JRadioButton rButton;
            String buttonName, buttonText, buttonAnswer;

            buttonName = da.getValue();
            buttonText = buttonName.substring(0, 1).toUpperCase() + buttonName.substring(1);
            buttonAnswer = va.getValue();

            if ((buttonAnswer.equals(lastAnswer)) ||
                    ((lastAnswer == null) && buttonAnswer.equals(selected))) {
                rButton = new JRadioButton(buttonText, true);
            } else {
                rButton = new JRadioButton(buttonText, false);
            }

            rButton.setActionCommand(buttonAnswer);
            choicesPanel.add(rButton);
            choicesButtons.add(rButton);

            if (firstButton == null) {
                firstButton = rButton;
            }
        }

        if ((choicesButtons.getSelection() == null) && (firstButton != null)) {
            choicesButtons.setSelected(firstButton.getModel(), true);
        }

        choicesPanel.repaint();

        /*====================================*/
        /* Set the label to the display text. */
        /*====================================*/

        relationAsserted = ((LexemeValue) fv.getSlotValue("relation-asserted")).getValue();

        /*====================================*/
        /* Set the label to the display text. */
        /*====================================*/

        String theText = ((StringValue) fv.getSlotValue("display")).getValue();

        wrapLabelText(displayLabel, theText);

        executionThread = null;

        isExecuting = false;
    }

    /*########################*/
    /* ActionListener Methods */
    /*########################*/

    /*******************/
    /* actionPerformed */

    /*******************/
    public void actionPerformed(
            ActionEvent ae) {
        try {
            onActionPerformed(ae);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    /***********/
    /* runAuto */

    /***********/
    private void runAuto() {
        Runnable runThread =
                () -> {
                    try {
                        clips.run();
                    } catch (CLIPSException e) {
                        e.printStackTrace();
                    }

                    SwingUtilities.invokeLater(
                            () -> {
                                try {
                                    handleResponse();
                                } catch (Exception e) {
                                    e.printStackTrace();
                                }
                            });
                };

        isExecuting = true;

        executionThread = new Thread(runThread);

        executionThread.start();
    }

    /****************/
    /* processRules */

    /****************/
    private void processRules() throws CLIPSException {
        clips.reset();

        for (String factString : variableAsserts) {
            String assertCommand = "(assert " + factString + ")";
            clips.eval(assertCommand);
        }

        runAuto();
    }

    /********************/
    /* nextButtonAction */

    /********************/
    private void nextButtonAction() throws CLIPSException {
        String theString;
        String theAnswer;

        lastAnswer = null;
        switch (interviewState) {
            /* Handle Next button. */
            case GREETING:
            case INTERVIEW:
                theAnswer = choicesButtons.getSelection().getActionCommand();
                theString = "(" + relationAsserted + " " + theAnswer + ")";
                variableAsserts.add(theString);
                priorAnswers.add(theAnswer);
                break;

            /* Handle Restart button. */
            case CONCLUSION:
                variableAsserts.clear();
                priorAnswers.clear();
                break;
        }
        processRules();

    }

    /********************/
    /* prevButtonAction */

    /********************/
    private void prevButtonAction() throws CLIPSException {
        lastAnswer = priorAnswers.get(priorAnswers.size() - 1);

        variableAsserts.remove(variableAsserts.size() - 1);
        priorAnswers.remove(priorAnswers.size() - 1);

        processRules();
    }

    /*********************/
    /* onActionPerformed */

    /*********************/
    private void onActionPerformed(
            ActionEvent ae) throws Exception {
        if (isExecuting) return;

        switch (ae.getActionCommand()) {
            case "Next":
                nextButtonAction();
                break;
            case "Restart":
                nextButtonAction();
                break;
            case "Prev":
                prevButtonAction();
                break;
        }
    }

    /*****************/
    /* wrapLabelText */

    /*****************/
    private void wrapLabelText(
            JLabel label,
            String text) {
        FontMetrics fm = label.getFontMetrics(label.getFont());
        Container container = label.getParent();
        int containerWidth = container.getWidth();
        int textWidth = SwingUtilities.computeStringWidth(fm, text);
        int desiredWidth;

        if (textWidth <= containerWidth) {
            desiredWidth = containerWidth;
        } else {
            int lines = ((textWidth + containerWidth) / containerWidth);

            desiredWidth = textWidth / lines;
        }

        BreakIterator boundary = BreakIterator.getWordInstance();
        boundary.setText(text);

        StringBuffer trial = new StringBuffer();
        StringBuilder real = new StringBuilder("<html><center>");

        int start = boundary.first();
        for (int end = boundary.next(); end != BreakIterator.DONE;
             start = end, end = boundary.next()) {
            String word = text.substring(start, end);
            trial.append(word);
            int trialWidth = SwingUtilities.computeStringWidth(fm, trial.toString());
            if (trialWidth > containerWidth) {
                trial = new StringBuffer(word);
                real.append("<br>");
                real.append(word);
            } else if (trialWidth > desiredWidth) {
                trial = new StringBuffer();
                real.append(word);
                real.append("<br>");
            } else {
                real.append(word);
            }
        }

        real.append("</html>");

        label.setText(real.toString());
    }

    public static void main(String[] args) {
        // Create the frame on the event dispatching thread.
        SwingUtilities.invokeLater(AutoDemo::new);
    }
}
