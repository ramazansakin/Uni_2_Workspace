/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */


/**
 *
 * @author Owner
 */

import java.util.*;
/**
 * CSE222List class
 * @author Orhan Aksoy, 09104302
 * @param <E> The type to be stored in the list.
 */
public class CSE222List < E > {

    /** The number of items in the list */
    private int listSize = 0;

    private Node < E > head = null;
    private Node < E > tail = null;


    /**
     * Initialize the linked list with node array 
     * length = arrayLength
     * @param arrLen The length of the node array
     */
    public CSE222List (int arrLen) {
        Node.ARRAYLEN = arrLen;
    }
    
    /** Insert an object at the beginning of the list.
        @param item - the item to be added
      */
    public void addFirst(E item) {
        add(0, item);
    }


    /** Insert an object at the end of the list.
        @param item - the item to be added
     */
    public void addLast(E item) {
        add(listSize, item);
    }
    /** Get the first element in the list.
        @return The first element in the list.
     */
    public E getFirst() {
        return head == null ? null : head.GetAt(0);
    }

    /** Get the last element in the list.
        @return The last element in the list.
     */
    public E getLast() {
        return tail == null ? null : tail.GetAt(tail.GetLength()-1);
    }



    /** Add an item at the specified index.
        @param index The index at which the object is to be
               inserted
        @param obj The object to be inserted
        @throws IndexOutOfBoundsException if the index is out
                of range (i < 0 || i > size())
     */
    public void add(int index, E obj) {
        listIterator(index).add(obj);
    }

    /** Get the element at position index.
        @param index Position of item to be retrieved
        @return The item at index
      */
    public E get(int index) {
        return listIterator(index).next();
    }

    /** Return an Iterator to the list
          @return an Itertor tot the list
     */
    public Iterator < E > iterator() {
        return new CSE222ListIterator(0);
    }

    /** Return a ListIterator to the list
        @return a ListItertor to the list
     */
    public ListIterator < E > listIterator() {
        return new CSE222ListIterator(0);
    }

    /** Return a ListIterator that begins at index
        @param index - The position the iteration is to begin
        @return a ListIterator that begins at index
     */
    public ListIterator < E > listIterator(int index) {
        return new CSE222ListIterator(index);
    }
    public void PrintContents() {
        System.out.println("Printing contents of the list:");

        CSE222ListIterator  it = (CSE222ListIterator)listIterator();

        it.PrintContents();
    }

  // Inner Classes
  /**
   * Implementation of the ListIterator interface.
   */
  private class CSE222ListIterator implements ListIterator < E > {

      /** Reference to the next item */
      private Node < E > nextItem = null;
      /** Index into the array in the next item */
      private int arrayIndex = 0;

      /** Reference to list node that contains the last returned item */
      private Node < E > lastNodeReturned = null;
      /** Index of the last returned item in the last list node */
      private int lastArrayIndex = 0;

      /** global index of this iterator containing the count of the items
       * until the pointed item.
       */
      private int globalIndex = 0;

      /**
       * CSE222ListIterator constructor
       * @param index at which the iterator will point.
       */
      public CSE222ListIterator(int index) {
          if ( ( index < 0 ) || ( index > listSize ) ) {
              throw new ArrayIndexOutOfBoundsException("Index out of bounds: " + index);

          }

          Node < E > item = head;
          int counter = 0;
          lastNodeReturned = null;
          
          while ( item != null ) {

              // Check if the index  matches one of the cells of
              // the array.

              if ( index >= counter + item.GetLength()) {

                  // Index is beyond the current array. If the next item
                  // is not null, this means that the list is not ending
                  // here; so keep iterating.

                  if ( item.next != null ) {
                      counter += item.GetLength();
                      item = item.next;
                      continue;
                  }

                  // The next item is null. If the current node
                  // is full, make nextItem null. If not, point to the
                  // next available slot in the node.

                  if ( index - counter >= Node.ARRAYLEN) {
                      arrayIndex = 0;
                      nextItem = null;
                      globalIndex = index;
                      return;
                  }
              }
              arrayIndex = index - counter;
              nextItem = item;
              globalIndex = index;
              return;
          }

          // We should never have come here.

          assert( true ) : "Bad List content";
      }
      /** Returns true if there's a next item
       *
       * @return true if a next item exists
       */
      public boolean hasNext() {

          if ( nextItem == null ) {
              return false;
          }

          if ( arrayIndex  >= nextItem.GetLength() ) {
              return false;
          }

          return true;
      }


    /** Move the iterator forward and return the next item.
        @return The next item in the list
        @throws NoSuchElementException if there is no such object
     */

