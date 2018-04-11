package pkg111044069hw04;

/**
 * @author ramazan
 */
import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.*;

public class ConverterInfixToPostfix {

  // Data Fields
  /** The operator stack */
  private Stack < String > operatorStack;
  static  int numberOfLine;
  private  File file;
  private  FileReader fileReader;
  private  BufferedReader bufferedReader;
  
  /** The operators */
  private static final String[] OPERATORS = {"+","-","/","*","(",")","=",
      "sin","cos","tan","cot","exp","log","sqrt","ceil","floor", "^" ,
      "input", "var", "print" };

  /** The precedence of the operators, matches order of OPERATORS. */
  private static final int[] PRECEDENCE = {
      1, 1, 2, 2, -2, -2, 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 4, 5, -1 };
  
  /** The postfix string */
  private StringBuilder postfix;
  private CalculatorPostfix calculator;
  
  public ConverterInfixToPostfix( String filePath ) throws FileNotFoundException{
      
      operatorStack = new Stack<>();
      postfix = new StringBuilder();
      calculator = new CalculatorPostfix();
      numberOfLine = 0;
      file = new File(filePath);
      fileReader = new FileReader(file);
      bufferedReader = new BufferedReader(fileReader);
  }
  
  
  /** Convert a string from infix to postfix.
      @param infix The infix expression
      @throws SyntaxErrorException
   */
  public void reader() throws IOException, SyntaxErrorException{
      String fullLine;
      numberOfLine=0;
      while (( fullLine = bufferedReader.readLine()) != null) {
            ++numberOfLine;
            //System.out.println(numberOfLine);
            if( !fullLine.isEmpty() && !fullLine.trim().equals("") && !fullLine.trim().equals("\n") &&
                /* if the line is used for comment, not convert //  */    
                !(fullLine.charAt(0) == '/' && fullLine.charAt(1) == '/' ) ){
                calculator.eval(convert(fullLine));
            }
      }
      
      
  }
  
  
  public String convert(String infix) throws SyntaxErrorException {
    
    postfix = new StringBuilder();
    operatorStack = new Stack<>();
    
    // Check the paranthesis
    if (!ParenChecker.isBalanced(infix)){
          throw new SyntaxErrorException("Error : Unmatched parenthesis!");
    }
    
    StringTokenizer infixTokens = new StringTokenizer(infix);
    try {
      // Process each token in the infix string.
      while (infixTokens.hasMoreTokens()) {
        String nextToken = infixTokens.nextToken();
        
        if ( isOperator( nextToken ) > -1 ) {
          processOperator( nextToken );
        }else if ( Character.isJavaIdentifierStart(nextToken.charAt(0))
            || Character.isDigit(nextToken.charAt(0) )) {
          postfix.append(nextToken);
          postfix.append(' ');
        } // Is it an operator? 
        else {
          throw new SyntaxErrorException
              ("Unexpected Character Encountered: "
               + nextToken);
        }
      } // End while.
      // Pop any remaining operators
      // and append them to postfix.
      while (!operatorStack.empty()) {
        String op = operatorStack.pop();
        // Any '(' on the stack is not matched.
        if ( op.compareTo("(") == 0)
          throw new SyntaxErrorException(
              "Unmatched opening parenthesis");
        postfix.append(op);
        postfix.append(' ');
      }
      // assert: Stack is empty, return result.
      return postfix.toString();
    }
    catch (EmptyStackException ex) {
      throw new SyntaxErrorException
          ("Syntax Error: Unmatched parenthesis or invalid opearator");
    }
  }

  public StringBuilder getPostfix(){
      return postfix; 
  }

