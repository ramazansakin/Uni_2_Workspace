/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package bankprogram;

import org.junit.After;
import org.junit.AfterClass;
import org.junit.Before;
import org.junit.BeforeClass;
import org.junit.Test;
import static org.junit.Assert.*;

/**
 *
 * @author neo
 */
public class CustomerTest {
    
    public CustomerTest() {
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
     * Test of getAccountBalance method, of class Customer.
     */
    @Test
    public void testGetAccountBalance() {
        System.out.println("getAccountBalance");
       Customer instance = new Customer("TestName", "TestNumber", "TestBalance");
        String expResult = "TestBalance";
        String result = instance.getAccountBalance();
        assertEquals(expResult, result);
        // TODO review the generated test code and remove the default call to fail.
//        fail("The test case is a prototype.");
    }

    /**
     * Test of setAccountBalance method, of class Customer.
     */
    @Test
    public void testSetAccountBalance() {
        System.out.println("setAccountBalance");
        String accountBalance = "TestBalance";
        Customer instance = new Customer("TestName", "TestNumber", "TestBalance");
        instance.setAccountBalance(accountBalance);
        // TODO review the generated test code and remove the default call to fail.
//        fail("The test case is a prototype.");
    }

    /**
     * Test of getAccountNumber method, of class Customer.
     */
    @Test
    public void testGetAccountNumber() {
        System.out.println("getAccountNumber");
        Customer instance = new Customer("TestName", "TestNumber", "TestBalance");
        String expResult = "TestNumber";
        String result = instance.getAccountNumber();
        assertEquals(expResult, result);
        // TODO review the generated test code and remove the default call to fail.
//        fail("The test case is a prototype.");
    }

    /**
     * Test of setAccountNumber method, of class Customer.
     */
    @Test
    public void testSetAccountNumber() {
        System.out.println("setAccountNumber");
        String accountNumber = "TestNumber";
        Customer instance = new Customer("TestName", "TestNumber", "TestBalance");
        instance.setAccountNumber(accountNumber);
        // TODO review the generated test code and remove the default call to fail.
//        fail("The test case is a prototype.");
    }
}