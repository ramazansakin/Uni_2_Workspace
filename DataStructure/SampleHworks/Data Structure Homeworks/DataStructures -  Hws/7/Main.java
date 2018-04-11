import java.io.*;
import java.util.*;

/**
 * Huffman Coding/Decoding test application
 *
 * @author Orhan Aksoy
 */
public class Main {

    enum COMMAND{CMD_NONE, CMD_ENCODE, CMD_DECODE};
    COMMAND command;
    String fileName="";
    String treeFileName="";
    
    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {

        Main myMain = new Main();
        myMain.processArguments(args);

        if ( ( myMain.command == COMMAND.CMD_NONE) || ( myMain.fileName.isEmpty())) {
            System.out.println("Usage: \thuffman -e -f <filename> to encrypt,\n" +
                               "\t\t huffman -d -f <filename> to decrypt, \n" +
                               "\t\t huffman -c -f <filename> -u <treefilename> to construct and use a new tree");
            return ;
        }

        HuffmanCoder hCoder;

        
        switch (myMain.command) {

            case CMD_ENCODE:
               hCoder = new HuffmanCoder();
               if (!myMain.treeFileName.isEmpty()) {
                    hCoder.createTreeFromFile(myMain.treeFileName);
                }
                System.out.println("Encoding the file " + myMain.fileName);

                hCoder.encodeFile(myMain.fileName);
                break;
            case CMD_DECODE:
               hCoder = new HuffmanCoder();
               if (!myMain.treeFileName.isEmpty()) {
                    hCoder.createTreeFromFile(myMain.treeFileName);
                }
                System.out.println("Decoding the file " + myMain.fileName);

                hCoder.decodeFile(myMain.fileName);
                break;
        }
        
    }
    /**
     * Processes the command line parameters, and
     * sets the command state and filename.
     *
     * @param args command line arguments.
     */
    void processArguments(String[] args) {

         command = COMMAND.CMD_NONE;

         for (int i=0; i<args.length; ++i) {
             if ( args[i].charAt(0) == '-') {
                 if (args[i].length() < 2) {
                     System.out.println("Bad parameters");
                     return;
                 }
                 char currentChar = args[i].charAt(1);
                 switch (currentChar) {
                     case 'd':
                         command = COMMAND.CMD_DECODE;
                         break;
                     case 'e':
                         command = COMMAND.CMD_ENCODE;
                         break;
                     case 'f':
                         if (args.length < i+2) {
                            System.out.println("Bad parameters");
                            return;
                         }
                         fileName = args[i+1];
                         break;
                    case 'u':
                         if (args.length < i+2) {
                            System.out.println("Bad parameters");
                            return;
                         }
                         treeFileName = args[i+1];
                         break;
                     default:
                 }

            }
         }
    }
}
