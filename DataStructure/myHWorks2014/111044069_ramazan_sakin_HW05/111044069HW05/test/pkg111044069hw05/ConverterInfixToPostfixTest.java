
package pkg111044069hw05;

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
    @Test 
    public void testConvert() throws Exception {
        System.out.println("convert1");
        String infix = "3 * 4 + sin 45";
        ConverterInfixToPostfix instance = null;
        String expResult = "3 4 * 45 sin + ";
        String result = instance.convert(infix);
        assertEquals(expResult, result);
        
    }
    
    /**
     * Test of convert method, of class ConverterInfixToPostfix.
     */
    @Test 
    public void testConvert2() throws Exception {
        System.out.println("convert2");
        String infix = "3 ^ 2 + log ( 12 * 5 + 3 )";
        ConverterInfixToPostfix instance = null;
        String expResult = "3 2 ^ 12 5 * 3 + log + ";
        String result = instance.convert(infix);
        assertEquals(expResult, result);
        
    }

    /**
     * Test of isBin method, of class ConverterInfixToPostfix.
     */
    @Test
    public void testIsBin() throws FileNotFoundException {
        System.out.println("isBin1");
        String op = "+";
        ConverterInfixToPostfix instance = new ConverterInfixToPostfix("program.git");
        boolean expResult = true;
        boolean result = instance.isBin(op);
        assertEquals(expResult, result);
        
    }
    
    @Test
    public void testIsBin2() throws FileNotFoundException {
        System.out.println("isBin2");
        // sin operator is not binary operator
        String op = "sin";
        ConverterInfixToPostfix instance = new ConverterInfixToPostfix("program.git");
        
        boolean expResult = false;
        boolean result = instance.isBin(op);
        assertEquals(expResult, result);
        
    }
    
    @Test
    public void testIsBin3() throws FileNotFoundException {
        System.out.println("isBin3");
        // ++ operator is not binary operator
        String op = "++";
        ConverterInfixToPostfix instance = new ConverterInfixToPostfix("program.git");
        
        boolean expResult = false;
        boolean result = instance.isBin(op);
        assertEquals(expResult, result);
        
    }
    
    @Test
    public void testIsBin4() throws FileNotFoundException {
        System.out.println("isBin4");
        String op = "/";
        ConverterInfixToPostfix instance = new ConverterInfixToPostfix("program.git");
        
        boolean expResult = true;
        boolean result = instance.isBin(op);
        assertEquals(expResult, result);
        
    }
}