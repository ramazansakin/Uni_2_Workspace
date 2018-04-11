

import java.util.*;

/**
 * Extended AVL Tree Class test application
 *
 * @author Orhan Aksoy
 */
public class Main {

    /** The type of the test being carried out */
    static enum TESTTYPE{INVALID, COMPLETE, WORSTCASE, LOGN};

    /**
     * Parses the input arguments and returns the test type and the list
     * of integers to be stored in the avl tree. The test type and integer
     * list are returned in an object array.
     *
     * @param args COmmand line argument array
     * @return An object array whose 1st element is the test type and the second
     *         element is a reference to the integer array.
     */
    private static Object [] parseArgs (String [] args){

        TESTTYPE type = TESTTYPE.INVALID;
        ArrayList<Integer> valueList = new ArrayList<Integer>();

        for (String arg : args) {
            if (arg.equals("-c")) {
                type = TESTTYPE.COMPLETE;
                continue;
            } else if (arg.equals("-w")) {
                type = TESTTYPE.WORSTCASE;
                continue;
            } else if (arg.equals("-l")) {
                type = TESTTYPE.LOGN;
                continue;
            } else {
                valueList.add(Integer.parseInt(arg));
            }
        }

        Object [] returnArray = new Object[2];
        returnArray[0] = type;
        returnArray[1] = valueList;
        return returnArray;
    }
    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        Object [] argList = parseArgs(args);

        TESTTYPE type = (TESTTYPE)(argList[0]);
        ArrayList<Integer> valueList = (ArrayList<Integer>) (argList[1]);

        if (valueList.size() == 0) {
            System.out.println("Usage: ");
            System.out.println("java Main <test type> <integer list>");
            System.out.println("<test type> : -l -> Log(n) tree");
            System.out.println("              -w -> Worst case tree");
            System.out.println("              -c -> Complete tree");
            System.out.println("<integer list>: integers separated by space");
            return;
        }

        switch (type) {
            case INVALID:
                System.out.println("Invalid tree type");
                break;
            case COMPLETE:
                System.out.println("Testing complete tree");
                testCompleteTree(valueList);
                break;
            case WORSTCASE:
                System.out.println("Testing worst case tree");
                testWorstCaseTree(valueList);
                break;
            case LOGN:
                System.out.println("Testing log(n) tree");
                testLogNTree(valueList);
                break;
        }
    }
    /**
     * Creates a complete avl tree using the provided integer values.
     * @param valueList The list of values to be put into the complete tree.
     */
    private static void testCompleteTree(List<Integer> valueList) {
        ExtendedAVLTree<Integer> tree = new ExtendedAVLTree(valueList.toArray(), ExtendedAVLTree.TREETYPE.COMPLETE);
        System.out.println("Complete Tree test with " + valueList.size() + " items:");
        System.out.println("Tree height is " + tree.getHeight());
        System.out.println(tree);
        System.out.println("----------------------------------------------------------");

    }
    /**
     * Creates a worst case avl tree using the provided integer values.
     * @param valueList The list of values to be put into the complete tree.
     */
    private static void testWorstCaseTree(List<Integer> valueList) {
        ExtendedAVLTree<Integer> tree = new ExtendedAVLTree(valueList.toArray(), ExtendedAVLTree.TREETYPE.WORSTCASE);
        System.out.println("Worst case Tree test with " + valueList.size() + " items:");
        System.out.println("Tree height is " + tree.getHeight());
        System.out.println(tree);
        System.out.println("----------------------------------------------------------");
    }
    /**
     * Creates a worst case avl tree using the provided integer values.
     * @param valueList The list of values to be put into the complete tree.
     */
    private static void testLogNTree(List<Integer> valueList) {
        ExtendedAVLTree<Integer> tree = new ExtendedAVLTree(valueList.toArray(), ExtendedAVLTree.TREETYPE.LOGN);
        System.out.println("Log(n) Tree test with " + valueList.size() + " items:");
        System.out.println("Tree height is " + tree.getHeight());
        System.out.println(tree);
        System.out.println("----------------------------------------------------------");
    }

}
