/**
 * GITLContext class represents the context in which the expressions are
 * evaluated. Contains global variables, function call parameters, etc.
 *
 * @author Orhan Aksoy - 09104302
 */
import java.util.*;

public class GITLContext {
    /** The list of parameters passed to each line */
   private LinkedList<String> paramList;
   /** The list of encountered labels */
   private LinkedList<LabelDef> labelList;
   /** The activation stack */
   private Stack<ActivationFrame> activationStack;
   /** The list of functions */
   private LinkedList<FunctionDef> functionList;
   /** the label string that is being seeked
    * by the parser at the moment. When this variable is a nonempty string,
    * this means that the parser has just received a jump statement, but could
    * not find the label in its label list. This means that this label is further
    * down in the code listing. So we keep on parsing the program listing, without
    * actually processing them, until we find the corresponding label. When the
    * label is found, tis variable is set to an empty string again
    */
   private String jumpToLabel = "";

   /** Works exactly the same as jumpToLabel, except that this is for function
    * calls.
    */
   private String jumpToFunction = "";

   /** return value from the program */
   public int returnValue = -1;
   /** program counter */
   public int currentLine = -1;
   /** Set by the return statement to tell the compiler to stop parsing and exit.*/
   public boolean exitStatus = false;

   /**
    * Constructs the label and function lists and activation stack.
    */
   public GITLContext() {
       labelList = new LinkedList<LabelDef>();
       functionList = new LinkedList<FunctionDef>();
       activationStack = new Stack<ActivationFrame>();
   }

   /**
    * Adds a new label at the current line
    * to the current context
    * @param label name of the label.
    * @throws GITLException("Duplicate label")
    */
   public void addLabel(String label) throws GITLException {
      for (LabelDef l : labelList) {
          if ( l.label.equals(label) && ( l.lineNum != currentLine ) )  {
              throw new GITLException("Duplicate label:" + label);
          }
      }
      labelList.add(new LabelDef(currentLine, label));
   }

   /**
    * Returns the jump label that the interpreter is looking for at the moment.
    * If we're not looking for a label, this function returns "".
    * @return the jumpToLabel string.
    */
   public String getJumpLabel() {
       return jumpToLabel;
   }
   /**
    * Returns the jump function name that the interpreter is looking for at the moment.
    * If we're not looking for a function, this function returns "".
    * @return the jumpToFunction string.
    */
   public String getJumpFunction() {
       return jumpToFunction;
   }
   /**
    * Creates a new activation frame, pushes at the top of the stack
    * and jumps to the function location.
    * @param functionName THe name of the function
    * @param param The integer parameter to be passed to the function
    * @param returnParam The return variable name
    * @throws GITLException
    */
   public void callFunction(String functionName, int param, String returnParam) throws GITLException {
       ActivationFrame frame = new ActivationFrame(functionName, currentLine, returnParam );
       activationStack.push(frame);

       // Add the call parameters to the current variable list. This parameter
       // will be treated as a regular local parameter. Note that the name of
       // the actual parameter is not known yet, so it is called 'callParam'.
       // When the function definition is found, this variable will be renamed
       // during interpretation of the called function.
       addVariable("__callParam");
       setVariableValue("__callParam", param);
       
       jumpFunction(functionName);
   }
   /**
    * Ends the current function and restores the previous activation frame
    * by popping the current frame from the activation stack. The current
    * line number is restored from the stack before popping the current frame.
    * @param retVal The return value from the function
    * @throws GITLException
    */
   public void endCurrentFunction(int retVal) throws GITLException {
       if ( activationStack.isEmpty()) {
           throw new GITLException("Activation stack empty."); // TODO: Better error report?
       }

       // The top element of the stack is the current frame. As we're returning
       // from a function, we're going to pop it.
       ActivationFrame frame = activationStack.pop();

       // Check if we're ending the 'main'. If so, tell the interpreter to stop.
       if (activationStack.isEmpty()) {
            setReturn(retVal);
            return;
       }

       // Restore the return address.
       currentLine =  frame.returnLine;
       // Set the return value
       setVariableValue(frame.retVariable, retVal);
   }

