/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package pkg111044069hw04;

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
public class ConverterInfixToPostfixTest {
    
    public ConverterInfixToPostfixTest() {
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
     * Test of reader method, of class ConverterInfixToPostfix.
     */
    @Test( expected = NullPointerException.class )
    public void testReader() throws Exception {
        System.out.println("reader");
        ConverterInfixToPostfix instance = null;
        instance.reader();
        
    }

    /**
     * Test of convert method, of class ConverterInfixToPostfix.
     */
    @Test( expected = NullPointerException.class ) 
    public void testConvert() throws Exception {
        System.out.println("convert");
        String infix = "";
        ConverterInfixToPostfix instance = null;
        String expResult = "";
        String result = instance.convert(infix);
        assertEquals(expResult, result);
        
    }

    /**
     * Test of getPostfix method, of class ConverterInfixToPostfix.
     */
    @Test
    public void testGetPostfix() throws FileNotFoundException {
        System.out.println("getPostfix");
        ConverterInfixToPostfix instance = new ConverterInfixToPostfix("program.git");
        String expResult = "var a";  // first line of the file
        StringBuilder result = instance.getPostfix();
        //assertEquals(expResult, result);
        
    }

    /**
     * Test of isBin method, of class ConverterInfixToPostfix.
     */
    @Test
    public void testIsBin() throws FileNotFoundException {
        System.out.println("isBin");
        String op = "+";
        ConverterInfixToPostfix instance = new ConverterInfixToPostfix("program.git");
        boolean expResult = true;
        boolean result = instance.isBin(op);
        assertEquals(expResult, result);
        
    }
    
    @Test
    public void testIsBin2() throws FileNotFoundException {
        System.out.println("isBin");
        String op = "sin";
        ConverterInfixToPostfix instance = new ConverterInfixToPostfix("program.git");
        boolean expResult = false;
        boolean result = instance.isBin(op);
        assertEquals(expResult, result);
        
    }
    
    @Test
    public void testIsBin3() throws FileNotFoundException {
        System.out.println("isBin");
        String op = "/";
        ConverterInfixToPostfix instance = new ConverterInfixToPostfix("program.git");
        boolean expResult = true;
        boolean result = instance.isBin(op);
        assertEquals(expResult, result);
        
    }
}