/**
 * @author Ramazan
 */
package HW8_111044069_p1;

public class Person {

    /**
     * @param args the command line arguments
     */
    private String  name;
    private String  surname;
    private int birthYear;
    private String gender;
    
    // Default-constructor
    Person() throws NullPointerException{
        this("Unnamed","Unsurnamed",0,"fe-male");
    }
    
    /**
     * @param Name
     * @param surName
     * @param Byear
     * @param Gender
     */
    Person( String Name, String surName, int Byear, String Gender ) throws NullPointerException{
        name = Name;
        surname = surName;
        gender = Gender;
        if( Byear < 0 )
            throw new NullPointerException("Illegal Birthyear year!!Birthyear must be positive!!!");
        birthYear = Byear;
    }
    
    /**
     * @param aPerson
     */
    Person( Person aPerson ){
        this(aPerson.getName(), aPerson.getSurname(),aPerson.getBirthYear(), aPerson.getGender());
    }

    //getters
    public String getName(){ return name; }
    public String getSurname(){ return surname; }
    public String getGender(){ return gender; }
    public int getBirthYear(){ return birthYear;}
    
    public void setName( String aName ){ name=aName; }
    public void setSurname(String aSname){ surname=aSname;}
    public void setYear(int aBYear) throws NullPointerException{
        if( aBYear < 0 ){
            throw new NullPointerException("Illegal index!!!");
        }else{
            birthYear=aBYear;
        }
    }
    
    public void setGender( String gndr ){ gender = gndr; }
    
    public String toString( ){
        return String.format( "%-15s\n%-10s%s\n%-10s%s\n%-10s%d\n%-10s%s\n",
                "The person is ", "Name: ",name, "Surname: ",surname, "Birthday: "
                                                ,birthYear, "Gender: ", gender);
        
    }
    
    
}
