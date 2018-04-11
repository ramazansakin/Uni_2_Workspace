/**
 *--------------------------------
 * CSE222_HW01_101044044
  *--------------------------------
 * @author Samet Sait Talayhan
 */
package bankprogram;

public class Customer extends Person {
    // Data Fields
    /**
     * Holds value of account balance and account number.
     */
//    private Fruit fruit = new Fruit();
    private BankAccount theAccount = new BankAccount();
    
    /** Creates a new instance of Customer */
    public Customer(String name, String accountNumber,
                    String accountBalance)
    {
        super(name);
        theAccount.setAccountNumber(accountNumber);
        theAccount.setAccountBalance(accountBalance);
    }

    /**
     * @return the accountBalance
     */
    public String getAccountBalance() {
        return theAccount.getAccountBalance();
    }

    /**
     * @param accountBalance the accountBalance to set
     */
    public void setAccountBalance(String accountBalance) {
        theAccount.setAccountBalance(accountBalance);
    }

    /**
     * @return the accountNumber
     */
    public String getAccountNumber() {
        return theAccount.getAccountNumber();
    }

    /**
     * @param accountNumber the accountNumber to set
     */
    public void setAccountNumber(String accountNumber) {
        theAccount.setAccountNumber(accountNumber);
    }


}
