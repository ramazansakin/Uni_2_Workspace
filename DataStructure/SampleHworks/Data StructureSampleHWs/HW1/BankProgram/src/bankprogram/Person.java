/**
 *--------------------------------
 * CSE222_HW01_101044044
  *--------------------------------
 * @author Samet Sait Talayhan
 */
package bankprogram;

public class Person {

    /**
     * Holds value of property name.
     */
    private String name;

    /** Creates a new instance of Person */
    public Person(){
        name = "";
    }
    
    /** Creates a new instance of Person */
    public Person(String name){
        this.name = name;
    }
    
    /**
     * @return the name
     */
    public String getName() {
        return name;
    }

    /**
     * @param name the name to set
     */
    public void setName(String name) {
        this.name = name;
    }
}
