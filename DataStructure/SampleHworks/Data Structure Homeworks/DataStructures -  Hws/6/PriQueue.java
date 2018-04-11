import java.util.*;
/**
 * Priority Queue class definition.
 *
 * @author Orhan Aksoy - 09104302
 */
public class PriQueue < E >  {

    /** an ordered list of queues each of which represent a queue for a specific priority */
    private ArrayList< CircularQueue <E> > queueList = new ArrayList < CircularQueue<E> > ();


    /**
     * Inserts item at the rear of the queue whose priority matches the input
     * priority. If no queue matches the input priority, a new one is created.
     *
     * @param item The item to be enqueued.
     * @param priority The priority of the item.
     * @return True if successfull.
     */
    public boolean offer (E item, int priority) {

        // If the queue list is 0, create a single queue and use it.

        if (queueList.size() == 0) {
            queueList.add(new CircularQueue(priority));
            queueList.get(0).enqueue(item);
            return true;
        }

        // Find the appropriate queue to put the item into.
        // The function 'getQueue' tries to find a queue for the input priority.
        // If it finds, returns it. Else, creates a new queue for that priority
        // and returns it.
        // The queue list is ordered according to the priorities, so the insertion
        // is a recursive process. So, we provide the range of queues to the
        // qetQueue function - in this initial case, the first and last queue
        // indices of the list

        getQueue(priority, 0, queueList.size()-1).enqueue(item);
        return true;
    }

    /**
     * Returns the item at the front of the queue with the highest priority and
     * removes it. If the queue is empty, throws
     * NoSuchElementException
     *
     * @return The item at the front of the queue.
     * @throws NoSuchElementException if the queue is empty.
     */
    public E remove() throws NoSuchElementException {
        ListIterator<CircularQueue<E>> it = queueList.listIterator();

        // Go through all queue's in the list to match the priority.
        // When a non-empty queue with the same priority is found, the first
        // item in the queue is removed and returned to the caller.
        while (it.hasNext()) {
            CircularQueue q = it.next();
            if ( q.isEmpty() == false ) {
                E e = (E) q.dequeue();// TODO : Neden cast????


                return e;
            }
        }
        throw new NoSuchElementException();
    }
    /**
     * Returns the item at the front of the queue with the highest priority and
     * removes it. If the queue is empty, returns null.
     *
     * @return The item at the front of the queue. If the queue is empty,
     * returns null.
     */
    public E poll() {
        ListIterator<CircularQueue<E>> it = queueList.listIterator();

        while (it.hasNext()) {
            CircularQueue q = it.next();
            if ( q.isEmpty() == false ) {
                E e = (E) q.dequeue();// TODO : Neden cast????

                return e;
            }
        }
        return null;

    }
    /**
     * Peeks at the front of the queue with the hightes priority,
     * and returns it if the queue is not
     * empty. If it is empty, returns null
     *
     * @return The item at the front of the queue. If the queue is empty,
     * returns null.
     */
    public E peek() {
        for (CircularQueue q : queueList) {
            if ( q.isEmpty() == false ) {
                return (E) q.peek(); // TODO : Neden cast????
            }
        }
        return null;

    }
    /**
     * Peeks at the front of the queue with the highest priority
     * and returns it if the queue is not empty.
     * If the queue is empty, throws NoSuchElementException
     * @return THe item at the front of the queue.
     * @throws NoSuchELementException if the queue is empty.
     */
    public E element() throws NoSuchElementException {
        for (CircularQueue q : queueList) {
            if ( q.isEmpty() == false ) {
                return (E) q.dequeue(); 
            }
        }
        throw new NoSuchElementException();

    }
    
    /**
     * Searches the ordered list of Circular Queues to match the correct
     * priority. To do it, makes a binary search. During the search, if
     * it finds out that this is the first item with this priority, then it
     * creates a new queue with this priority, and inserts it in the list,
     * keeping the list ordered.
     *
     * returns a queue reference for the specified priority.
     * @param pri The priority of the queue
     * @param begin the beginning of the range of priorities
     * @param end the end of the range of priorities
     */