      public E next() {
          if ( ! hasNext()) {
              throw new NoSuchElementException();
          }

          lastNodeReturned = nextItem;
          lastArrayIndex = arrayIndex;


          if ( arrayIndex + 1 < nextItem.GetLength()) {
              ++arrayIndex;
              ++globalIndex;
              return lastNodeReturned.GetAt(lastArrayIndex);
          }

          nextItem = nextItem.next;
          arrayIndex = 0;
          ++globalIndex;
          return lastNodeReturned.GetAt(lastArrayIndex);
      }

      /** Returns true if there's a previous item
       *
       * @return true if there's a previous item
       */
      public boolean hasPrevious() {

          // If array index is greater than 0, then
          // there's at least 1 item before this item
          // in the same node.

          if ( arrayIndex  > 0 ) {
              return true;
          }

          // if we're pointing to the end of the list,
          // then check the list size

          if ( ( nextItem == null) && ( listSize > 0 ) ) {
              return true;
          }

          return (nextItem.prev != null);

      }

    /** Move the iterator backward and return the previous item.
        @return The previous item in the list
        @throws NoSuchElementException if there is no such object
     */

      public E previous() {
          if ( !hasPrevious()){
              throw new NoSuchElementException();
          }

          --globalIndex;

          if ( arrayIndex > 0 ) {
              --arrayIndex;
          } else {
              if ( nextItem == null ) {
                  nextItem = tail;
              } else {
                  nextItem = nextItem.prev;
              }
              arrayIndex = nextItem.GetLength() - 1;
          }
          lastNodeReturned = nextItem;
          lastArrayIndex = arrayIndex;

          return nextItem.GetAt(arrayIndex);

      }

      /** Returns the global index within the list
       * 
       * @return the global index to the next item
       */
      public int nextIndex() {
          return globalIndex;
      }
      
      /** Returns the global index to the previous
       *  item in the list.
       * @return the global index to the previous item.
       */

      public int previousIndex() {
          return globalIndex - 1;
      }

      /** Insert an item into the list right before the nextItem.
       *  The index will point to the same item
       *  after the insertion.
       *  TODO: array'in basina eklendiginde (veya ilk 2) yeni node
       *  basta olusturulmali.
       *
       * @param obj The item to be inserted.
       */

      public void add(E obj) {

          // If the head is null, then this is the first item in
          // the list. So, initialize the list with this item.

          if ( head == null ) {
              head = new Node < E > ();
              tail = head;
              head.AddItem(obj);
              nextItem = head;
              arrayIndex = 0;
          } else if ( nextItem != null ) {

              // Insert the item at the current location.

              E tmpItem = nextItem.InsertAt(arrayIndex, obj);

              // If the array is full within the node, InsertAt returns
              // the pushed out element from the array after insertion.

              if ( tmpItem != null ) {
                
                  // If there's an empty cell in the next node, insert it
                  // at the beginning of this node.

                  if ( ( nextItem.next != null ) && (nextItem.next.GetLength() < Node.ARRAYLEN-1) ){
                      nextItem.next.InsertAt(0, tmpItem);
                  } else {
                      // Create a new node between the next node and its next.
                      // This new node will contain a single element, which is
                      // the one pushed out during insertion.

                      Node < E > newNode = new Node <E> ();
                      newNode.AddItem(tmpItem);

                      newNode.next = nextItem.next;
                      if (nextItem.next != null) {
                          nextItem.next.prev = newNode;
                      } else {
                          // If the node we've created is the last node in the list,
                          // make it the 'tail'.
                          tail = newNode;
                      }

                      nextItem.next = newNode;
                      newNode.prev = nextItem;
                      
                      
                  }
              } 
          } else { // nextItem is null
              
              Node < E > newNode = new Node < E >();
              newNode.AddItem(obj);
              tail.next = newNode;
              newNode.prev = tail;
              tail  = newNode;
              nextItem = tail;
              arrayIndex = 0;

              
          }
          // after the addition, update the index.
          if ( ++arrayIndex >= Node.ARRAYLEN) {
              nextItem = nextItem.next;
              arrayIndex = 0;
          }
          ++globalIndex;
          ++listSize;
          lastNodeReturned = null;

      }
      /** Replace the last item returned with a new value
       *
       * @param item The new value of the item
       * @throws IllegalStateException if next or previous
       *  was not called prior to calling this method
       */

      public void set(E item) {
          if ( lastNodeReturned == null ) {
              throw new IllegalStateException();
          }
          lastNodeReturned.SetAt(lastArrayIndex, item);
      }




