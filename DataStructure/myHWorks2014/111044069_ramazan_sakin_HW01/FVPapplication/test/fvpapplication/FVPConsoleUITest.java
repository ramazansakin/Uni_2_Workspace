/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package fvpapplication;

import java.io.FileNotFoundException;
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
public class FVPConsoleUITest {
    
    public FVPConsoleUITest() {
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
     * Test of processCommands method, of class FVPConsoleUI.
     */
    @Test( expected = Exception.class )
    public void testProcessCommands() {
        System.out.println("processCommands");
        FVPConsoleUI instance = new FVPConsoleUI();
        instance.processCommands();
        // TODO review the generated test code and remove the default call to fail.
        //fail("The test case is a prototype.");
    }

    /**
     * Test of readFileandShowFuncVis method, of class FVPConsoleUI.
     */
    @Test( expected = Exception.class )
    public void testReadFileandShowFuncVis() throws Exception {
        System.out.println("readFileandShowFuncVis");
        int selection = 0;
        FVPConsoleUI instance = new FVPConsoleUI();
        instance.readFileandShowFuncVis(selection);
        // TODO review the generated test code and remove the default call to fail.
        //fail("The test case is a prototype.");
    }
}

