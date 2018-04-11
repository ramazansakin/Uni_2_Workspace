/**
 * Priority Queue driver application.
 *
 * @author Orhan Aksoy - 09104302
 */
public class Main {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        PriQueue<Integer> q = new PriQueue();

        // Test1 : Add items with same priority, and observe that the
        // output is in the same order.

        System.out.println("Test1 ======================");

        q.offer(5, 1);
        q.offer(7, 1);
        q.offer(8, 1);

        while (q.peek() != null) {
            System.out.println("Test1: Dequeue: " + q.poll());
        }

        // Test2 : Add items with different priorities, and observe that the
        // output is in the order of priorities, irrespective of the order
        // that they arrive

        System.out.println("Test2 ======================");

        q.offer(5, 1);
        q.offer(7, 5);
        q.offer(8, 3);

        while (q.peek() != null) {
            System.out.println("Test2: Dequeue: " + q.poll());
        }

        // Test3 : Add items with the same priority, and observe that the
        // circular queue for the corresponding queue gets its size doubled
        // when the boundary is reached. The initial size is 4, so add 5 items
        // to get the reallocation mechanism work.

        System.out.println("Test3 ======================");

        q.offer(5, 3);
        q.offer(10, 3);
        q.offer(15, 3);
        q.offer(22, 3);
        q.offer(44, 3);

        while (q.peek() != null) {
            System.out.println("Test3: Dequeue: " + q.poll());
        }
        // Test4 :Observe the thrown exception in case the methods 'element' and
        // 'remove' are called with empty queues.
        System.out.println("Test4 ======================");

        try {
            q.offer(5, 3);
            q.remove();
            q.remove();
        } catch (Exception e) {
            System.out.println("Exception received during remove() : " + e.getMessage());
        }

        try {
            q.offer(5, 3);
            q.remove();
            q.element();
        } catch (Exception e) {
            System.out.println("Exception received during element() : " + e.getMessage());
        }

        // Test5 : Observe that the functions 'peek' and 'poll' return null when
        // the queue is empty

        System.out.println("Test5 ======================");

        System.out.println ("q.peek() returned " + q.peek());
        System.out.println ("q.poll() returned " + q.poll());

        // Test6 : Add different items with different priorities and observe that
        // the highest priorities come first, with the correct arriving order

        System.out.println("Test6 ======================");
        q.offer(3, 6);
        q.offer(4, 3);
        q.offer(5, 6);
        q.offer(6, 3);
        q.offer(300, 14);
        q.offer(7, 6);
        q.offer(8, 3);
        q.offer(9, 6);
        q.offer(100, 9);
        q.offer(10, 3);
        q.offer(11, 6);
        q.offer(12, 3);
        q.offer(200, 12);
        q.offer(13, 6);
        q.offer(14, 3);
        q.offer(400, 14);

        while (q.peek() != null) {
            System.out.println("Test 6 : Dequeue : " + q.poll());
        }
    }

}
