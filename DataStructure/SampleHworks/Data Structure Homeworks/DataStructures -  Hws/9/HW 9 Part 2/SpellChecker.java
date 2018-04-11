import java.io.*;
import java.util.*;
/**
 * Spell Checker class. Provides functionality to check the spelling of words in a text file and
 * suggesting alternatives to misspelled words.
 *
 * @author Orhan Aksoy - 09104302
 */
public class SpellChecker {
    /** THe list of characters in the alphabet. Set in the constructor. */
    private static final char [] alphabet = new char[26];
    /** The dictionary object to be used during spellcheck. Set in the constructor */
    private Dictionary dict = null;
    /**
     * Constructs a new SpellChecker object. Stores the dictonary reference for
     * using during checking and initializes the alphabet character array.
     * @param dictionary The dictionary object to be used during spell checks.
     */
    public SpellChecker(Dictionary dictionary) {
        dict = dictionary;
        String alph = "abcdefghijklmnopqrstuvwxyz";
        for (int i=0; i<alph.length(); ++i) {
            alphabet[i] = alph.charAt(i);
        }

    }
    /**
     * Spellchecks a text file.
     *
     * @param fileName The file to be checked.
     * @throws IOException If a problem occurs during file open/read.
     */
    public void check(String fileName) throws IOException {
        System.out.println("Checking the file " + fileName);
        BufferedReader input = new BufferedReader( new FileReader(fileName));

        // THis one-item array represents the advice set. This set is filled
        // by various local functions for each word, so this variable needs to
        // be modified by methods to which it is passed. For this reason, a
        // reference to this set is created by putting it into an array.

        Object [] adviceSet = new Object[1];
        adviceSet[0] = new HashSet<String>();

        String line;
        int lineNo = 1;

        // Check each line in the file.
        while ((line = input.readLine()) != null ) {
            checkLine(line, adviceSet, lineNo++);
        }
        System.out.println("File check complete");
    }
    /**
     * Tokenizes a line of string, and checks the spelling of each word.
     * @param line The line string containing the words
     * @param adviceSet The set to be filled by spellchecker if the dictionary lookup fails.
     * @param lineNo The line number of this line.
     */
    private void checkLine(String line, Object [] adviceSet, int lineNo) {
        StringTokenizer tok = new StringTokenizer(line);
        if ( tok.countTokens() == 0 ) {
            return;
        }
        HashSet<String> advices = ((HashSet<String>)(adviceSet[0]));
        while (tok.hasMoreTokens()) {
            // For each word, initialize the advice list.
            advices.clear();
            // The check is made with lower case letters.
            String word = tok.nextToken().toLowerCase();
            // The spellchecker is only interested in letters.
            word = word.replaceAll("[^a-z]", " ");
            // Leave out the leading and trailing whitespaces, and skip if
            // no character is left.
            word = word.trim();
            if (word.length() == 0) {
                continue;
            }
            // Check the word and print out the results.
            if ( checkWord(word, adviceSet) == false) {
                System.out.print("Misspelled word \"" + word + "\" at line " + lineNo);
                if (advices.size() == 0) {
                    System.out.println(", no suggestions.");
                    return;
                }
                System.out.print(", suggestions: ");
                for (String advice : advices) {
                    System.out.print(advice + " ");
                }
                System.out.println();
            }
        }
    }
    /**
     * Spell checks a specified word. If the word is found in the dictionary,
     * returns true. Otherwise, tries to find alternatives to the word by adding
     * and removing one character at all positions within the word and swapping
     * adjacent characters in the word. The list of these alternatives which are
     * in the dictionary is returned to the caller in the array 'results', which
     * is a Set<String> collection.
     *
     * @param word The word to be checked.
     * @param results A one item array to Set<String> of advices
     * @return True if the original word is found in the dictionary.
     */
    private boolean checkWord(String word, Object [] results) {
        if ( dict.hasWord(word)) {
            return true;
        }

        checkOneCharacterAdded(word, results);
        checkOneCharacterRemoved(word, results);
        checkAdjacentSwap(word, results);
        return false;
    }

    /**
     * Takes a word, and generates a list of words by adding each alphabet
     * character one by one to all of the positions within the word, but only one
     * character at a time. For all of these new words, makes a check in the
     * dictionary. If a word exists in the dictionary, this word is added
     * to the set of results.
     *
     * @param word The word to be checked
     * @param results The one item array of Set<String> of new words that exist in the dictionary.
     */
    private void checkOneCharacterAdded(String word, Object [] results) {
        int len = word.length();
        for (int i=0; i<len; ++i) {
            for (char c : alphabet) {
                if (i == 0) {
                    if (dict.hasWord( c + word)) {
                        ((HashSet<String>)(results[0])).add(c + word);
                    }
                }
                if (dict.hasWord(word.substring(0, i+1) + c + word.substring(i+1, word.length()  ))) {
                    ((HashSet<String>)(results[0])).add(word.substring(0, i+1) + c + word.substring(i+1, word.length()  ));
                }
            }
        }
    }
    /**
     * Takes a word, and generates a list of words by removing one character
     * at every position within the word. For all of these new words, makes
     * a check in the dictionary. If a word exists in the dictionary, this
     * word is added to the set of results.
     *
     * @param word The word to be checked
     * @param results The one item arrayo of Set<String> of new words that exist in the dictionary.
     */
    private void checkOneCharacterRemoved(String word, Object [] results) {
        int len = word.length();
        for (int i=0; i<len; ++i) {
            if (dict.hasWord(word.substring(0, i) + word.substring(i+1, len))) {
                ((HashSet<String>)(results[0])).add(word.substring(0, i) + word.substring(i+1, len));
            }
        }
    }
    /**
     * Takes a word, and generates a list of words by swaping two adjacent
     * characters within the string. For all of these new words, makes a check in the
     * dictionary. If a word exists in the dictionary, this word is added
     * to the set of results.
     *
     * @param word The word to be checked
     * @param results The one item arrayo of Set<String> of new words that exist in the dictionary.
     */
    private void checkAdjacentSwap(String word, Object [] results) {
        int len = word.length();
        for (int i=0; i<len-1; ++i) {
            if (dict.hasWord(word.substring(0, i) + word.charAt(i+1) + word.charAt(i) + word.substring(i+2, len))) {
                ((HashSet<String>)(results[0])).add(word.substring(0, i) + word.charAt(i+1) + word.charAt(i) + word.substring(i+2, len));
            }
        }
    }
}
