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
public class GITLinkedListTest {
    
    public GITLinkedListTest() {
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
     * Test of add method, of class GITLinkedList.
     */
    @Test
    public void testAdd() {
        System.out.println("add");
        int index = 0;
        Object obj = "Feyyaz";
        GITLinkedList instance = new GITLinkedList();
        instance.add(index, obj);
        
    }
    
    @Test
    public void testAdd2() {
        System.out.println("add2");
        int index = 0;
        Object obj = "Sabri";
        
        GITLinkedList instance = new GITLinkedList();
        instance.add(index, obj);
    }
    
    @Test
    public void testAdd3() {
        System.out.println("add3");
        int index = 0;
        Object obj = "Ferdi";
        
        GITLinkedList instance = new GITLinkedList();
        instance.add(index, obj);
    }
    
    /**
     * Test of addFirst method, of class GITLinkedList.
     */
    @Test
    public void testAddFirst() {
        System.out.println("addFirst");
        Object item = "Ibrahim";
        GITLinkedList instance = new GITLinkedList();
        instance.addFirst(item);
        
    }

    /**
     * Test of get method, of class GITLinkedList.
     */
    @Test
    public void testGet() {
        System.out.println("get");
        //int index = 0;
        GITLinkedList instance = new GITLinkedList();
        instance.add(0, "Selahattin");
        instance.add(1, "Ibrahim");
        instance.add(2, "Selami");
        
        Object expResult = "Ibrahim";
        Object result = instance.get(1);
        assertEquals(expResult, result);
        
    }

    /**
     * Test of getFirst method, of class GITLinkedList.
     */
    @Test
    public void testGetFirst() {
        System.out.println("getFirst");
        GITLinkedList instance = new GITLinkedList();
        instance.add(0, "Selahattin");
        instance.add(1, "Ibrahim");
        instance.add(2, "Selami");
        instance.add(3, "Enis");
        instance.add(4, "Yılmaz");
        
        Object expResult = "Selahattin";
        Object result = instance.getFirst();
        assertEquals(expResult, result);
        
    }

    /**
     * Test of getLast method, of class GITLinkedList.
     */
    @Test
    public void testGetLast() {
        System.out.println("getLast");
        GITLinkedList instance = new GITLinkedList();
        instance.add(0, "Selahattin");
        instance.add(1, "Ibrahim");
        instance.add(2, "Selami");
        instance.add(3, "Enis");
        instance.add(4, "Yılmaz");  // the last one
        instance.add(4, "Oguzhan");
        
        Object expResult = "Yılmaz";
        Object result = instance.getLast();
        assertEquals(expResult, result);
     
    }

    /**
     * Test of iterator method, of class GITLinkedList.
     */
    @Test( expected = AssertionError.class )
    public void testIterator() {
        System.out.println("iterator");
        GITLinkedList instance = new GITLinkedList();
        Iterator expResult = null;
        Iterator result = instance.iterator();
        assertEquals(expResult, result);
    }

    /**
     * Test of listIterator method, of class GITLinkedList.
     */
    @Test( expected = AssertionError.class )
    public void testListIterator_0args() {
        System.out.println("listIterator");
        GITLinkedList instance = new GITLinkedList();
        instance.add(0, "Selahattin");
        instance.add(1, "Ibrahim");
        instance.add(2, "Selami");
        instance.add(3, "Enis");
        instance.add(4, "Yılmaz");  // the last one
        instance.add(4, "Oguzhan");
        
        ListIterator expResult = null;
        ListIterator result = instance.listIterator(0);
 
        assertEquals(expResult, result);
    }

    /**
     * Test of listIterator method, of class GITLinkedList.
     */
    @Test
    public void testListIterator_int() {
        System.out.println("listIterator");
        int index = 0;
        GITLinkedList instance = new GITLinkedList();
        instance.add(0, "Fahri");
        instance.add(1, "Sinan");
        instance.add(2, "Abdurrahman");
        instance.add(3, "Enis");
        instance.add(4, "Yılmaz");  // the last one
        instance.add(4, "Oguzhan");
        
        ListIterator expResult = instance.listIterator(index);  // the next one ! I couldnt get it ?
        String res = (String)expResult.next();
        ListIterator result = instance.listIterator(index);
        assertEquals(expResult, res);
    
    }

    /**
     * Test of addAll method, of class GITLinkedList.
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
     * Test of containsAll method, of class GITLinkedList.
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
     * Test of removeAll method, of class GITLinkedList.
     */
    @Test
    public void testRemoveAll() {
        System.out.println("removeAll");
        GITArrayList instance = new GITArrayList();
        
        instance.add(0, "Hakan");
        instance.add(1, "Hakan");
        instance.add(2, "Ramazan");
        instance.addFirst("Hakan");
        instance.add(4,"Hakkı");
        
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
     * Test of retainAll method, of class GITLinkedList.
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