    private CircularQueue getQueue(int pri, int begin, int end) {

        // Check if the priority matches the queue with the smallest priority

        if ( queueList.get(begin).priority == pri ) {
            return queueList.get(begin);
        } else if (pri > queueList.get(begin).priority) {
            // This item's priority is higher than the highest queue.
            CircularQueue<E> q = new CircularQueue(pri);
            queueList.add(0, q);
            return q;
        }

        // Check if the priority matches the queue with the highest priority
        if ( queueList.get(end).priority == pri ) {
            return queueList.get(end);
        } else if (pri < queueList.get(end).priority) {
            // This item's priority is lower than the lowest queue.
            CircularQueue<E> q = new CircularQueue(pri);
            queueList.add(q);
            return q;
        }


        // FInd the queue in the middle.

        int mid = begin + ( end - begin ) / 2;

        // IF the priority of the queue in the middle matches us, return it/
        if ( queueList.get(mid).priority == pri ) {
            return queueList.get(mid);
        }

        if ( queueList.get(mid).priority < pri ) {
            // We're going to check the lower half. So, first check if the
            // range in the lower half is zero. If so, this means that there's
            // queue with this priority. So ,create and return it, keeping the
            // order of the list.
            if ( begin == mid - 1 ) {
                CircularQueue<E> q = new CircularQueue(pri);
                queueList.add(mid, q);
                return q;
            }
            // Make the recursive call in the lower half.
            return getQueue(pri, begin, mid - 1);
        } else {
            // Check the upper half and do the same thing. If there's no such
            // queue, create a new one and return it.
            if ( end == mid + 1 ) {
                CircularQueue<E> q = new CircularQueue(pri);
                queueList.add(end, q);
                return q;
            }
            // Make the recursive call in the upper half.
            return getQueue(pri, mid + 1, end);
        }

    }

    /**
     * Circular Queue implementation.
     * @param <E> THe type of the items in the queue.
     */
    private class CircularQueue<E> {
        /** THe queue itself */
        private E queue []  = (E[]) new Object[4];
        /** The write pointer */
        private int writePtr;
        /** The read pointer */
        private int readPtr;
        /** THe priority this queue belongs to */
        private int priority;
        

        /**
         * Initializes the queue.
         * Note that the initial size of the queue is 10 by default.
         * @param pri Priority of this queue.
         */
        public CircularQueue(int pri) {
            writePtr = 0;
            readPtr = 0;
            priority = pri;

        }
        /**
         * Enqueue a new item in the queue. First, puts the item in the next
         * available location. Then checks if the queue is full. If so,
         * reallocates the queue.
         * @param item
         */
        public void enqueue(E item) {
            // Put the item in the next available location pointed by the
            // write pointer. THen, increment the write pointer location.
            queue[writePtr++] = item;

            // Check if we have reached the end of the array. If so, go back
            // to location 0.
            if ( writePtr == queue.length) {
                writePtr = 0;
            }

            // After incrementing the write pointer, if we meet the read pointer,
            // this means that the whole circular queue is full. SO, we create
            // a new queue with double size, and initialize it with the current
            // queue content.

            if ( writePtr == readPtr ) {

                // Create the new array with size doubled.
                E newQueue []  = (E[]) new Object[2*queue.length];

                // Copy the data starting from the read pointer until the end
                // of the queue.
                for (int i = readPtr; i<queue.length; ++i) {
                    newQueue[i-readPtr] = queue[i];
                }
                // Now, copy the data starting from 0 until the write pointer
                for (int i=0; i<writePtr; ++i) {
                    newQueue[queue.length - readPtr + i] = queue[i];
                }
                // We have copied the whole ring. Since we moved the data starting from
                // the read pointer to the beginning of the new array, make the read
                // pointer 0. Write pointer will be the length of the old array (recall
                // that we initiated this process when the old queue got full)
                readPtr = 0;
                writePtr = queue.length;
                queue = newQueue;
            }

        }


        /**
         * Dequeues item from the end of the circular queue.
         * @return Item if exists, null else.
         */
        public E dequeue() {
            if ( readPtr == writePtr ) {
                return null;
            }
            E retVal = queue[readPtr++];
            // We're at the end of the array, go back to index 0.
            if ( readPtr == queue.length) {
                readPtr = 0;
            }
            return retVal;

        }
        /**
         * Peeks at the front of the queue and returns it.
         * @return null if queue empty.
         */
        public E peek() {
            if ( readPtr == writePtr ) {
                return null;
            }
            return queue[readPtr];
        }
        /**
         * Checks if the queue is empty
         * @return True if the queue is empty.
         */
        public boolean isEmpty() {
            return writePtr == readPtr;
        }
 
    }

}