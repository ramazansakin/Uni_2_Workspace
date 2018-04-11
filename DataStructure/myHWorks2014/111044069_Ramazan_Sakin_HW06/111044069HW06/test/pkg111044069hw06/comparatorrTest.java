/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package pkg111044069hw06;

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
public class comparatorrTest {
    
    public comparatorrTest() {
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
     * Test of compare method, of class comparatorr.
     */
    @Test
    public void testCompare() {
        System.out.println("compare");
        Car left = new Car("Fiat", "Albea", 25.000 );
        Car right = new Car("Mercedes","Benz",250.000);
        comparatorr instance = new comparatorr();
        int expResult = -1; // Because of the Fiat Albea's cost is cheaper than Mercedes
                            // result will be -1            
        int result = instance.compare(left, right);
        assertEquals(expResult, result);
        
    }
    
    @Test
    public void testCompare2() {
        System.out.println("compare2");
        Car left = new Car("Porche", "Cayenne", 350.000 );
        Car right = new Car("Mercedes","Benz",250.000);
        comparatorr instance = new comparatorr();
        int expResult = 1; // Because of the Porche Cayenne's cost is mare exp than Mercedes
                           // result will be 1 
        int result = instance.compare(left, right);
        assertEquals(expResult, result);
        
    }
    
    @Test
    public void testCompare3() {
        System.out.println("compare3");
        Car left = new Car("Porche", "X-Rt", 250.000 );
        Car right = new Car("Mercedes","Benz",250.000);
        comparatorr instance = new comparatorr();
        int expResult = 0; // Because of the Porche Cayenne's cost is mare exp than Mercedes
                           // result will be 1 
        int result = instance.compare(left, right);
        assertEquals(expResult, result);
        
    }
}