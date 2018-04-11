/*
 * CSE222 HW #3
 * Linked list of arrays implementation
 */

/**
 *
 * @author Orhan Aksoy, 09104302
 */
import java.util.*;

public class Main {

    /**
     * Main Function
     * Makes 3 tests: Insertion, REmove and Get/Set method tests
     * Uses iterators in different places.
     * @param args the command line arguments
     */
    public static void main(String[] args) {

        CSE222List<String> list2 = new CSE222List<String>(2);
        TestInsertion(list2);
        TestRemove(list2);
        TestGetMethods(list2);
        
   }
   /**
    * Tests the Get methods of the list class and the set method
    * of its list iterator.
    * @param list is a reference to a CSE222List object
    */
    public static void TestGetMethods(CSE222List list) {
        System.out.println("--------- GET/SET METHOD TESTS ---------------------------------");
        PrintList(list);
        System.out.println("First item in the list: " + list.getFirst());
        System.out.println("Last item in the list: " + list.getLast());
        System.out.println("Item at index 1 in the list: " + list.get(1));

        System.out.println("Set item at index 0 to Forty");
        ListIterator it = list.listIterator(0);
        it.next();
        it.set("Forty");
        PrintList(list);
        System.out.println("--------- END OF GET/SET METHOD TESTS --------------------------");
    }

   /**
    * Tests the Remove method of the list class in various
    * iterator positions, before and after prev and next calls.
    * @param list is a reference to a CSE222List object
    */

    public static void TestRemove(CSE222List list) {
        System.out.println("--------- REMOVE TESTS ---------------------------------");
        System.out.println("From the beginning, next, next, and remove:");
        ListIterator it = list.listIterator();
        it.next();
        it.next();
        it.remove();
        PrintList(list);
        //list.PrintContents();
        System.out.println("--------------------------------------------------------");
        System.out.println("From current location, next, and remove:");
        it.next();
        it.remove();
        PrintList(list);
        //list.PrintContents();
        System.out.println("--------------------------------------------------------");
        ListIterator it2 = list.listIterator(1);
        System.out.println("Start from index 1, next, prev and remove:");
        it2.next();
        it2.previous();
        it2.remove();
        //list.PrintContents();
        PrintList(list);

        System.out.println("--------- END OF REMOVE TESTS ---------------------------");

    }
   /**
    * Tests the Insertion methods of the list class
    * @param list is a reference to a CSE222List object
    */
    public static void TestInsertion(CSE222List list) {
        System.out.println("--------- INSERTION TESTS ---------------------------------");
        System.out.println("addFirst(Tom), addLast(Dick), addFirst(Ann), ");
        System.out.println("addLast(Harry), addFirst(Sam), add(4, Sharon),");

        list.addFirst("Tom");
        list.addLast("Dick");
        list.addFirst("Ann");
        list.addLast("Harry");
        list.addLast("Sam");
        list.add(4, "Sharon");
        //list.PrintContents();
        PrintList(list);


        System.out.println("--------- END OF INSERTION TESTS ---------------------------");

    }
    /**
     * PrintList function prints out the list content..
     * @param list is a reference to a CSE222List object
     */

    public static void PrintList(CSE222List list) {
        ListIterator it = list.listIterator();
        while ( it.hasNext()) {
            System.out.println("Current index: " + it.nextIndex() + " , current item: " + it.next());
        }
    }

}


