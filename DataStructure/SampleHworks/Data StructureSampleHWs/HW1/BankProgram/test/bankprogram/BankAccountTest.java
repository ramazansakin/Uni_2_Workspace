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
public class BankAccountTest {
    
    public BankAccountTest() {
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
     * Test of setAccountBalance method, of class BankAccount.
     */
    @Test
    public void testSetAccountBalance() {
        System.out.println("setAccountBalance");
        String accountBalance = "Test";
        BankAccount instance = new BankAccount();
        instance.setAccountBalance(accountBalance);
        // TODO review the generated test code and remove the default call to fail.
//        fail("The test case is a prototype.");
    }

    /**
     * Test of getAccountBalance method, of class BankAccount.
     */
    @Test
    public void testGetAccountBalance() throws 
            junit.framework.AssertionFailedError{
        System.out.println("getAccountBalance");
        BankAccount instance = new BankAccount();
        String expResult = "Test";
        String result = instance.getAccountBalance();
        assertEquals(expResult, result);
        // TODO review the generated test code and remove the default call to fail.
//        fail("The test case is a prototype.");
    }

    /**
     * Test of setAccountNumber method, of class BankAccount.
     */
    @Test
    public void testSetAccountNumber() {
        System.out.println("setAccountNumber");
        String accountNumber = "Test";
        BankAccount instance = new BankAccount();
        instance.setAccountNumber(accountNumber);
        // TODO review the generated test code and remove the default call to fail.
//        fail("The test case is a prototype.");
    }

    /**
     * Test of getAccountNumber method, of class BankAccount.
     */
    @Test
    public void testGetAccountNumber() throws 
            junit.framework.AssertionFailedError {
        System.out.println("getAccountNumber");
        BankAccount instance = new BankAccount();
        String expResult = "Test";
        String result = instance.getAccountNumber();
        assertEquals(expResult, result);
        // TODO review the generated test code and remove the default call to fail.
//        fail("The test case is a prototype.");
    }
}