/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package lists;

import java.util.Iterator;
import java.util.ListIterator;

/**
 *
 * @author ramazan
 */
public class ListTest {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        GITArrayList<String> newStringArrList = new GITArrayList<String>();
        GITArrayList<String> otherList = new GITArrayList<String>();
        GITLinkedList<String> myGITlinked = new GITLinkedList<>();
        GITLinkedList<String> myGITlinked2 = new GITLinkedList<>();
        GITLinkedList<String> myGITlinked3 = new GITLinkedList<>();

        
        try{
            System.out.println("-------------  UNIT TESTING  -----------");
            System.out.println("GIT LinkedList methods Testing ");
            
            // Unit Testing for add , addFirst and get methods
            newStringArrList.add(0, "Ramazan");
            newStringArrList.add(1,"Fatih");
            newStringArrList.add(2, "Ensar");
            newStringArrList.add(1, "Ali");
            newStringArrList.add(4, "Selim");
            System.out.println("Add method");
            for( Object it: newStringArrList )
                System.out.println(it);
            System.out.println("\n");
            System.out.println("After addFirst method  'Karen'");
            newStringArrList.addFirst("Karen");
            
            for( Object it: newStringArrList)
                System.out.println(it);    
            
            System.out.println("\n");
            System.out.println("get() method for index of 3");
            System.out.println(newStringArrList.get(3));
            System.out.println("\n");
            System.out.println("getFirst() method :");
            System.out.println(newStringArrList.getFirst());
            System.out.println("\n");
            System.out.println("getLast() method :");
            System.out.println(newStringArrList.getLast());
            System.out.println("\n");
            System.out.println("Size of the list is "+newStringArrList.getSize());
            System.out.println("\n");
            System.out.println("GITlinkedList iterator :");
            Iterator<String> itr = newStringArrList.iterator();
            
            for( int i=0; itr.hasNext(); )
                System.out.println(itr.next());
            
            System.out.println("\n");
            System.out.println("GITlinkedList ListIterator at begining of index 2:(next - hasNext)");
            Iterator<String> iter = newStringArrList.listIterator(2);
            
            for( int i=0; iter.hasNext(); )
                System.out.println(iter.next());
            
            System.out.println("\n");
            System.out.println("GITlinkedList ListIterator at begining of index 4: (previous - hasPrevious)");
            ListIterator<String> iter2 = newStringArrList.listIterator(4);
            
            for( int i=0; iter2.hasPrevious(); )
                System.out.println(iter2.previous());
            
            System.out.println("GITlinkedList ListIterator(0) set, add and remove methods testing");
            ListIterator<String> iter3 = newStringArrList.listIterator(0);
            
            System.out.println("remove first element");
            System.out.println("if the iter called no next or preious, will be thrown IllegalStsteException by set or remove method");
            System.out.println("After listIterator next one time and remove");
            
            iter3.next();
            iter3.remove();
            System.out.println("next and remove goes the iterator to index of 2");
            for( int i=0; iter3.hasNext(); )
                System.out.println(iter3.next());
            
            System.out.println("\n");
            System.out.println("Other list for testing addAll, removeAll, containsAll and retainsAll:");
            
            otherList.add(0, "Kerem");
            otherList.add(1, "Kerim");
            otherList.add(2, "Kenan");
            otherList.add(2, "Sinan");
            otherList.add(2, "Ali");
            
            for( int i=0; i<otherList.getSize(); ++i )
                System.out.println(otherList.get(i));
            
            System.out.println("\n");
            System.out.println("addAll() method Testing:");
            newStringArrList.addAll(otherList);
            
            for( int i=0; i<newStringArrList.getSize(); ++i )
                System.out.println(newStringArrList.get(i));
            
            System.out.println("\n");
            System.out.println("removeAll() method Testing:");
            newStringArrList.removeAll(otherList);
            
            for( int i=0; i<newStringArrList.getSize(); ++i )
                System.out.println(newStringArrList.get(i));
            
            System.out.println("\n");
            System.out.println("containsAll() method Testing Result ");
            System.out.println(newStringArrList.containsAll(otherList)+"for first and second GITArrayList");
            
            System.out.println("\n");
            System.out.println("Add an element to seond ArrayList -> 'Ramazan'");
            otherList.add(otherList.getSize(), "Ramazan");
            
            System.out.println("First GITArrayList ");
            for( int i=0; i<newStringArrList.getSize(); ++i )
                System.out.println(newStringArrList.get(i));
            
            System.out.println("\n");
            System.out.println("Second GITArrayList ");
            for( int i=0; i<otherList.getSize(); ++i )
                System.out.println(otherList.get(i));
            
            System.out.println("\n");
            System.out.println("retainsAll() method Testing ");
            
            newStringArrList.retainAll(otherList);
            for( int i=0; i<newStringArrList.getSize(); ++i )
                System.out.println(newStringArrList.get(i));
            
            
            System.out.println("\n");
            System.out.println("****** GITLinkedList Testing *******");
            myGITlinked.add(0, "Ramazan");
            myGITlinked.add(1, "Bayram");
            myGITlinked.add(2, "Fatih");
            myGITlinked.add(3, "Burak");
            myGITlinked.add(0, "Hakkı");
            
            System.out.println("First List");
            for( Object it: myGITlinked ){
                System.out.println(it);
            }
            
            myGITlinked2.add(0, "Ismail");
            myGITlinked2.add(1, "Fahri");
            myGITlinked2.add(2, "Bilal");
            myGITlinked2.add(3, "Ibrahim");
            
            System.out.println("\n");
            System.out.println("Second List");
            for( int i=0; i<4; ++i )
                System.out.println(myGITlinked2.get(i));
            
            myGITlinked.addAll(myGITlinked2);
            
            System.out.println("After AddAll method :");
            for( Object it: myGITlinked )
                System.out.println(it);
            
            System.out.println("\n");
            System.out.println("Third GITLinkedList: ");
            myGITlinked3.add(0, "Ramazan");
            myGITlinked3.add(1, "Bayram");
            myGITlinked3.add(2, "Fatih");
            myGITlinked3.add(3, "Burak");
            myGITlinked3.add(4, "Habib");
            for( Object it: myGITlinked3 )
                System.out.println(it);
            
            System.out.println("\n");
            System.out.println("Testing containsAll method between first GITLL and third GITLL status ");
            boolean status2 = myGITlinked.containsAll(myGITlinked3);
            System.out.println(status2);
            
            // removeAll method testing
            System.out.println("\n");
            System.out.println("RemoveAll method Testing between first and third GITLL");
            
            myGITlinked.removeAll(myGITlinked3);
            //myGITlinked.retainAll(myGITlinked3);
            
            for( Object it: myGITlinked )
                System.out.println(it);
            
            System.out.println("\n");
            System.out.println("Other example for Testing");
            GITArrayList<Integer> intList = new GITArrayList<>();
            
            System.out.println("First GITLL array and Iterator testing with for-each loop:");
            intList.add(0, 18);
            intList.add(1, 30);
            intList.add(2, 46);
            intList.add(3, 21);
            intList.add(4, 70);
            intList.add(5, 65);
            intList.add(6, 40);
            
            System.out.println("The size of the first GITLLarray is "+intList.getSize());
            for( Object data: intList)
                System.out.println(data);
            
            System.out.println("Last item"+intList.getLast());
            System.out.println("First item"+intList.getFirst());
            
            System.out.println("\n");
            System.out.println("Second GITLL array");
            GITArrayList<Integer> intList2 = new GITArrayList<>();
            intList2.add(0, 4);
            intList2.add(1, 8);
            intList2.add(2, 12);
            intList2.add(3, 45);
            for( Object data: intList2)
                System.out.println(data);
            
            System.out.println("\n");
            System.out.println("Third GITLL array: ");
            GITArrayList<Integer> intList3 = new GITArrayList<>();
            intList3.add(0, 15);
            intList3.add(1, 30);
            intList3.add(2, 45);
            intList3.add(3, 12);
            
            for( Object data: intList3)
                System.out.println(data);
            System.out.println("addAll method for first and second GITLL arrarys:");
            intList.addAll(intList2);
            for( Object data: intList)
                System.out.println(data);
            
            System.out.println("\n");
            System.out.println("After containsAl method for first GITLL and third GITLL");
            System.out.println("Result is "+intList.containsAll(intList3));
            
            System.out.println("\n");
            System.out.println("addAll GITLL 2 and GITLL1");
            intList.addAll(intList2);
            
            for( Object data: intList)
                System.out.println(data);
            
            System.out.println("\n");
            System.out.println("removeAll for GITLL1 and GITLL3");
            intList.removeAll(intList3);
            
            for( Object data: intList)
                System.out.println(data);
            
            intList.retainAll(intList3);
            System.out.println("\n");
            System.out.println("retainsAll method for GITLL1 and 3");
            for( Object data: intList)
                System.out.println( data);
            
            System.out.println("--------------  END OF TESTING ------------");
        }catch(ArrayIndexOutOfBoundsException e){   // if the index is out of bounds
            System.out.printf("Invalid Index!!  %s\n", e.toString());
        
        }catch(Exception e){    //catch for other exceptions
            System.err.printf("Exception is %s\n",e.toString());
        }
        
    }
}

