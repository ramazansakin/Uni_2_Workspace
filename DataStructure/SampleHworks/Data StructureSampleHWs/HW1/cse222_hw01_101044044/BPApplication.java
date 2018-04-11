/**
 *--------------------------------
 * CSE222_HW01_101044044
  *--------------------------------
 * @author Samet Sait Talayhan
 */
package bankprogram;

public class BPApplication {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        // TODO code application logic here
                // Create a BankProgram object.
        BankProgram bankProgram = new ArrayBasedBP();
        // Load the customers and bank workers content from a file.
        bankProgram.loadData("customers.txt", "bankWorkers.txt");
        
        // Create a user interface object
        BPUserInterface bankProgramInterface = new BPConsoleUI();
        // Process User Commands
        bankProgramInterface.processCommands(bankProgram);
    }
}
