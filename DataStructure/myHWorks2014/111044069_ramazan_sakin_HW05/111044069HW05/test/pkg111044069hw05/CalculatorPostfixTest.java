
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
public class CalculatorPostfixTest {
    
    public CalculatorPostfixTest() {
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
     * Test of isNumeric method, of class CalculatorPostfix.
     */
    @Test
    public void testIsNumeric() {
        System.out.println("isNumeric");
        String str = "1231412";
        boolean expResult = true;
        boolean result = CalculatorPostfix.isNumeric(str);
        assertEquals(expResult, result);
        
    }
    
    @Test
    public void testIsNumeric2() {
        System.out.println("isNumeric2");
        String str = "1231412asd";
        boolean expResult = false;
        boolean result = CalculatorPostfix.isNumeric(str);
        assertEquals(expResult, result);
        
    }
    /**
     * Test of searchVar method, of class CalculatorPostfix.
     */
    @Test
    public void testSearchVar() throws FileNotFoundException {
        System.out.println("searchVar");
        String target = "newVar";
        String filePath = "program.git";
        CalculatorPostfix instance = new CalculatorPostfix( filePath );
        
        // the variable is not in the LinkeList <variable>
        int expResult = -1;
        int result = instance.searchVar(target);
        assertEquals(expResult, result);
        
    }

    @Test
    public void testSearchVar2() throws FileNotFoundException {
        System.out.println("searchVar2");
        String target = "variable";
        String filePath = "program.git";
        CalculatorPostfix instance = new CalculatorPostfix( filePath );
        int expResult = -1;     // the variable is not in the LinkeList <variable>
        int result = instance.searchVar(target);
        assertEquals(expResult, result);
        
    }
    
    /**
     * Test of eval method, of class CalculatorPostfix.
     */
    @Test
    public void testEval() throws Exception {
        System.out.println("eval");
        String expression = "variable";
        String filePath = "program.git";
        CalculatorPostfix instance = new CalculatorPostfix( filePath );
        Double expResult = 0.0;
        Double result = instance.eval(expression);
        assertEquals(expResult, result);
        
    }
    
    @Test
    public void testEval2() throws Exception {
        System.out.println("eval2");
        String expression = "newVAr";
        String filePath = "program.git";
        CalculatorPostfix instance = new CalculatorPostfix( filePath );
        Double expResult = 0.0;
        Double result = instance.eval(expression);
        assertEquals(expResult, result);
        
    }
}