    /** Remove the last item returned. This can only be
     *  done once per call to next or previous.
     *  @throws IllegalStateException if next or previous
     *  was not called prior to calling this method
     */
      public void remove() {
          if (lastNodeReturned == null) {
              throw new IllegalStateException();
          }

          // Remove the item from the node array

          lastNodeReturned.RemoveAt(lastArrayIndex);
          --globalIndex;
          --listSize;

          // If the removed item is in the same array as our next item's array,
          // then we should move back in order keep pointing to the same item.

          if ( nextItem == lastNodeReturned ) {

              if ( arrayIndex == lastArrayIndex ) {
                  ++globalIndex;
              } else if ( arrayIndex > 0 ) { // This check is for post-prev op ??? TODO
                  --arrayIndex;
              }
          }

          // Check if the removed item was the
          // only item in the node.

          if ( lastNodeReturned.GetLength() == 0) {

              // The node will be removed from the list.

              // Remove the node's link to the next node.

              if ( lastNodeReturned.next == null ) {
                  tail = lastNodeReturned.prev;
                  if ( tail == null ) {
                      head = null;
                  } else {
                      tail.next = null;
                  }
              } else {
                  lastNodeReturned.next.prev = lastNodeReturned.prev;
              }

              // Remove the node's link to the previous node.

              if ( lastNodeReturned.prev == null ) {
                  head = lastNodeReturned.next;
                  if ( head != null ) {
                      head.prev = null;
                  } else {
                      tail = null;
                  }
              } else {
                  lastNodeReturned.prev.next = lastNodeReturned.next;
              }
          }
          lastNodeReturned = null;
      }

      public void PrintContents() {
          while ( nextItem != null) {
              System.out.println("Printing node (Length = " + nextItem.GetLength() + ") ==================");
              for (int i=0; i< nextItem.GetLength(); ++i) {
                  System.out.println("Array[" + i + "] = " + nextItem.GetAt(i));
              }
              System.out.println("Node ends =====================================");
              nextItem  = nextItem.next;
          }
      
      }

  }


  /** A Node is the building block for a double-linked list.
   */
  private static class Node < E > {
    /** The value array. */
    private E[] valArray ;
    /** Number of items in the array */
    private int valLen;
    /** Max number of items of the array */
    private static int ARRAYLEN = 1;

    /** The link to the next node. */
    private Node < E > next = null;

    /** The link to the previous node. */
    private Node < E > prev = null;

    /** Construct a node with the given node array length.
        @param arrayLen node Array Length
     */
    private Node() {
      valArray = (E[]) new Object[ARRAYLEN];
      valLen = 0;
    }

    /** Add a data item to the end of the node array
     * @param data The data to be added to the node.
     */
    private void AddItem(E data) {
        if ( valLen >= ARRAYLEN ) {
            throw new ArrayIndexOutOfBoundsException("Node Array full");
        }

        valArray[valLen++] = data;

    }
    /** Remove a data item from the node array
     *
     * @param idx The index to the item to be removed
     * @return THe removed item.
     */
    private E RemoveAt(int idx) {
        
        E retVal = GetAt(idx);

        --valLen;

        for ( int i = idx; i < valLen; ++i) {
            valArray[i] = valArray[i+1];
        }

        return retVal;
    }
    /** Get the data at a specific location
     *
     * @param idx array position
     * @return the value at the specified position
     * @throws ArrayIndexOutOfBoundsException if index is larger than the array length
     */
    private E GetAt(int idx) {
        if ( ( idx >= valLen ) || ( idx < 0 ) ) {
            throw new ArrayIndexOutOfBoundsException("Index out of bounds: " + idx);
        }
        return valArray[idx];

    }

    /** Get the data at a specific location
     *
     * @param idx array position
     * @param obj value to be set at the specified position
     * @throws ArrayIndexOutOfBoundsException if index is larger than the array length
     */
    private void SetAt(int idx, E obj) {
        if ( ( idx >= valLen ) || ( idx < 0 ) ) {
            throw new ArrayIndexOutOfBoundsException("Index out of bounds: " + idx);
        }
        valArray[idx] = obj;
    }

    /** Insert a data item at a specific location in the node array
     *
     * @param idx The index to the array location to be inserted at
     * @data The data item to be inserted
     * @return If the array was already full, the overflown item; else null.
     */

    private E InsertAt(int idx, E data) {
        if ( ( idx >= ARRAYLEN ) || ( idx < 0 ) ) {
            throw new ArrayIndexOutOfBoundsException("Index out of bounds: " + idx);
        }

        E retVal = null;

        // If the array is full, then the last item of the array will
        // be pushed out. This data item is returned.

        if ( valLen == ARRAYLEN) {
            retVal = valArray[valLen-1];
        }

        for (int i=valLen; i>idx; --i) {
            if ( i == ARRAYLEN ) {
                continue;
            }
            valArray[i] = valArray[i-1];
        }

        valArray[idx] = data;

        if (valLen < ARRAYLEN ) {
            ++valLen;
        }

        return retVal;
    }

    /** Returns the number of items in the node
     *
     * @return number of items in the node array
     */

    private int GetLength() {
        return valLen;
    }

  }
}

