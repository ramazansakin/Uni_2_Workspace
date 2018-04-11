/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package pkg111044069hw05;

/**
 *
 * @author ramazan
 */
public class variable {
    
    private String name;
    private Double value;
    private boolean initStatus;
    

    /* non-parameter constructor */
    public variable() {
        this.name = null;
        this.value = null;
        this.initStatus = false;
    }
    
    /**
     * @param name
     * @param value
     */
    public variable(String name) {
        this.name = name;
        this.initStatus = false;
    }

    /**
     * @return the name
     */
    public String getName() {
        return name;
    }
    
    public boolean getStatus(){
        return initStatus;
    }

    /**
     * @return the value
     */
    public double getValue() {
        return value;
    }

    /**
     * @param value the value to set
     */
    public void setValue(double value) {
        this.value = value;
        initStatus=true;
    }
    
}