  /** Method to process operators.
      @param op The operator
      @throws EmptyStackException
   */
  private void processOperator(String op) {
    if( !isBin(op) ){
        operatorStack.push(op);
    }else if (operatorStack.empty() || op.compareTo("(" ) == 0 ) {
        operatorStack.push(op);
    }else {
      // Peek the operator stack and
      // let topOp be the top operator.
      String topOp = operatorStack.peek();
      if (precedence(op) > precedence(topOp)) {
        operatorStack.push(op);
      }else {
        // Pop all stacked operators with equal
        // or higher precedence than op.
        while (!operatorStack.empty()
               && precedence(op) <= precedence(topOp)) {
          operatorStack.pop();
          if (topOp.compareTo("(") == 0 ) {
            // Matching '(' popped - exit loop.
            break;
          }
          
          //System.out.print("Line "+numberOfLine+": ->"+topOp);
          postfix.append(topOp);
          postfix.append(' ');
          if (!operatorStack.empty()) {
            // Reset topOp.
            topOp = operatorStack.peek();
          }
        }
        
        // assert: Operator stack is empty or
        //         current operator precedence >
        //         top of stack operator precedence.
        if (op.compareTo(")") != 0 )
          operatorStack.push(op);
      }
    }
  }
  

  /** Determine whether a character is an operator.
      @param ch The character to be tested
      @return true if ch is an operator
   */
  private int isOperator(String op) {
      for( int i=0; i<OPERATORS.length ; ++i ){
          if( op.compareTo(OPERATORS[i])  == 0)
              return i;
      }
      return -1;  
  }

  /** Determine the precedence of an operator.
      @param op The operator
      @return the precedence
   */
  private int precedence(String op) {
      return PRECEDENCE[isOperator(op)];
  }
  
  /* My Syntax Error Exception Class */
  /** Class to report a syntax error. */
  public static class SyntaxErrorException extends Exception {
    /** Construct a SyntaxErrorException with the specified
        message.
        @param message The message
     */
    String Message;
    SyntaxErrorException(String message) {
      super(message);
      Message = message;
    }
    
    public String getMessage(){
        return Message;
    }
  }
  
  public boolean isBin( String op ){
      switch(op){
          case "+":  case "-":
          case "/":  case "*":
          case "=":  case "(":
          case ")":
          return true;
      }
      return false;
  }
  
  public static class ParenChecker {

  // Constants
  /** Set of opening parenthesis characters. */
  private static final String OPEN = "([{";

  /** Set of closing parenthesis characters, matches OPEN. */
  private static final String CLOSE = ")]}";

 
  /** Test the input string to see that it contains balanced
      parentheses. This method tests an input string to see
      that each type of parenthesis is balanced. '(' is matched
      with ')', '[' is matched with ']', and
      '{' is matched with '}'.
      @param expression A String containing the expression to
             be examined
      @return true if all the parentheses match
   */
  public static boolean isBalanced(String expression) {
    // Create an empty stack.
    Stack < Character > s = new Stack < Character > ();
    boolean balanced = true;
    try {
      int index = 0;
      while (balanced && index < expression.length()) {
        char nextCh = expression.charAt(index);
        if (isOpen(nextCh)) {
          s.push(nextCh);
        }
        else if (isClose(nextCh)) {
          char topCh = s.pop();
          balanced = OPEN.indexOf(topCh)
              == CLOSE.indexOf(nextCh);
        }
        index++;
      }
    }
    catch (EmptyStackException ex) {
      balanced = false;
    }
    return (balanced && s.empty());
  }

  /** Method to determine whether a character is one of the
      opening parentheses.
      @param ch Character to be tested
      @return true if ch is one of the opening parentheses
   */
  private static boolean isOpen(char ch) {
    return OPEN.indexOf(ch) > -1;
  }

  /** Method to determine whether a character is one of the
      closing parentheses.
      @param ch Character to be tested
      @return true if ch is one of the closing parentheses
   */
  private static boolean isClose(char ch) {
    return CLOSE.indexOf(ch) > -1;
  }

  /** main method. Ask the user for a string and
      call the ParenChecker to see whether the parentheses
      are balanced.
      @param args Not used
   */
   
}
  
}
