
package pkg111044069hw06;

/**
 * @author ramazan
 */
public interface PriorityQueue<E>{
    
    // Insert an item into the priority queue.
    boolean offer(E item);
    /* Removes an item from the priority queue and 
      sorts the heap spesific priarity  throws NoSuchElemnetException*/
    E remove();
    
    /* Removes an item from the priority queue and 
      sorts the heap spesific priarity */
    E poll();
    
    /* take the root's data without removing it */
    E peek();
    
    /* take the root's data without removing it throws NoSuchElementException */
    E element();
    
}
