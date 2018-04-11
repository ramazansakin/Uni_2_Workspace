/**
 *--------------------------------
 * CSE222_HW01_101044044
  *--------------------------------
 * @author Samet Sait Talayhan
 */
package bankprogram;

public interface BPUserInterface {

    /**
     * Abstract method that processes user's commands.
     *
     * @param theBankProgram The BankProgram object that contains the data
     * to be displayed and/or changed
     */
    void processCommands(BankProgram theBankProgram);
}
