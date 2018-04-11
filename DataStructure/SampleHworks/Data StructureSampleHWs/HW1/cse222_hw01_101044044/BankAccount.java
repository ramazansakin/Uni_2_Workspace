/**
 *--------------------------------
 * CSE222_HW01_101044044
  *--------------------------------
 * @author Samet Sait Talayhan
 */
package bankprogram;

public class BankAccount {
    
    /**
     * Holds value of account balance.
     */
    private String accountBalance;
    
    /**
     * Holds value of account balance.
     */
    private String accountNumber;

    /**
     * Constructs a bank account with a zero balance
     */
    public BankAccount() {
        accountBalance = "0";
    }

    /**
     * Constructs a bank account with a given balance
     *
     * @param initialBalance the initial balance
     */
    public BankAccount(String initialBalance) {
        setAccountBalance(initialBalance);
    }


    /**
     * Gets the current balance of the bank account.
     * @return the accountBalance
     */
    public String getAccountBalance() {
        return accountBalance;
    }

    /**
     * @param accountBalance the accountBalance to set
     */
    public void setAccountBalance(String accountBalance) {
        this.accountBalance = accountBalance;
    }

    /**
     * @return the accountNumber
     */
    public String getAccountNumber() {
        return accountNumber;
    }

    /**
     * @param accountNumber the accountNumber to set
     */
    public void setAccountNumber(String accountNumber) {
        this.accountNumber = accountNumber;
    }
}
