import java.io.*;
import java.util.*;

/**
 * Huffman tree impelementation
 *
 * @author Orhan Aksoy - 09104302
 */
public class HuffmanTree < E extends Comparable<E> >   {

    /** The frequency heap containing value-frequency pairs. */
    private Heap< Node > frequencyHeap = new Heap< Node >();

    /** The root node of the tree */
    private Node root;

    /** The binary file storing the huffman tree */
    private static final String dataFileName = "Huffman.dat";

    /** Storage area used during decoding */
    private ArrayList<Integer> decodeStream = new ArrayList<Integer>();

    /**
     * Using the frequency heap, this function sets the connections between
     * nodes, creating the binary tree. To do it, this method removes smallest
     * two items from the tree, creates a parent for both of them, and adds it\
     * to the heap. At every iteration, the number of items in the heap
     * decreases by one. When there's only one item in the heap, the method
     * returns.
     * This last item in the heap is the root of the binary tree.
     */
    public void constructTree() {
        while (frequencyHeap.getCount() > 1 ) {
            Node item1 = frequencyHeap.getFirst();
            Node item2 = frequencyHeap.getFirst();

            Node newNode = new Node(null, item1.frequency + item2.frequency);
            newNode.left = item1;
            newNode.right = item2;
            frequencyHeap.add(newNode);
            root = newNode;
        }
    }

    /**
     * This is a wrapper metod for decoding an item 'e'
     * @param e The item to be decoded
     * @param code The binary code of the item
     * @param length The number of bits for the code
     * @return True if the code is found in the tree.
     */
    public boolean getCode(E e, int [] code, int [] length) {

        int depth = 0;
        return getCode(root, code, depth, length, e);
    }

    /**
     * This recursive method finds a given item in the huffman tree and
     * derives its huffman code.
     *
     * @param localRoot The node from which the search will begin
     * @param bld The integer value storing the code bits
     * @param depth recursion parameter
     * @param finalDepth Returns the depth at which the item was found.
     * @param e The item to be searched
     * @return True if the item is found.
     */
    private boolean getCode(Node localRoot, int [] bld, int depth, int [] finalDepth, E e) {
        // The base case. If this node is a leaf node, only check its value.
        if (localRoot.left == null) {
            finalDepth[0] = depth;
            return (e.compareTo(localRoot.value) == 0);
        } else {
            // If the item is found on the left branch, leave the code as it is
            if (getCode(localRoot.left, bld, depth+1, finalDepth, e)) {
                return true;
            } else if (getCode(localRoot.right, bld, depth+1, finalDepth, e)) {
               bld[0] |= (1<<(finalDepth[0] - depth - 1));
               return true;
            }
            return false;
        }
    }


    /**
     * Decodes the input bit stream.
     * Every time this method is called, the input 'bit' value is appended
     * to the stored decoding bitstream, and the bitstream is checked against
     * the tree. If a match occurs, the bitstream is reset and the item is
     * returned.
     * 
     * @param bit Represents the bit in the code.
     * @return The decoded item if decode succeeds, null otherwise.
     */
    public E decode(int bit) {
        decodeStream.add(bit);
        E retVal = decode(root, 0);
        if (retVal != null) {
            decodeStream.clear();
        }
        return retVal;
    }

    private E decode(Node localRoot, int bitIndex) {
        if (localRoot.value != null) {
            return localRoot.value;
        } else {
            if (bitIndex >= decodeStream.size()) {
                return null;
            }
            if (decodeStream.get(bitIndex) == 0) {
                return decode(localRoot.left, bitIndex + 1);
            } else {
                return decode(localRoot.right, bitIndex + 1);
            }
        }
    }

    
   /**
     * Adds a value-frequency pair to the frequency heap
     * @param e The type of values.
     * @param prb The frequency of the value.
     */
    public void addFrequency(E e, double freq) {
        frequencyHeap.add(new Node(e, freq));
    }
    /**
     * Resets the frequency heap so that the 'addFrequency' calls can
     * rebuilt the heap.
     */
    void resetFrequencyHeap() {
        frequencyHeap.clear();
    }
    public void printProbabilities() {
        System.out.println(" The item frequency distribution ====================");
        System.out.println(frequencyHeap.toString());

    }
    public void printTree() {
        System.out.println(" The Huffman Tree ====================");
        printTree(root, 0);


    }
    private void printTree(Node localRoot, int tabCount) {
        for (int i =0; i<tabCount; ++i) {
            System.out.print("\t");
        }
        System.out.println(localRoot.value + "(" + localRoot.frequency + ")");
        if (localRoot.left != null) {
            printTree(localRoot.left, tabCount+1);
        }
        if (localRoot.right != null) {
            printTree(localRoot.right, tabCount+1);
        }
    }

    /**
     * The Frequency-Value Pair structure
     */
    private class Node implements Comparable<Node>, Serializable {
        private E value;
        private double frequency;
        Node left;
        Node right;

        /**
         * Two Value-Frequency pairs are compared according to their
         * frquency values.
         * @param fData
         * @return
         */
        public int compareTo(Node fData) {
            if (frequency < fData.frequency) {
                return -1;
            } else if (frequency > fData.frequency) {
                return 1;
            } else {
                return 0;
            }
        }
        /**
         * Constructs a Node struture with given item and frequency
         * @param e The item
         * @param f The frequency of the item
         */
        public Node(E e, double f) {
            value = e;
            frequency = f;
        }
        /**
         * Generates the string represenatation of a node.
         * @return
         */
        public String toString() {
            return "( " + value + " -> " + frequency + " )";
        }
    }

 
}