   /**
    * Adds a new variable (integer) whose value is set to 0
    * to the current activation frame (the top of the activation stack).
    * @param variable name of the variable.
    * @throws GITLException("Duplicate variable")
    */
   public void addVariable(String variable) throws GITLException {

       if ( activationStack.isEmpty()) {
           throw new GITLException("Activation stack empty.");
       }

       // The top element of the stack is the current frame
       ActivationFrame frame = activationStack.lastElement();

       for (VariableDef v : frame.variableList) {
          if (v.variable.equals(variable)) {
              throw new GITLException("Duplicate variable:" + variable);
          }
       }
       frame.variableList.add(new VariableDef(variable, 0));
   }
   /**
    * This function is used during function calls. WHen a function is called,
    * the parameter being passed is named "__callParam" by the caller. After this,
    * the interpreter finds the function definition location and jumps to this
    * line. THe local name of the parameter is found by the interpreter at that
    * moment, so it renames the "__callParam" variable into the variable name defined
    * in the function definition.
    *
    * @param oldName THe old name of the variable in the current frame
    * @param newName THe new name of the variable 
    * @throws GITLException WHen the activation stack is empty or the variable is not found
    */
   public void renameVariable(String oldName, String newName) throws GITLException {
        if ( activationStack.isEmpty()) {
           throw new GITLException("Activation stack empty.");
       }

       // The top element of the stack is the current frame
       ActivationFrame frame = activationStack.lastElement();

       for (VariableDef v : frame.variableList) {
           if ( v.variable.equals(oldName)) {
               v.variable = newName;
               return;
           }
       }
       throw new GITLException("Variable not found: " + oldName);
   }

   /**
    * Returns the value of a variable in the current activation frame
    * @param variable variable name
    * @return value of the variable
    * @throws GITLException("Variable not found")
    */
   public int getVariableValue(String variable) throws GITLException {
        if ( activationStack.isEmpty()) {
           throw new GITLException("Activation stack empty.");
       }

       // The top element of the stack is the current frame
       ActivationFrame frame = activationStack.lastElement();

       for (VariableDef v : frame.variableList) {
           if ( v.variable.equals(variable)) {
               return v.value;
           }
       }
       throw new GITLException("Variable not found: " + variable);

   }
   /**
    * Sets the value of a variable
    * @param variable The variable to be set
    * @param value The value
    * @throws GITLException("Variable not found")
    */
   public void setVariableValue(String variable, int value) throws GITLException {

        if ( activationStack.isEmpty()) {
           throw new GITLException("Activation stack empty.");
       }

       // The top element of the stack is the current frame
       ActivationFrame frame = activationStack.lastElement();

       for (VariableDef v : frame.variableList) {
           if ( v.variable.equals(variable)) {
               v.value = value;
               return;
           }
       }
       throw new GITLException("Variable not found: " + variable);
   }
   
   /**
    * Retrieves the name of the active function.
    * @return the active function name
    */
   public String getActiveFunction() {
       if ( activationStack.isEmpty()) {
           return null;
       }
       return activationStack.lastElement().functionName;
   }
   /**
    * Sets the return flag to true and also stores
    * the return value. Called to tell the interpreter to stop.
    * @param retVal Return value to be stored.
    */
   public void setReturn(int retVal) {
       exitStatus = true;
       returnValue = retVal;
   }

   /** Called during the 'if' statement interpretation if the variable is nonzero.
    * If the label to jump exists, it means that that we have processed a
    * label statement before with this name. So, we know its line number. In
    * this case, we set the current line number (the program counter).
    *
    * If the label is not found, the context variable 'jumpToLabel' is used.
    * When this variable is a nonempty string, the expression evaluators (other
    * than the label expression) do nothing. When the label expression with the
    * same name is found, we reset to normal interpretation mode again.
    *
    * @param label The label to jump to.
    */
   public void jumpLabel(String label) {
       for (LabelDef l : labelList) {
           if ( l.label.equals(label)) {
               currentLine = l.lineNum;
               jumpToLabel = "";
               return;
           }
       }
       // We haven't encountered this label until now
       // We store this label so that the parser will proceed until it finds
       // this label.

       jumpToLabel = label;

   }

