/**
 * Spellchecker application.
 *
 * @author Orhan AKsoy - 09104302
 */
import java.io.*;
public class Main {

    /**
     * Accepts two arguments: THe dictionary file and the test file. THen,
     * creates the dictionary and makes a spellcheck of the test file, and
     * prints out the results.
     * 
     * @param args the command line arguments
     */
    public static void main(String[] args) {

        if (args.length < 2) {
            System.out.println("Usage: java Main <dictionary file> <test file>");
            return;
        }
        String dictionaryFile = args[0];
        String testFile = args[1];

        Dictionary dict = new Dictionary();
        SpellChecker checker = new SpellChecker(dict);
        try {
            dict.load(dictionaryFile);
            System.out.println("Total words in the dictionary: " + dict.wordCount());
            Long refTime = System.currentTimeMillis();
            checker.check(testFile);
            System.out.println("Spellcheck time: " + (System.currentTimeMillis() - refTime) + " milliseconds.");

        } catch (IOException e) {
            e.printStackTrace();
        }
    }

}
