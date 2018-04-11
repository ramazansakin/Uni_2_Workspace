
package pkg111044069hw05;

import java.io.FileNotFoundException;
import java.io.IOException;

/**
 * @author ramazan
 */
public class Main {    

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) throws FileNotFoundException  {
        /* Converters for each file so there are 10 files at the project */
        ConverterInfixToPostfix conv1 = new ConverterInfixToPostfix( "program.git" );
        ConverterInfixToPostfix conv2 = new ConverterInfixToPostfix( "program2.git" );
        ConverterInfixToPostfix conv3 = new ConverterInfixToPostfix( "program3.git" );
        ConverterInfixToPostfix conv4 = new ConverterInfixToPostfix( "program4.git" );
        ConverterInfixToPostfix conv5 = new ConverterInfixToPostfix( "program5.git" );
        /* file that includes error to show the error about redecleared error  */
        ConverterInfixToPostfix conv8 = new ConverterInfixToPostfix( "errProgram.git" );
        ConverterInfixToPostfix conv10 = new ConverterInfixToPostfix( "program8.git");
        /* Ic ice 2 loop lu example program */
        ConverterInfixToPostfix conv6 = new ConverterInfixToPostfix( "nestedLoop.git" );
        /* Ic ice 3 loop lu example program */
        ConverterInfixToPostfix conv7 = new ConverterInfixToPostfix( "nestedLoop2.git" );
        /* file that includes error to show the error about nested loop error  */
        ConverterInfixToPostfix conv9 = new ConverterInfixToPostfix( "nestedErr.git" );
        
        try{
            
            System.out.println("-------------------------  File program.git   --------------------");
            conv1.reader();
            System.out.println("-------------------------------------------------------------------\n");
        
            System.out.println("-------------------------  File program2.git   --------------------");
            conv2.reader();
            System.out.println("-------------------------------------------------------------------\n");
            
            System.out.println("-------------------------  File program3.git   --------------------");
            conv3.reader();
            System.out.println("-------------------------------------------------------------------\n");
            
            System.out.println("-------------------------  File program4.git   --------------------");
            conv4.reader();
            System.out.println("-------------------------------------------------------------------\n");
            
            System.out.println("-------------------------  File program5.git   --------------------");
            conv5.reader();
            System.out.println("-------------------------------------------------------------------\n");
            
            System.out.println("-------------------------  File program8.git   --------------------");
            conv10.reader();
            System.out.println("-------------------------------------------------------------------\n");
            
            System.out.println("-------------------------  File nestedLoop.git   --------------------");
            conv6.reader();
            System.out.println("-------------------------------------------------------------------\n");
            
            System.out.println("-------------------------  File nestedLoop2.git   --------------------");
            conv7.reader();
            System.out.println("-------------------------------------------------------------------\n");
            
        }catch( IOException e ){
            System.out.printf("IOException : %s\n",e.toString());
        }catch( ConverterInfixToPostfix.SyntaxErrorException e ){
            System.out.printf("SyntaxErrorException : %s\n",e.getMessage() );
        }catch( Exception e ){
            System.out.printf("Exception : %s\n",e.toString());
        }
        
        /* Because of catching the errors, I seperated error files to another try-catch blocks */
        try{
            
            System.out.println("-------------------------  File errProgram.git   --------------------");
            conv8.reader();
            System.out.println("-------------------------------------------------------------------\n");
         
        }catch( IOException e ){
            System.out.printf("IOException : %s\n",e.toString());
        }catch( ConverterInfixToPostfix.SyntaxErrorException e ){
            System.out.printf("SyntaxErrorException : %s\n",e.getMessage() );
        }catch( Exception e ){
            System.out.printf("Exception : %s\n",e.toString());
        }
        
        try {
            
            System.out.println("-------------------------  File nestedErr.git   --------------------");
            conv9.reader();
            System.out.println("-------------------------------------------------------------------\n");
        
        }catch( IOException e ){
            System.out.printf("IOException : %s\n",e.toString());
        }catch( ConverterInfixToPostfix.SyntaxErrorException e ){
            System.out.printf("SyntaxErrorException : %s\n",e.getMessage() );
        }catch( Exception e ){
            System.out.printf("Exception : %s\n",e.toString());
        }
    }
}

