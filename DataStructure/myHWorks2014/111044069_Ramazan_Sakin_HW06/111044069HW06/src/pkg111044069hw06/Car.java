
package pkg111044069hw06;

/**
 *
 * @author ramazan
 */
public class Car {
    
    private String brand;
    private String name;
    private Double cost;

    public Car() {
        this.brand = null;
        this.name = null;
        this.cost=null;
    }

    
    
    public Car( String brand, String name, Double cost  ) {
        this.brand = brand;
        this.name = name;
        this.cost=cost;
    }
    
    public String toString(){
        return (brand.toString()+"-"+name.toString());
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

    /**
     * @return the cost
     */
    public Double getCost() {
        return cost;
    }

    /**
     * @param cost the cost to set
     */
    public void setCost(Double cost) {
        this.cost = cost;
    }
    
    
}
