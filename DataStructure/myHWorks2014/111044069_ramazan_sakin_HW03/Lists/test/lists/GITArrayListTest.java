/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package lists;

import java.util.InputMismatchException;
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
public class GITArrayListTest {
    
    public GITArrayListTest() {
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
     * Test of add method, of class GITArrayList.
     */
    @Test
    public void testAdd() {
        System.out.println("add");
        int index = 0;
        Object obj = "Ramazan";
        GITArrayList instance = new GITArrayList();
        instance.add(index, obj);
        
    }
    
    @Test( expected = Exception.class )
    public void testAdd2() {
        System.out.println("add2");
        int index = 1;
        Object obj = 2; 
        GITArrayList instance = new GITArrayList();
        instance.add(index, obj);
        
    }
    
    /**
     * Test of addFirst method, of class GITArrayList.
     */
    @Test
    public void testAddFirst() {
        System.out.println("addFirst");
        Object item = "Selami";
        GITArrayList instance = new GITArrayList();
        instance.addFirst(item);
        
    }

    /**
     * Test of getSize method, of class GITArrayList.
     */
    @Test
    public void testGetSize() {
        System.out.println("getSize");
        GITArrayList instance = new GITArrayList();
        instance.add(0, "Ramazan");
        instance.addFirst("Hakan");
        int expResult = 2;
        int result = instance.getSize();
        assertEquals(expResult, result);
        
    }

    /**
     * Test of get method, of class GITArrayList.
     */
    @Test
    public void testGet() {
        System.out.println("get");
        int index = 2;
        GITArrayList instance = new GITArrayList();
        instance.add(0, "Ramazan");
        instance.add(1,"Hakan");
        instance.add(2,"Sabri");
        Object expResult = "Sabri";
        Object result = instance.get(index);
        assertEquals(expResult, result);
        
    }

    /**
     * Test of getFirst method, of class GITArrayList.
     */
    @Test
    public void testGetFirst() {
        System.out.println("getFirst");
        GITArrayList instance = new GITArrayList();
        instance.add(0, "Ramazan");
        instance.addFirst("Hakan");
        instance.addFirst("Sabri");
        instance.addFirst("Seyda");
        instance.add(4,"Hakkı");
        // First eleman of the array Seyda  addFirst
        Object expResult = "Seyda";
        Object result = instance.getFirst();
        assertEquals(expResult, result);
       
    }

    /**
     * Test of getLast method, of class GITArrayList.
     */
    @Test
    public void testGetLast() {
        System.out.println("getLast");
        GITArrayList instance = new GITArrayList();
        instance.add(0, "Ramazan");
        instance.addFirst("Hakan");
        instance.addFirst("Sabri");
        instance.addFirst("Seyda");
        instance.add(4,"Hakkı");
        Object expResult = "Hakkı";
        Object result = instance.getLast();
        assertEquals(expResult, result);
    
    }

    /**
     * Test of iterator method, of class GITArrayList.
     */
    @Test
    public void testIterator() {
        System.out.println("iterator");
        
        GITArrayList instance = new GITArrayList();
        instance.add(0, "Ramazan");
        instance.addFirst("Hakan");
        instance.addFirst("Sabri");
        
        Iterator expResult =  instance.iterator();
        Iterator result = instance.iterator();
        assertEquals(expResult, result);
    
    }

    /**
     * Test of listIterator method, of class GITArrayList.
     */
    @Test( expected = NullPointerException.class )
    public void testListIterator_0args() {
        System.out.println("listIterator");
        GITArrayList instance = null;
        ListIterator expResult = null;
        
        ListIterator result = instance.listIterator();
        assertEquals(expResult, result);
    
    }

    /**
     * Test of listIterator method, of class GITArrayList.
     */
    @Test
    public void testListIterator_int() {
        System.out.println("listIterator");
        int index = 1;
        
        GITArrayList instance2 = new GITArrayList();
        instance2.add(0,"Sefa");
        instance2.add(1,"Abdullah");
        instance2.add(2,"Fahri");
        
        
        ListIterator expResult = instance2.listIterator(index);
        
        // NullPointer Exception
        ListIterator result = instance2.listIterator(index);
        assertEquals(expResult, result);
    
    }

    /**
     * Test of addAll method, of class GITArrayList.
     */
    @Test
    public void testAddAll() {
        System.out.println("addAll");
        GITArrayList instance = new GITArrayList();
        instance.add(0, "Ramazan");
        instance.addFirst("Hakan");
        instance.addFirst("Sabri");
        instance.addFirst("Seyda");
        instance.add(4,"Hakkı");
        
        GITArrayList instance2 = new GITArrayList();
        instance2.add(0,"Sefa");
        instance2.add(1,"Abdullah");
        instance2.add(2,"Fahri");
        
        boolean expResult = true;
        boolean result = instance.addAll(instance2);
        assertEquals(expResult, result);
    
    }

    /**
     * Test of containsAll method, of class GITArrayList.
     */
    @Test
    public void testContainsAll() {
        System.out.println("containsAll");
        GITArrayList instance = new GITArrayList();
        instance.add(0, "Ramazan");
        instance.addFirst("Hakan");
        instance.addFirst("Sabri");
        instance.addFirst("Seyda");
        instance.add(4,"Hakkı");
        
        GITArrayList instance2 = new GITArrayList();
        instance2.add(0,"Sefa");
        instance2.add(1,"Abdullah");
        instance2.add(2,"Fahri");
        
        boolean expResult = false;
        boolean result = instance.containsAll(instance2);
        assertEquals(expResult, result);
    
    }

    /**
     * Test of removeAll method, of class GITArrayList.
     */
    @Test( expected = ArrayIndexOutOfBoundsException.class )
    public void testRemoveAll() {
        System.out.println("removeAll");
        GITArrayList instance = new GITArrayList();
        
        // getting index 4 causes ArrayOutOfBoundException, it should be start 0
        instance.add(4, "Hakan");
        instance.add(0, "Ramazan");
        instance.addFirst("Hakan");
        instance.addFirst("Sabri");
        instance.add(3,"Hakkı");
        
        GITArrayList instance2 = new GITArrayList();
        instance2.add(0,"Cengiz");
        instance2.add(1,"Fatih");
        instance2.add(2,"Hasan");
        instance2.add(3, "Hakan");
        
        boolean expResult = true;
        
        boolean result = instance.removeAll(instance2);
        assertEquals(expResult, result);
    
    }

    /**
     * Test of retainAll method, of class GITArrayList.
     */
    @Test
    public void testRetainAll() {
        System.out.println("retainAll");
        GITArrayList instance = new GITArrayList();
        
        instance.add(0, "Ramazan");
        instance.add(1, "Hakan");
        instance.addFirst("Hakan");
        instance.add(3,"Hakkı");
        
        GITArrayList instance2 = new GITArrayList();
        instance2.add(0,"Cengiz");
        instance2.add(1,"Ramazan");
        instance2.add(2,"Sabri");
        instance2.add(3, "Hakan");
        
        boolean expResult = true;
        
        boolean result = instance.retainAll(instance2);
        assertEquals(expResult, result);
    
    }
}

