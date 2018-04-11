/**
 * Test application for the GITL parser.
 *
 * @author Orhan Aksoy - 09104302
 */

import java.io.*;
import java.util.*;

public class Main {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {

        GITLInterpreter interpreter = new GITLInterpreter();

        if ( ( args.length == 0 ) ||
             ( args[0].lastIndexOf('.')  <=0 ) ||
             (! args[0].substring(1 + args[0].lastIndexOf('.')).equalsIgnoreCase("GITL") ) ) {

            System.out.println("Invalid filename");
            System.exit(1);
       }

        try {
            System.out.println("Interpreting " + args[0]);
            BufferedReader inp = new BufferedReader ( new FileReader(args[0]));
            String line = null;

            LinkedList<String> program = new LinkedList<String>();

            while ((line = inp.readLine()) != null ) {
                program.addLast(line);
            }
            GITLContext context = new GITLContext();

            Long refTime = System.currentTimeMillis();
            interpreter.interpret(context, program);
            System.out.println("Total Execution Time = " + (System.currentTimeMillis() - refTime) + " msecs");

        } catch (IOException ex) {
            ex.printStackTrace();
        }
    }
}
