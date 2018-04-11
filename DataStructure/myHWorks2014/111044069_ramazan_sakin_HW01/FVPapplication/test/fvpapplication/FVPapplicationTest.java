/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package fvpapplication;

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
public class FVPapplicationTest {
    
    public FVPapplicationTest() {
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
    public void tearDown(){
    }

    /**
     * Test of main method, of class FVPapplication.
     */
    @Test( expected = Exception.class )
    public void testMain() {
        System.out.println("main");
        String[] args = null;
        FVPapplication.main(args);
        // TODO review the generated test code and remove the default call to fail.
        //fail("The test case is a prototype.");
    }
}