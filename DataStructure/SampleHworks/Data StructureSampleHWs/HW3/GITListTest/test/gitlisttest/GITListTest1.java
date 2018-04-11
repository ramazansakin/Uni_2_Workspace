/**
 * CSE222_HW03_101044044 
 * --------------------------------
 * Class GITListTest1
 * tests all methods of GITList class.
 * --------------------------------
 *
 * @author Samet Sait Talayhan
 */
package gitlisttest;

import java.util.Iterator;
import java.util.ListIterator;
import org.junit.After;
import org.junit.AfterClass;
import org.junit.Before;
import org.junit.BeforeClass;
import org.junit.Test;
import static org.junit.Assert.*;


public class GITListTest1 {

    /**
     * Test of size method, of class GITList.
     */
    @Test
    public void testSize() {
        System.out.println("size");
        GITList instance = new GITList();
        int expResult = 0;
        int result = instance.size();
        assertEquals(expResult, result);
        // TODO review the generated test code and remove the default call to fail.
//        fail("The test case is a prototype.");
    }

    /**
     * Test of clear method, of class GITList.
     */
    @Test
    public void testClear() {
        System.out.println("clear");
        GITList instance = new GITList();
        instance.clear();
        // TODO review the generated test code and remove the default call to fail.
//        fail("The test case is a prototype.");
    }

    /**
     * Test of addFirst method, of class GITList.
     */
    @Test
    public void testAddFirst() {
        System.out.println("addFirst");
        Object item = null;
        GITList instance = new GITList();
        instance.addFirst(item);
        // TODO review the generated test code and remove the default call to fail.
//        fail("The test case is a prototype.");
    }

    /**
     * Test of addLast method, of class GITList.
     */
    @Test
    public void testAddLast() {
        System.out.println("addLast");
        Object item = null;
        GITList instance = new GITList();
        instance.addLast(item);
        // TODO review the generated test code and remove the default call to fail.
//        fail("The test case is a prototype.");
    }

    /**
     * Test of getFirst method, of class GITList.
     */
    @Test
    public void testGetFirst() {
        System.out.println("getFirst");
        GITList<Integer> instance = new GITList<>();
        instance.addFirst(99);
        Integer expResult = 99;
        Integer result;
        result = instance.getFirst();
        assertEquals(expResult, result);
        // TODO review the generated test code and remove the default call to fail.
//        fail("The test case is a prototype.");
    }

    /**
     * Test of getLast method, of class GITList.
     */
    @Test
    public void testGetLast() {
        System.out.println("getLast");
        GITList<Integer> instance = new GITList<>();
        instance.addLast(99);
        Object expResult = 99;
        Object result = instance.getLast();
        assertEquals(expResult, result);
        // TODO review the generated test code and remove the default call to fail.
//        fail("The test case is a prototype.");
    }

    /**
     * Test of iterator method, of class GITList.
     */
    @Test
    public void testIterator() {
        System.out.println("iterator");
        GITList<Integer> instance = new GITList<>();
        Iterator expResult;
        expResult = instance.iterator();
        Iterator result = instance.iterator();
        assertEquals(expResult, result);
        // TODO review the generated test code and remove the default call to fail.
//        fail("The test case is a prototype.");
    }

    /**
     * Test of listIterator method, of class GITList.
     */
    @Test
    public void testListIterator_0args() {
        System.out.println("listIterator");
        GITList instance = new GITList();
        ListIterator expResult = null;
        ListIterator result = instance.listIterator();
        assertEquals(expResult, result);
        // TODO review the generated test code and remove the default call to fail.
//        fail("The test case is a prototype.");
    }

    /**
     * Test of listIterator method, of class GITList.
     */
    @Test
    public void testListIterator_int() {
        System.out.println("listIterator");
        int index = 0;
        GITList instance = new GITList();
        ListIterator expResult = null;
        ListIterator result = instance.listIterator(index);
        assertEquals(expResult, result);
        // TODO review the generated test code and remove the default call to fail.
//        fail("The test case is a prototype.");
    }

    /**
     * Test of add method, of class GITList.
     */
    @Test
    public void testAdd() {
        System.out.println("add");
        int index = 0;
        Object obj = null;
        GITList instance = new GITList();
        instance.add(index, obj);
        // TODO review the generated test code and remove the default call to fail.
//        fail("The test case is a prototype.");
    }

    /**
     * Test of get method, of class GITList.
     */
    @Test
    public void testGet() {
        System.out.println("get");
        int index = 0;
        GITList<Integer> instance = new GITList<>();
        instance.add(index, 99);
        Object expResult = 99;
        Object result = instance.get(index);
        assertEquals(expResult, result);
        // TODO review the generated test code and remove the default call to fail.
//        fail("The test case is a prototype.");
    }

    /**
     * Test of display method, of class GITList.
     */
    @Test
    public void testDisplay() {
        System.out.println("display");
        GITList instance = new GITList();
        instance.display();
        // TODO review the generated test code and remove the default call to fail.
//        fail("The test case is a prototype.");
    }
}
