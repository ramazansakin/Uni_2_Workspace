/**
 * Multiple Heap Data Structure
 *
 * This class keeps a collection of items, and can be queried for the
 * first item with respect to various criteria.
 *
 * @author Orhan Aksoy - 09104302
 */
import java.util.*;

public class MultipleHeap<E> {
    /** A list of arrays representing heaps */
    private  ArrayList<ArrayList<Node>> itemList = new  ArrayList<ArrayList<Node>>();
    /** The criteria array that the items are organized according to */
    private Comparator [] criteriaArray;

    /**
     * Creates a MultipleHeap instance using the Comparator array. The Comparator
     * objects in the provided Comparator array are used to organize the items
     * differently in each different heap. The number of heaps is equal to the
     * number of items in the comparator array.
     * 
     * @param compArray The comparator array composed of Comparator objects
     * each of which compare two Items differently.
     */
    MultipleHeap(Comparator [] compArray) {
        
        if (compArray == null) {
            throw new NullPointerException("compArray cannot be null");
        }
        if (compArray.length == 0) {
            throw new IllegalArgumentException("compArray size is zero");
        }
        // Store the comparator array.
        criteriaArray = compArray;

        // Create the array lists which constitute the heap stores. THe number
        // of heaps is equal to the number of ways the items can be organized,
        // that is, the size of the comparator array.

        itemList = new ArrayList<ArrayList<Node>>(criteriaArray.length);
        for (int i=0; i<criteriaArray.length; ++i) {
            itemList.add(new ArrayList<Node>());
        }
    }

    /**
     * Adds a new item into the heap.
     * 
     * @param item The item to be added to the heap.
     */
    void add(E item) {

        // For the first heap, create a new node object that contain the item data,
        // and for the rest of the heaps, use the same reference. Following the
        // heap addition algorithm, the references are all added to the end of
        // the heap arrays as the last item of the heap.

        for (int i=0; i<criteriaArray.length; ++i) {
            Node newNode = (i == 0) ? new Node(item) : itemList.get(0).get(itemList.get(0).size()-1);
            itemList.get(i).add(newNode);

            // Together with the actual item data, the nodes contain an array of
            // indices that represent the same node's position in different
            // heaps. When a new node is added, it is appended to the end of the
            // heap, so the index values are equal to the last index in the heaps.

            newNode.addIndex(itemList.get(i).size()-1);
        }

        // For all heaps, follow the heap addition algorithm after the addition
        // of a new item to the end of the heap:
        // Flip this new item with its parent until it is _not_ smaller than
        // the parent or it becomes the root. During checking whether it is
        // smaller than its parent, the stored comparator object is used.

        for (int i=0; i<criteriaArray.length; ++i) {

            // The index to the added item in the heap is the last position.
            int index = itemList.get(i).size()-1;

            // Swap this item with its parent until either its parent is larger than it,
            // or it becomes the root.

            while ( ( index >= 1 ) && (criteriaArray[i].compare(itemList.get(i).get(index).getValue() ,itemList.get(i).get((index-1)/2).getValue() ) < 0) ) {
                swapItems(i, index, (index-1)/2);
                index = (index - 1)/2;
            }

        }
    }

