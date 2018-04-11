package pkg111044069hw04;

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
        
        ConverterInfixToPostfix conv1 = new ConverterInfixToPostfix( "program.git" );
        ConverterInfixToPostfix conv2 = new ConverterInfixToPostfix( "program2.git" );
        ConverterInfixToPostfix conv3 = new ConverterInfixToPostfix( "program3.git" );
        ConverterInfixToPostfix conv4 = new ConverterInfixToPostfix( "program4.git" );
        ConverterInfixToPostfix conv5 = new ConverterInfixToPostfix( "program5.git" );
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
        
        }catch( IOException e ){
            System.out.printf("IOException : %s\n",e.toString());
        }catch( ConverterInfixToPostfix.SyntaxErrorException e ){
            System.out.printf("SyntaxErrorException : %s\n",e.getMessage() );
        }catch( Exception e ){
            System.out.printf("Exception : %s\n",e.toString());
        }
    }
}

