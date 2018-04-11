/**
 * @author ramazan
 */

package HW8_111044069_p1;

public class Family extends Person {
    
    private Person father;
    private Person mother;
    private Person[] children;      // Person array for children
    private static int numOfFamily = 0;     //static number for number of Family object
                                            //in memory
    private int capacity;
    private int numOfChild;
    
    
    //String aFname, String aFsurname, int aFyear, String aFgender,
    Family() throws NullPointerException{
        father = new Person();
        mother = new Person();
        this.father.setName("");
        this.father.setSurname("");
        this.father.setYear(0);
        this.father.setGender("");
        
        this.mother.setName("");
        this.mother.setSurname("");
        this.mother.setYear(0);
        this.mother.setGender("");
        
        this.capacity = 10;
        this.numOfChild = 0;
        this.children = new Person[capacity];
        ++Family.numOfFamily;   //increasing the number of family static number
    }
    
    // two-parameter constructor one for father and  one for mother
    // it can throw an exception if there is a problem at parameters
    /**
     * @param aFather
     * @param aMother
     */
    Family( Person aFather, Person aMother  ) throws NullPointerException{
        
        father = new Person();
        mother = new Person();
        this.capacity = 15;
        this.numOfChild = 0;
        this.children = new Person[capacity];
        ++Family.numOfFamily;   //increasing the number of family static number
        
        if( aFather.getGender() == "male" ){
            this.father.setName(aFather.getName());
            this.father.setSurname(aFather.getSurname());
            this.father.setYear(aFather.getBirthYear());
            this.father.setGender(aFather.getGender());
        }else
            throw new NullPointerException("Father must be a male!!");
        
        if( aMother.getGender() == "female" ){
            this.mother.setName(aMother.getName());
            this.mother.setSurname(aMother.getSurname());
            this.mother.setYear(aMother.getBirthYear());
            this.mother.setGender(aMother.getGender());
        }else
            throw new NullPointerException("Mother must be female!!!");
        
    }
    
    //Copy-constructor for Family
    Family( Family aFamily ) throws NullPointerException{
        // initializing
        father = new Person();
        mother = new Person();
        this.capacity = 10;
        this.numOfChild = 0;
        this.children = new Person[capacity];
        
        ++Family.numOfFamily;   //increasing the number of family static number
        
        if( aFamily != null ){
            this.setTheFather(aFamily.getFather());
            this.setTheMother(aFamily.getMother());
            for( int i=0; i<aFamily.getNumOfChildren();++i )
                this.setAChild(aFamily.at(i));
        }
        this.numOfChild = aFamily.getNumOfChildren();
    }
    
    
    /** Set the mother
     * @param aMother
     */
    public void setTheMother( Person aMother )  throws NullPointerException{
    
        if( aMother.getGender() != "female" ){
            throw new NullPointerException("Mother can not be male!!!");
        }else if( aMother != null ){
            this.mother.setName(aMother.getName());
            this.mother.setSurname(aMother.getSurname());
            this.mother.setYear(aMother.getBirthYear());
            this.mother.setGender(aMother.getGender());
        }
    }
    
    /**  Set the father
     * @param aFather
     */
    public void setTheFather( Person aFather )  throws NullPointerException{
        if( aFather.getGender() != "male" ){
            throw new NullPointerException("Father can not be female!!!");
        }else if( aFather != null ){
            getFather().setName(aFather.getName());
            getFather().setSurname(aFather.getSurname());
            getFather().setYear(aFather.getBirthYear());
            getFather().setGender(aFather.getGender());
        }
    }
    
    /**
     * @return number for children's number
     */
    public int getNumOfChildren(){ return numOfChild; }
    
    /**
     * @return Person for Father
     */
    public Person getFather(){ return father; }
    /**
     * @return Person for Mother
     */
    public Person getMother(){ return mother; }
    
    public Person[] getChildren(){
        return children;
    }
    
    /**
     * @param index
     * @return
     */
    public void setAChild( Person aChild ) throws NullPointerException{
        children[numOfChild] = aChild;
        ++numOfChild;
    }
    
    /**
     * @param index
     * @return one of the child with called index
     */
    public Person at( int index ){ // throw an excp
        if( index < 0 || index > getNumOfChildren() )	//error checking
            System.out.println("The index is illegal. Throw an exception!!!");
        
        return children[index]; 
    }
    
    /**
     *
     * @return
     */
    public static int getNumberOfFamily(){ return numOfFamily; }
    
    protected void finalize(){
        System.out.println("Finalize() was called.");
        --numOfFamily;
    }
    
    /**
     *
     * @param aFamily
     * @return
     */
    public boolean equals( Family aFamily ){
        
        int tChild = 0;
        if( father.getName() == aFamily.getFather().getName()             &&
            father.getSurname() == aFamily.getFather().getSurname()       &&
            father.getBirthYear() == aFamily.getFather().getBirthYear()   &&
            mother.getName() == aFamily.getMother().getName()             &&
            mother.getSurname() == aFamily.getMother().getSurname()       &&
            mother.getBirthYear() == aFamily.getMother().getBirthYear()   &&
            getNumOfChildren() == aFamily.getNumOfChildren()
                                                                              ){
            for( int i=0; i<getNumOfChildren(); ++i )
                for( int j=i+1; j<getNumOfChildren(); ++j ){
                    if( at(i).getName() == aFamily.at(i).getName() &&
                        at(i).getSurname() == aFamily.at(i).getSurname() &&
                        at(i).getBirthYear() == aFamily.at(i).getBirthYear() &&
                        at(i).getGender() == aFamily.at(i).getGender()     ){
                            ++tChild;
                    }
                }
        }
        if( tChild == getNumOfChildren() )
            return true;
        return false;
    }
    
    // I have already decleared a method that adds a child to the family,
    // So I decleared this add() method like this...
    /**
     *
     * @param aChild
     */
    public void add( Person aChild ) throws NullPointerException{
        setAChild(aChild);
    }
    

}
