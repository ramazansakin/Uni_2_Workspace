/**
 * Interpreter class for GITL language.
 *
 * @author Orhan Aksoy
 */

import java.util.*;

public class GITLInterpreter {
  /** The list of expression objects stored during expression registratino */
  private GITLExpressions.GITLExpressionBase [] expressions;
  /** The interpreter state */
  public enum RunState { RUN_JUMP, RUN_NORMAL };
  /**
   * Creates the expression objects.
   */
  public GITLInterpreter() {
      createExpressions();
  }

    /**
     * Interprets a program within a context.
     * @param ctx The context in which the program will run
     * @param program The list of strings of program lines.
     */
    public void interpret(GITLContext ctx, LinkedList<String> program)  {

        try {
            // Set the program counter to the first line.
            ctx.currentLine = 0;
            // Call 'main'
            ctx.callFunction("main", 0, "");

            while (ctx.currentLine < program.size()) {
                // Interpret the program line string at the currentline location.
                interpretLine(program.get(ctx.currentLine), ctx);
                // If the exit status was set during interpretation, exit.
                if (ctx.exitStatus) {
//                    System.out.println("Program returned with value " + ctx.returnValue);
                    return;
                }
                // Proceed to the next line in the program.
                ++ctx.currentLine;
            }

            // There's no more program lines. We're exiting.

            // If  we're in JUMP state then we ran out of program lines
            // while looking for a label or function .
            if (ctx.getRunState() == RunState.RUN_JUMP) {
                String errorString;
                if ( ctx.getJumpLabel().equals("")) {
                    errorString = new String("Function not found: " + ctx.getJumpFunction());
                } else {
                    errorString = new String("Label not found: " + ctx.getJumpLabel());
                }
                throw new GITLException(errorString);
            }

            // THe activation stack should be empty at the moment. Otherwise,
            // this means that we ran out of program lines before an 'end' statement.
            if (!ctx.getActiveFunction().isEmpty()) {
                throw new GITLException("Function " + ctx.getActiveFunction() + " not terminated");
            }
        } catch (GITLException e) {
            System.out.println("Error at line " + (ctx.currentLine + 1) + " : " + e.getMessage());
        }




     }

    /**
     * Interprets a single code line within a context
     * @param line The code line
     * @param ctx The context in which the line will run
     */
    private void interpretLine(String line, GITLContext ctx) throws GITLException {
//        System.out.println("<< Interpreting line " + (ctx.currentLine + 1));
        // The code lines will be split using space character (' ').
        StringTokenizer tok = new StringTokenizer(line, " ");

        // Check if it is an empty line
        if ( tok.countTokens() == 0 ) {
            return;
        }

        LinkedList<String> tokens = new LinkedList<String>();

        // Put all of the tokens in a linked list
        while (tok.hasMoreTokens()) {
            tokens.add(tok.nextToken());
        }

        // Check for every possible expression for a match with the current
        // line.
        for (GITLExpressions.GITLExpressionBase exp : expressions) {
            if (exp.checkMatch(tokens)) {
                // Set the call parameters in the current context.
                ctx.setParams(tokens);

                // Check if we're in normal run mode, or we're looking\
                // for a label now.

                if ( ctx.getRunState() == RunState.RUN_JUMP) {
                    exp.handleJump(ctx);
                    return;
                }

                // Interpret.
                exp.evaluate(ctx);
                return;
            }
        }

     // We could not match.
       throw new GITLException("Invalid statement");
   }


    /**
     * Creates the expression objects that the language interprets.
     */
    private void createExpressions() {

        expressions = new GITLExpressions.GITLExpressionBase[9];

        expressions[0] = new GITLExpressions.GITLComment(this);
        expressions[1] = new GITLExpressions.GITLVariable(this);
        expressions[2] = new GITLExpressions.GITLAssignment(this);
        expressions[3] = new GITLExpressions.GITLCall(this);
        expressions[4] = new GITLExpressions.GITLConditional(this);
        expressions[5] = new GITLExpressions.GITLLabel(this);
        expressions[6] = new GITLExpressions.GITLReturn(this);
        expressions[7] = new GITLExpressions.GITLFunctionDefinition(this);
        expressions[8] = new GITLExpressions.GITLFunctionTerm(this);
    }



}
