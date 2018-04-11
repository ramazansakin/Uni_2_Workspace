
package pkg111044069hw05;

/**
 * @author ramazan
 */
import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.*;

/**
 * @author ramazan
 */
public class ConverterInfixToPostfix {
     // Data Fields
  static   int numberOfLine;
  private  File file;
  private  FileReader fileReader;
  private  BufferedReader bufferedReader;
  private  CalculatorPostfix calculator;
  static   int numberOfSkipLine;
  
  /** The operators */
  private static final String[] OPERATORS = {"+","-","/","*","(",")","=",
      "sin","cos","tan","cot","exp","log","sqrt","ceil","floor", "^" ,
      "input", "var", "print", "loop", "++", "--", "prints" };

  /** The precedence of the operators, matches order of OPERATORS. */
  private static final int[] PRECEDENCE = {
      1, 1, 2, 2, -2, -2, 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 4, 5, -3, -1, 6, 6,-1  };
  
  public ConverterInfixToPostfix( String filePath ) throws FileNotFoundException{
      
      calculator = new CalculatorPostfix(filePath);
      file = new File(filePath);
      fileReader = new FileReader(file);
      bufferedReader = new BufferedReader(fileReader);
      numberOfLine=0;
      numberOfSkipLine=0;
  }
  
  
  /** Convert a string from infix to postfix.
      @param infix The infix expression
      @throws SyntaxErrorException
   */
  
  public void reader() throws IOException, SyntaxErrorException{
      String fullLine;
      int lineNum;
      numberOfLine=0;
      numberOfSkipLine=0;
      
      while (( fullLine = bufferedReader.readLine()) != null) {
            ++numberOfLine;
            ++numberOfSkipLine;
            // System.out.println(numberOfLine);
            if( !fullLine.isEmpty() && !fullLine.trim().equals("") && !fullLine.trim().equals("\n") &&
                // if the line is used for comment, not convert and evaluate 
                !fullLine.contains("//") ){
                
                lineNum = calculator.eval(convert(fullLine)).intValue();
                
                if( fullLine.contains("loop") ){
                    for( int i=0; i<lineNum && fullLine != null; ++i)
                        fullLine = bufferedReader.readLine();
                    numberOfSkipLine+=lineNum;
                }
            }
      }      
  }
  
    /**
     *
     * @param infix : infix notation of the expression
     * @return  postfix expression of the infix notat. expr.
     * @throws pkg111044069hw04.ConverterInfixToPostfix.SyntaxErrorException
     */
    public static String convert(String infix) throws SyntaxErrorException {
    
    StringBuilder postfix2 = new StringBuilder();
    Stack<String> operatorStack2 = new Stack<>();
    
    // Check the paranthesis whether put properly or not! 
    if (!ParenChecker.isBalanced(infix)){
          throw new SyntaxErrorException("Error : Unmatched parenthesis!");
    }
    
    StringTokenizer infixTokens = new StringTokenizer(infix);
    try {
      // Process each token in the infix string.
      while (infixTokens.hasMoreTokens()) {
        String nextToken = infixTokens.nextToken();
        
        if ( isOperator( nextToken ) > -1 ) {
          processOperator( nextToken, postfix2, operatorStack2 );
        }else if ( Character.isJavaIdentifierStart(nextToken.charAt(0))
            || Character.isDigit(nextToken.charAt(0) )) {
          postfix2.append(nextToken);
          postfix2.append(' ');
        } // Is it an operator? 
        else if( infix.contains("//") ){
            // Skip the line
        }else{
          throw new SyntaxErrorException
              ("Unexpected Character Encountered: "
               + nextToken);
        }
      } // End while.
      // Pop any remaining operators
      // and append them to postfix.
      while (!operatorStack2.empty()) {
        String op = operatorStack2.pop();
        // Any '(' on the stack is not matched.
        if ( op.compareTo("(") == 0)
          throw new SyntaxErrorException(
              "Unmatched opening parenthesis");
        postfix2.append(op);
        postfix2.append(' ');
      }
      // assert: Stack is empty, return result.
      return postfix2.toString();
    }
    catch (EmptyStackException ex) {
      throw new SyntaxErrorException
          ("Syntax Error: Unmatched parenthesis or invalid operator");
    }
  }
  

  /** Method to process operators.
      @param op The operator
      @throws EmptyStackException :  Exception class to show the error with line
   */
  private static void processOperator(String op, StringBuilder postfix2, Stack<String> operatorStack2) {
    if( !isBin(op) ){
        operatorStack2.push(op);
    }else if (operatorStack2.empty() || op.compareTo("(" ) == 0 ) {
        operatorStack2.push(op);
    }else {
      // Peek the operator stack and
      // let topOp be the top operator.
      String topOp = operatorStack2.peek();
      if (precedence(op) > precedence(topOp)) {
        operatorStack2.push(op);
      }else {
        // Pop all stacked operators with equal
        // or higher precedence than op.
        while (!operatorStack2.empty()
               && precedence(op) <= precedence(topOp)) {
          operatorStack2.pop();
          if (topOp.compareTo("(") == 0 ) {
            // Matching '(' popped - exit loop.
            break;
          }
          
          //System.out.print("Line "+numberOfLine+": ->"+topOp);
          postfix2.append(topOp);
          postfix2.append(' ');
          if (!operatorStack2.empty()) {
            // Reset topOp.
            topOp = operatorStack2.peek();
          }
        }
        
        // assert: Operator stack is empty or
        //         current operator precedence >
        //         top of stack operator precedence.
        if (op.compareTo(")") != 0 )
          operatorStack2.push(op);
      }
    }
  }
  

  /** Determine whether a character is an operator.
      @param ch The character to be tested
      @return true if ch is an operator
   */
  private static int isOperator(String op) {
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
  private static int precedence(String op) {
      return PRECEDENCE[isOperator(op)];
  }

    StringBuilder getPostfix() {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
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

        SyntaxErrorException(String no_end_statement_for_loop_ar_dline, int numberOfLine) {
            throw new UnsupportedOperationException("Not supported yet."); 
        }
    
    public String getMessage(){
        return Message;
    }
  }
  
    /**
     * @param op : checks the operator is binary or not
     * @return
     */
    public static boolean isBin( String op ){
      switch(op){
          case "+":  case "-":
          case "/":  case "*":
          case "=":  case "(":
          case ")":
          return true;
      }
      return false;
  }
    
  /* Static class for warning the user about unmatched phranthesis, shows the
    error line  */

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
    Stack < Character > s = new Stack <  > ();
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
   
}
    
}
