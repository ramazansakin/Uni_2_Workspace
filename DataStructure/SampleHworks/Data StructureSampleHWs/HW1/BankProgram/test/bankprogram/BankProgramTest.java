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
public class BankProgramTest {
    
    public BankProgramTest() {
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
     * Test of loadData method, of class BankProgram.
     */
    @Test
    public void testLoadData() {
        System.out.println("loadData");
        String customersTxt = "";
        String bankWorkersTxt = "";
        BankProgram instance = new BankProgramImpl();
        instance.loadData(customersTxt, bankWorkersTxt);
        // TODO review the generated test code and remove the default call to fail.
//        fail("The test case is a prototype.");
    }

    /**
     * Test of lookupAccount method, of class BankProgram.
     */
    @Test
    public void testLookupAccount() {
        System.out.println("lookupAccount");
        String name = "";
        BankProgram instance = new BankProgramImpl();
        String expResult = "";
        String result = instance.lookupAccount(name);
        assertEquals(expResult, result);
        // TODO review the generated test code and remove the default call to fail.
//        fail("The test case is a prototype.");
    }

    /**
     * Test of lookupBankWorker method, of class BankProgram.
     */
    @Test
    public void testLookupBankWorker() {
        System.out.println("lookupBankWorker");
        String workerName = "";
        BankProgram instance = new BankProgramImpl();
        String expResult = "";
        String result = instance.lookupBankWorker(workerName);
        assertEquals(expResult, result);
        // TODO review the generated test code and remove the default call to fail.
//        fail("The test case is a prototype.");
    }

    /**
     * Test of addOrChangeAccount method, of class BankProgram.
     */
    @Test
    public void testAddOrChangeAccount() {
        System.out.println("addOrChangeAccount");
        String name = "";
        String accountNumber = "";
        String accountBalance = "";
        BankProgram instance = new BankProgramImpl();
        String expResult = "";
        String result = instance.addOrChangeAccount(name, accountNumber, accountBalance);
        assertEquals(expResult, result);
        // TODO review the generated test code and remove the default call to fail.
//        fail("The test case is a prototype.");
    }

    /**
     * Test of addOrChangeWorker method, of class BankProgram.
     */
    @Test
    public void testAddOrChangeWorker() {
        System.out.println("addOrChangeWorker");
        String workerName = "";
        BankProgram instance = new BankProgramImpl();
        String expResult = "";
        String result = instance.addOrChangeWorker(workerName);
        assertEquals(expResult, result);
        // TODO review the generated test code and remove the default call to fail.
//        fail("The test case is a prototype.");
    }

    /**
     * Test of removeAccount method, of class BankProgram.
     */
    @Test
    public void testRemoveAccount() {
        System.out.println("removeAccount");
        String name = "";
        BankProgram instance = new BankProgramImpl();
        String expResult = "";
        String result = instance.removeAccount(name);
        assertEquals(expResult, result);
        // TODO review the generated test code and remove the default call to fail.
//        fail("The test case is a prototype.");
    }

    /**
     * Test of save method, of class BankProgram.
     */
    @Test
    public void testSave() {
        System.out.println("save");
        BankProgram instance = new BankProgramImpl();
        instance.save();
        // TODO review the generated test code and remove the default call to fail.
//        fail("The test case is a prototype.");
    }

    public class BankProgramImpl implements BankProgram {

        public void loadData(String customersTxt, String bankWorkersTxt) {
        }

        public String lookupAccount(String name) {
            return "";
        }

        public String lookupBankWorker(String workerName) {
            return "";
        }

        public String addOrChangeAccount(String name, String accountNumber, String accountBalance) {
            return "";
        }

        public String addOrChangeWorker(String workerName) {
            return "";
        }

        public String removeAccount(String name) {
            return "";
        }

        public void save() {
        }
    }
}