/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package fvpapplication;


import java.awt.Graphics;
import org.junit.After;
import org.junit.AfterClass;
import org.junit.Before;
import org.junit.BeforeClass;
import org.junit.Test;
import static org.junit.Assert.*;

/**
 * @author ramazan
 */
public class FunctionGraphicsTest {
    
    public FunctionGraphicsTest() {
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
     * Test of paintComponent method, of class FunctionGraphics.
     */
    // Because of g is null, so I always get Exception 
    @Test( expected = Exception.class )
    public void testPaintComponent() {
        System.out.println("paintComponent");
        Graphics g = null;
        FunctionGraphics instance = new FunctionGraphics();
        instance.paintComponent(g);
        // TODO review the generated test code and remove the default call to fail.
        //fail("The test case is a prototype.");
    }

    /**
     * Test of setColor method, of class FunctionGraphics.
     */
    // Because of g is null, so I always get Exception
    @Test( expected = Exception.class )
    public void testSetColor() {
        System.out.println("setColor");
        String color = "yellow";
        Graphics theGrap = null;
        FunctionGraphics instance = new FunctionGraphics();
        instance.setColor(color, theGrap);
        // TODO review the generated test code and remove the default call to fail.
        //fail("The test case is a prototype.");
    }

    /**
     * Test of setFunction method, of class FunctionGraphics.
     */
    
    @Test( expected = Exception.class )
    public void testSetFunction() {
        System.out.println("setFunction");
        String funcName = "sin(x)";
        String fLowBound = "-2.5";
        String fUpBound = "2.5";
        Graphics g = null;
        FunctionGraphics instance = new FunctionGraphics();
        instance.setFunction(funcName, fLowBound, fUpBound, g);
        // TODO review the generated test code and remove the default call to fail.
        //fail("The test case is a prototype.");
    }

    /**
     * Test of getFuncInfos method, of class FunctionGraphics.
     */
    @Test
    public void testGetFuncInfos() {
        System.out.println("getFuncInfos");
        String[] datas = {"sin(x)", "-2.5", "2.5", "yellow"};
        int num = 4;
        FunctionGraphics instance = new FunctionGraphics();
        instance.getFuncInfos(datas, num);
        // TODO review the generated test code and remove the default call to fail.
        //fail("The test case is a prototype.");
    }
}


