import java.util.*;
import java.io.*;

/**
 * Heap implementation
 *
 * @author Orhan Aksoy - 09104303
 *
 * @param <E> The type of items that will be stored in the heap. This type must implement Comparable interface.
 *
 */
public class Heap<E extends Comparable<E>> implements Serializable {
    /** The array list storing the heap elements */
    private ArrayList<E> valArray = new ArrayList<E>();

    /**
     * Adds a new item into the heap.
     * @param item
     */
    void add(E item) {
        valArray.add(item);

        // The index to the added item in the heap.
        int index = valArray.size()-1;

        // Swap this item with its parent until either its parent is larger than it,
        // or it becomes the root.
        while ( ( index >= 1 ) && (valArray.get(index).compareTo(valArray.get((index-1)/2)) < 0) ) {
            swapItems(index, (index-1)/2);
            index = (index - 1)/2;
        }
    }
    /**
     * Returns the root of the heap and restructures it so that
     * The tree keeps being a heap.
     *
     * @return THe root of the heap.
     */
    public E getFirst() {

        // Return null if the heap is empty.
        if ( valArray.size() == 0) {
            return null;
        }

        // The item to be returned is the root.

        E retVal = valArray.get(0);

        // REturn and remove the first item if the heap has only
        // one item.
        if ( valArray.size() == 1) {
            valArray.remove(0);
            return retVal;
        }

        // Get the last item in the array, and overwrite the root
        // which is array[0]
        valArray.set(0, valArray.remove(valArray.size()-1));

        int index = 0;

        // This loop first checks if any of the children of the root is less
        // than the root. If so, flips them. Then checks for the next child
        // until the child is less than the parent.
        while ( 2*index+1 < valArray.size() ) {

            // If the item at index has only one child, we're going to quit.
            // Before quitting, swap it with its child if the child is bigger or equal.
            if ( 2*index + 2 == valArray.size()) {
                if ( valArray.get(index).compareTo(valArray.get(2*index + 1)) >= 0)
                    swapItems(index, 2*index+1);
                break;
            }
            // Swap the items at index and the smaller of its two children
            int swapIndex = (valArray.get(2*index+1).compareTo(valArray.get((2*index+2)))) < 0 ?
                            2*index+1 : 2*index+2;

            // If the item is smaller than its both children, quit.
            if (valArray.get(index).compareTo(valArray.get(swapIndex)) < 0) {
                break;
            }
            swapItems(index, swapIndex);

            index = swapIndex;

        }

        return retVal;
    }

    /**
     * Creates a string representation of the heap.
     * @return The string representation of the heap.
     */
    public String toString() {
        StringBuilder str = new StringBuilder();

        int index = 0;
        while (index < valArray.size()) {
            for (int i=index; (i<2*index+1) && (i<valArray.size()); ++i) {
                str.append(valArray.get(i));
                str.append("\t");
            }
            str.append("\n");
            index *= 2;
            index++;
        }
        return str.toString();
    }
    /**
     * Returns the number of items in the heap.
     * @return The number of items in the heap.
     */
    public int getCount() {
        return valArray.size();
    }

    /**
     * Clears the heap.
     */
    public void clear() {
        valArray.clear();
    }

    /**
     * Swaps the two items in the heap pointed by indices index1 and index2
     * @param index1 INdex to the first item to be swapped
     * @param index2 Index to the second item to be
     */
    private void swapItems(int index1, int index2) {

        // This is a private function, so assert if we misused it.
        assert( (index1 < valArray.size()) && (index2 < valArray.size()) );

        E tmpItem = valArray.get(index2);
        valArray.set(index2, valArray.get(index1));
        valArray.set(index1, tmpItem);
    }
}
