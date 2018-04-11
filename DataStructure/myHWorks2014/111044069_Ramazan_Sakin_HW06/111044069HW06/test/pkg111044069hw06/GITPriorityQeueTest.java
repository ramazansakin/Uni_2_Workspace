/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package pkg111044069hw06;

import java.util.NoSuchElementException;
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
public class GITPriorityQeueTest {
    
    public GITPriorityQeueTest() {
    }
    
    @BeforeClass
    public static void setUpClass() {
        System.out.println("Test Started");
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
     * Test of offer method, of class GITPriorityQeue.
     */
    @Test
    public void testOffer() {
        System.out.println("offer");
        Object item = "ramazan";    // Ramazan Queue de olmadıgı icin ekleyecek 
                                    // Eger olan biseyi eklemek istersek false return eder
        GITPriorityQeue instance = new GITPriorityQeue();
        instance.offer(item);
        boolean expResult = true;
        boolean result = instance.offer(item);
        assertEquals(expResult, result);
        
    }

    /**
     * Test of remove method, of class GITPriorityQeue.
     */
    @Test
    public void testRemove() {
        System.out.println("remove");
        GITPriorityQeue instance = new GITPriorityQeue();
        String anyName = "Fatih";
        instance.offer(anyName);
        
        Object expResult=anyName;
        Object result = instance.remove();
        assertEquals(expResult, result);
        
    }

    /**
     * Test of poll method, of class GITPriorityQeue.
     */
    @Test
    public void testPoll() {
        System.out.println("poll");
        GITPriorityQeue instance = new GITPriorityQeue();
        String anyName = "Fatih";
        // Eleman yoksa null return eder
        
        Object expResult=null;  // Because the queue is empty ( root= null )
        Object result = instance.poll();
        assertEquals(expResult, result);
        
    }

    /**
     * Test of peek method, of class GITPriorityQeue.
     */
    @Test
    public void testPeek() {
        System.out.println("peek");
        GITPriorityQeue instance = new GITPriorityQeue();
        instance.offer("Ali");
        instance.offer("Salih");
        instance.offer("Muhammed");
        Object expResult = "Ali";   // element at the root is Ali
        Object result = instance.peek();
        assertEquals(expResult, result);
        
    }

    /**
     * Test of element method, of class GITPriorityQeue.
     */
    @Test( expected = NoSuchElementException.class )
    public void testElement() {
        System.out.println("element");
        GITPriorityQeue instance = new GITPriorityQeue();
        Object expResult = null;
        // root null ise Exception firlatır
        Object result = instance.element();
        assertEquals(expResult, result);
        
    }
}