    /**
     * Returns the root of the heap according to the criteria identified
     * by the index.
     *
     * @param criteriaIndex The index into the criteria array according to which
     * the first item will be returned.
     * @return THe root of the heap. null if the heap is empty.
     */
    public  E findFirst(int criteriaIndex) {
        // Return null if the heap is empty.
        if ( itemList.get(criteriaIndex).size() == 0) {
            return null;
        }

        // The item to be returned is the root.

        return itemList.get(criteriaIndex).get(0).getValue();

    }
    /**
     * Returns and removes the root of the heap and restructures all of
     * the heaps so that the trees keep heap properties.
     *
     * @param criteriaIndex The index into the criteria array according to which
     * the first item will be returned.
     * @return THe root of the heap. null if the heap is empty.
     */
    public E getFirst(int criteriaIndex) {

        // Return null if the heap is empty.
        if ( itemList.get(criteriaIndex).size() == 0) {
            return null;
        }

        // The item to be returned is the root.

        E retVal = itemList.get(criteriaIndex).get(0).getValue();

        // Remove the item at the root according to the criteria identified
        // by criteriaIndex.

        removeAt(criteriaIndex, 0);

        return retVal;


    }
    /**
     * Removes an item from the heap identified by the criteriaIndex. THen,
     * it restores the heap structure for all of the heaps:
     * 1. swaps the hole with its parent until the root;
     * 2. moves the last item of the heap onto the root
     * 3. swaps the root with its smaller child until the child is greater.
     * @param criteriaIndex Index to the criteria from which the remove will be done
     * @param removeIndex The index to the item that will be removed.
     */
    private void removeAt(int criteriaIndex, int removeIndex) { 

       int tmpIndex = removeIndex;

        // Shift the item to be deleted up to the root.
        while ( tmpIndex >= 1 ) {

             swapItems(criteriaIndex, tmpIndex, (tmpIndex-1)/2);
             tmpIndex = (tmpIndex - 1)/2;
        }

        int size = itemList.get(criteriaIndex).size();

        // Now, the item to be removed is the root.

        // If there is only one item in the heap, then
        // remove this single item in all of the heaps.

        if (size == 1) {
            for (int i=0; i<itemList.size(); ++i) {
                itemList.get(i).clear();
            }
            return;
        }

        // Swap the first and last items in the array, overwriting the root
        // which is array[0], because the root is being deleted.

        swapItems(criteriaIndex, 0, size-1);

        // Now, the last item points to the node being deleted. Get the list of
        // indices inside this node. These indices represent the cells in all of
        // the heaps that point to this node.

        ArrayList<Integer> indices = itemList.get(criteriaIndex).get(size-1).indices;

        // Remove this node.

        itemList.get(criteriaIndex).remove(size-1);

        // We have just removed the node reference within the heap that we are
        // in now. But, there may be some other heaps that have references to
        // this node as well. So, for all heaps, find the cell within the
        // heap and remove it, too.

        for (int i=0; i<indices.size(); ++i) {

            // Skip our own heap, because we just have removed it there.
            if (criteriaIndex == i) {
                continue;
            }

            // Size match means we haven't removed the item for this heap yet.
            // After the removal, itemList.get(i).size() will return size - 1.
            // This also represents the base case for the recursive call to
            // removeAt method.

            if (itemList.get(i).size() == size) {
                removeAt(i, indices.get(i));
            }
        }

        // Now we have a new item at the root. Move this item down to an
        // appropriate place to restore the heap structure.
        // To do it, this item will be flipped with the
        // smaller of its children as long as it is bigger than them.

        int index = 0;

        // This loop first checks if any of the children of the root is less
        // than the root. If so, flips them. Then checks for the next child
        // until the child is less than the parent.
        while ( 2*index+1 < itemList.get(criteriaIndex).size() ) {

            // If the item at index has only one child, we're going to quit.
            // Before quitting, swap it with its child if the child is bigger or equal.
            if ( 2*index + 2 == itemList.get(criteriaIndex).size()) {
                if (criteriaArray[criteriaIndex].compare(itemList.get(criteriaIndex).get(index).getValue() ,itemList.get(criteriaIndex).get(2*index + 1).getValue() ) >= 0) {
                    swapItems(criteriaIndex, index, 2*index+1);
                }
                break;
            }
            // Swap the items at index and the smaller of its two children

            int swapIndex = criteriaArray[criteriaIndex].compare(itemList.get(criteriaIndex).get(2*index + 1).getValue() ,itemList.get(criteriaIndex).get(2*index + 2).getValue() ) < 0 ?
                            2*index+1 : 2*index+2;

            // If the item is smaller than its both children, quit.
            if (criteriaArray[criteriaIndex].compare( itemList.get(criteriaIndex).get(index).getValue(), itemList.get(criteriaIndex).get(swapIndex).getValue()) < 0) {
                break;
            }
            swapItems(criteriaIndex, index, swapIndex);

            index = swapIndex;

        }
       
   }

    /**
     * Swaps the two items in the heap pointed by indices index1 and index2
     * @param criteriaIndex The criteria within which the swap operation will be performed.
     * @param index1 INdex to the first item to be swapped
     * @param index2 Index to the second item to be
     */
    private void swapItems(int criteriaIndex, int index1, int index2) {

        // This is a private function, so assert if we misused it.
        assert( (index1 < itemList.get(criteriaIndex).size()) && (index2 < itemList.get(criteriaIndex).size()) );

        // Swap the contents of the heap cells pointed by the two indices in
        // the selected heap array. (Selection is done with the criteria index)

        Node tmpItem = itemList.get(criteriaIndex).get(index2);
        itemList.get(criteriaIndex).set(index2, itemList.get(criteriaIndex).get(index1));
        itemList.get(criteriaIndex).set(index1, tmpItem);

        // The positions of two references have changed. As the index positions
        // of a specific node is stored inside it, they should be updated as well.

        itemList.get(criteriaIndex).get(index1).setIndex(criteriaIndex, index1);
        itemList.get(criteriaIndex).get(index2).setIndex(criteriaIndex, index2);
    }

    /**
     * Node class encapsulates the data item to be stored and also indices
     * that point to different cells in the available heaps.
     */
    private class Node {

        /** The item data */
        E value;

        /** An array of indices pointing to different heaps. For example,
         indices[0] is an integer representing the array position in heap #0
         that this node resides. 
         */
        private ArrayList<Integer> indices = new ArrayList<Integer>();

        /**
         * Constructs a new node object using the item data.
         * @param e The data to be stored.
         */
        Node(E e) {
            value = e;
        }
        /**
         * Returns the stored value within the node.
         * @return The stored value.
         */
        E getValue() {
            return value;
        }
        /**
         * Adds a new index pointing to a cell in a new heap. The order of
         * the call to this method determines which heap this index will point to.
         * When this method is called for the first time for a Node, this means
         * that the index value is valid for the first heap. FOr the second call,
         * the index value is for the second heap.
         *
         * @param i THe index to the cell in which this Node will reside.
         */
        void addIndex(int i) {
            indices.add(i);
        }
        /**
         * Modifies the index value for a specific heap. This method is called
         * when the position of a Node is changed within a heap. In this case,
         * the heap is identified by the indexToIndex value, and the new index
         * is identified by the index value.
         *
         * @param indexToIndex The heap identifier.
         * @param index The index pointing to the new cell that the Node resides.
         */
        void setIndex(int indexToIndex, int index) {

            indices.set(indexToIndex, index);
        }
    }
}