   /** Works exactly the same as jumpLabel function, except that this jump
    * should be to a function definition line by a call statement, not a label.
    *
    * @param functionName The function to jump to.
    * @throws GITLException 
    */
   public void jumpFunction(String functionName) throws GITLException {

       for (FunctionDef f : functionList) {
           if ( f.name.equals(functionName)) {

                // The caller passed the parameter with the name "__callParam"
                // Now, we know the real parameter name, so rename it before
                // jumping to the first line of the function
                renameVariable("__callParam", f.paramName);

                currentLine = f.lineNum;
                jumpToFunction = "";
                return;
           }
       }
       // We haven't encountered this function until now
       // We store the function name so that the parser will proceed until it
       // finds it.

       jumpToFunction = functionName;
   }

   /**
    * returns RUN_JUMP if the interpreter is either processing a conditional jump
    * or a function call, and is searching the line number to jump to.
    * @return run state (RUN_NORMAL or RUN_JUMP)
    */
   public GITLInterpreter.RunState getRunState() {
       if (jumpToLabel.isEmpty() && jumpToFunction.isEmpty()) {
           return GITLInterpreter.RunState.RUN_NORMAL;
       }
       return GITLInterpreter.RunState.RUN_JUMP;
   }
   /**
    * sets the parameters after the current key.
    * @param params the parameters.
    */
   public void setParams(LinkedList params) {
       paramList = params;
   }

   /**
    * returns the parameters after the current key.
    * @return the parameters after the current key.
    */
   public LinkedList<String> getParams() {
       return paramList;
   }

   /**
    * Adds a new function returning int with an int paramerer
    * to the current context at the current line.
    *
    * @param functionName Name of the function
    * @param paramName The name of the parameter in the function definition
    * @throws GITLException("Duplicate function definition")
    */
   public void addFunction(String functionName, String paramName) throws GITLException {
      for (FunctionDef f : functionList) {
          if (f.name.equals(functionName) && ( f.lineNum != currentLine ) )  {
              throw new GITLException("Duplicate function definition:" + functionName);
          }
      }
      functionList.add(new FunctionDef(currentLine, functionName, paramName));
   }

    /**
    * Function definition structure. Contains the line number, name of
    * the function and parameter.
    */
    private static class FunctionDef {
        private int lineNum;
        private String name;
        private String paramName;
        FunctionDef(int ln, String n, String pName) {
            lineNum = ln;
            name = n;
            paramName = pName;
        }
    }

    /**
    * Label definition structure. Contains the line number and name of
    * the label.
    */
    private static class LabelDef {
        private int lineNum;
        private String label;
        LabelDef(int n, String l) {
            lineNum = n;
            label = l;
        }
    }
   /**
    * Variable definition structure. Contains the variable name and value of
    * the variable.
    */
    private static class VariableDef {
        private String variable;
        private int value;
        VariableDef(String name, int val) {
            variable = name;
            value = val;
        }
    }
    /**
     * Activation frame structure.
     * Represents the runtime stack for the current
     * function.
     */
    private static class ActivationFrame {
        /** Return line  */
        private int returnLine;
        /** The name of the current function */
        private String functionName;
        /** Return variable name */
        private String retVariable;
        /** The list of variables */
        private LinkedList<VariableDef> variableList;

        /**
         * Creates a new activation frame
         * @param funcName The name of the current function
         * @param retLineNo the return address
         */
        ActivationFrame(String funcName, int retLineNo, String returnParam){
            returnLine = retLineNo;
            functionName = funcName;
            retVariable = returnParam;
            // Create an empty variable list
            variableList = new LinkedList<VariableDef>();
       }

    }
}
