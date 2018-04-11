/**
 *--------------------------------
 * CSE222_HW01_101044044
  *--------------------------------
 * @author Samet Sait Talayhan
 */
package bankprogram;

public interface BankProgram {

    /**
     * Load the data file containing the customers and workers, or establish 
     * a connection with the data source.
     *
     * @param customersTxt The name of the file (data source) with the 
     * customers information
     * @param bankWorkersTxt The name of the file (data source) with the bank
     * workers information
     */
    void loadData(String customersTxt, String bankWorkersTxt);

    /**
     * Look up a account.
     *
     * @param accountNumber The number of the account to look up
     * @return The number or null if accountNumber is not in the program
     */
    String lookupAccount(String accountNumber);
    
    /**
     * Look up a account.
     *
     * @param workerName The name of the worker to look up
     * @return The name or null if name is not in the program
     */
    String lookupBankWorker(String workerName);

    /**
     * Add a account or change an existing entry.
     *
     * @param name The name of the person being added or changed
     * @param accountNumber The new number to be assigned
     * @param accountBalance The new number to be assigned
     * @return The old number or, if a new entry, null
     */
    String addOrChangeAccount(String name, String accountNumber,
                                String accountBalance);
    
    String addOrChangeWorker(String workerName);

    /**
     * Remove a account from the program.
     *
     * @param accountNumber The number of the account to be removed
     * @return The current number. If not in program, null is returned
     */
    String removeAccount(String accountNumber);

    /**
     * Method to save the program. pre: The program has been loaded with
     * data.
     */
    void save();
}
