import java.io.*;
import java.util.*;

/**
 * Dictionary class.
 * Provides functionality to load a dictionary file, and to check if a
 * specific word exists in the dictionary.
 *
 * @author Orhan Aksoy - 09104302
 */
public class Dictionary {
    /** THe set containing the dictionary words */
    private HashSet<String> dict = new HashSet<String>();

    /**
     * Loads the dictionary words from a text file.
     * @param fileName The file containing the words.
     * @throws IOException If a problem occurs during opening/reading the file.
     */
    public void load(String fileName) throws IOException {
        System.out.println("Loading the dictionary file");
        BufferedReader input = new BufferedReader( new FileReader(fileName));

        String line;

        while ((line = input.readLine()) != null ) {
            addWord(line);
        }
        System.out.println("Dictionary file loaded");
    }
    /**
     * Checks if a word exists in the dictionary.
     * @param word THe word to be checked
     * @return True if the specified word exists in the dictionary
     */
    public boolean hasWord(String word) {
        return dict.contains(word);
    }
    /**
     * Returns the number of words in the dictionary.
     * @return The number of words in the dictionary.
     */
    public int wordCount() {
        return dict.size();
    }
    /**
     * Adds a word to the dictionary set.
     * @param word The word to be added.
     */
    private void addWord(String word) {
        dict.add(word.trim().toLowerCase());
    }
}
