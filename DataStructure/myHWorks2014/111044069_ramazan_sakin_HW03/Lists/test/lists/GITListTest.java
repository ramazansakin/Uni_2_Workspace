/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package lists;

import java.util.Iterator;
import java.util.ListIterator;
import org.junit.After;
import org.junit.AfterClass;
import org.junit.Before;
import org.junit.BeforeClass;
import org.junit.Test;
import static org.junit.Assert.*;

/**
 *
 * @author ramazan
 */
public class GITListTest {
    
    public GITListTest() {
    }
    
    @BeforeClass
    public static void setUpClass() {
    }
    
    @AfterClass
    public static void tearDownClass() {
    }
    
    @Before
    public void setUp() {
    }
    
    @After
    public void tearDown() {
    }

    /**
     * Test of add method, of class GITList.
     */
    @Test
    public void testAdd() {
        System.out.println("add");
        int index = 0;
        Object obj = null;
        GITList instance = new GITListImpl();
        instance.add(index, obj);
       
    }

    /**
     * Test of addFirst method, of class GITList.
     */
    @Test
    public void testAddFirst() {
        System.out.println("addFirst");
        Object item = null;
        GITList instance = new GITListImpl();
        instance.addFirst(item);
        
    }

    /**
     * Test of get method, of class GITList.
     */
    @Test
    public void testGet() {
        System.out.println("get");
        int index = 0;
        GITList instance = new GITListImpl();
        Object expResult = null;
        Object result = instance.get(index);
        assertEquals(expResult, result);
        
    }

    /**
     * Test of getFirst method, of class GITList.
     */
    @Test
    public void testGetFirst() {
        System.out.println("getFirst");
        GITList instance = new GITListImpl();
        Object expResult = null;
        Object result = instance.getFirst();
        assertEquals(expResult, result);
    }

    /**
     * Test of getLast method, of class GITList.
     */
    @Test
    public void testGetLast() {
        System.out.println("getLast");
        GITList instance = new GITListImpl();
        Object expResult = null;
        Object result = instance.getLast();
        assertEquals(expResult, result);
    }

    /**
     * Test of iterator method, of class GITList.
     */
    @Test
    public void testIterator() {
        System.out.println("iterator");
        GITList instance = new GITListImpl();
        Iterator expResult = null;
        Iterator result = instance.iterator();
        assertEquals(expResult, result);
    }

    /**
     * Test of listIterator method, of class GITList.
     */
    @Test
    public void testListIterator_0args() {
        System.out.println("listIterator");
        GITList instance = new GITListImpl();
        ListIterator expResult = null;
        ListIterator result = instance.listIterator();
        assertEquals(expResult, result);
    }

    /**
     * Test of listIterator method, of class GITList.
     */
    @Test
    public void testListIterator_int() {
        System.out.println("listIterator");
        int index = 0;
        GITList instance = new GITListImpl();
        ListIterator expResult = null;
        ListIterator result = instance.listIterator(index);
        assertEquals(expResult, result);
    }

    /**
     * Test of addAll method, of class GITList.
     */
    @Test
    public void testAddAll() {
        System.out.println("addAll");
        GITList instance = new GITListImpl();
        boolean expResult = false;
        boolean result = instance.addAll(null);
        assertEquals(expResult, result);
    }

    /**
     * Test of containsAll method, of class GITList.
     */
    @Test
    public void testContainsAll() {
        System.out.println("containsAll");
        GITList instance = new GITListImpl();
        boolean expResult = false;
        boolean result = instance.containsAll(null);
        assertEquals(expResult, result);
    }

    /**
     * Test of removeAll method, of class GITList.
     */
    @Test
    public void testRemoveAll() {
        System.out.println("removeAll");
        GITList instance = new GITListImpl();
        boolean expResult = false;
        boolean result = instance.removeAll(null);
        assertEquals(expResult, result);
    }

    /**
     * Test of retainAll method, of class GITList.
     */
    @Test
    public void testRetainAll() {
        System.out.println("retainAll");
        GITList instance = new GITListImpl();
        boolean expResult = false;
        boolean result = instance.retainAll(null);
        assertEquals(expResult, result);
    }

    public class GITListImpl<E> implements GITList<E> {

        public void add(int index, E obj) {
        }

        public void addFirst(E item) {
        }

        public E get(int index) {
            return null;
        }

        public E getFirst() {
            return null;
        }

        public E getLast() {
            return null;
        }

        public Iterator<E> iterator() {
            return null;
        }

        public ListIterator<E> listIterator() {
            return null;
        }

        public ListIterator<E> listIterator(int index) {
            return null;
        }

        public boolean addAll(GITList<E> l) {
            return false;
        }

        public boolean containsAll(GITList<E> l) {
            return false;
        }

        public boolean removeAll(GITList<E> l) {
            return false;
        }

        public boolean retainAll(GITList<E> l) {
            return false;
        }
    }
}