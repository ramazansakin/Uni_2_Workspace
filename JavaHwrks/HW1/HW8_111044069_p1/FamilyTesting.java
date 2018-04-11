/**
 * @author ramazan
 */
package HW8_111044069_p1;

public class FamilyTesting {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        try{
            System.out.println("#####################################################");
            System.out.println("Creating a Father and a Mother as Person object.");
            System.out.println("Printing with toString methods: ");
            
            Person Father1 = new Person("Huseyin", "SAKIN", 1968, "male");
            System.out.println(Father1);
            Person Mother1 = new Person("Saadet","SAKIN",1970,"female");
            System.out.println(Mother1);
            System.out.println("#####################################################");
            
            System.out.println("Creating a Person with default constructor: ");
            Person Father3 = new Person();
            System.out.println(Father3);
            
            System.out.println("#####################################################");
            System.out.println("Creating a Person eith copy-constructor :");
            Person Father2 = new Person(Father1);
            System.out.println(Father2);
            System.out.println("#####################################################");
            
            System.out.println("Creating some Person as child  and adding them to the family: ");
            Person child1 = new Person("Mustafa", "SAKIN", 2007, "male");
            System.out.println(child1);
            Family aFamily = new Family(Father2, Mother1);
            aFamily.add(child1);
            Person child2 = new Person("Aysegul", "SAKIN", 1994, "female");
            aFamily.add(child2);
            Person child3 = new Person("Huzeyfe", "SAKIN", 1993, "male");
            aFamily.add(child3);
            System.out.println("The first family is:");
            System.out.println(aFamily.getFather());
            System.out.println(aFamily.getMother());
            
            System.out.println("The children are :");
            for( int i=0; i<aFamily.getNumOfChildren(); ++i ){
                System.out.printf("%d.Child :\n",i+1);
                System.out.println(aFamily.at(i));      // as using at() function 
            }
            
            System.out.println("#####################################################");
            Person Father4 = new Person("Yilmaz", "EDIS",1985 ,"male" );
            Person Mother2 = new Person("Sümeyye", "EDIS", 1987, "female");
            Family Family2 = new Family( Father4,Mother2);
            // add some childeren to new family 
            Person child5 = new Person("Seyfullah", "EDIS", 2010, "male");
            Person child6 = new Person("Hatice", "EDIS", 2011, "EDIS");
            
            Family2.add(child5);
            Family2.add(child6);
            //Second - Family
            System.out.println("The second family :");
            System.out.println(Family2.getFather());
            System.out.println(Family2.getMother());
            
            for( int j=0; j<Family2.getNumOfChildren(); ++j ){
                System.out.printf("%d.Child is:\n",j+1);
                System.out.println(Family2.at(j));
            }
            System.out.println("#####################################################");
            System.out.println("Testing equals function for comparing two families: ");
            System.out.println("Test whether Family1 and Family2 is equal:");
            if( aFamily.equals(Family2) )
                System.out.println("The families are equal with each other.");
            else
                System.out.println("The families are not equal with each other.");
            System.out.println("#####################################################");
            System.out.println("Creating a new family with copy-constructor and "
                    + "\ntest them whether are equal or not: ");
            Family Family3 = new Family(aFamily);
            System.out.println("Family3 is: ( created with copy-const )");
            System.out.println(Family3.getFather());
            System.out.println(Family3.getMother());
            
            for( int i=0; i<aFamily.getNumOfChildren(); ++i ){
                System.out.printf("%d.Child is:\n",i+1);
                System.out.println(Family3.at(i));
            }
            
            System.out.println("And If we test in now:");
            if( Family3.equals(aFamily) )
                System.out.println("The families are equal with each other.");
            else
                System.out.println("The families are not equal with each other.");
            
            System.out.println("#####################################################");
            System.out.println("Creating a new Family and search it at Families array:");
            // Families array
            Family[] Families = new Family[3];
            Families[0] = aFamily;
            Families[1] = Family2;
            Families[2] = Family3;
            
            Person Father5 = new Person("Ali", "Bayar", 1982, "male");
            Person Mother3 = new Person("Sevda", "Bayar", 1985, "female");
            Family Family4 = new Family(Father5, Mother3);
            //number of the families were created so far
            System.out.println("#####################################################");
            System.out.printf("Number of the families is %d\n",Family.getNumberOfFamily());
            System.out.println("#####################################################");
            
            if( searchFamily(Father5, Mother3, Families))
                System.out.println("The families has relation with one of Family in Families");
            else    
                System.out.println("The families has not relation with one of Family in Families");
            System.out.println("#####################################################");
            System.out.println("Testing for Exception Handling:");
            System.out.println("If we call the Person constructor with negative birthyear");
            Person anyPerson = new Person("Ali", "Tek", -1234, "male");
            
            System.out.println("#####################################################\n");
            
            // Because of after first catching handling these codes can not run,
            // So this Exception can not be seen at the output screen!!
            System.err.println("When a Person who may be a man is tried to declare as 'female':");
            Person aaPerson = new Person("Salih", "Durmus", 1980, "female");
            Family Family5 = new Family(aaPerson, Mother3);
            
            
        }catch( NullPointerException e){
            System.out.printf("The exception is %s\n", e.toString());
        }finally{
            System.out.println("Finally method is called!!!");
        }
        
        
    }
   
    /**
     * @param aFather
     * @param theMother
     * @param Families
     * @return
     */
    public static boolean searchFamily( Person aFather, Person theMother,
                                        Family Families[]                 ){

        for( int i=0; i<3 ; ++i ){  // 3 is number of families in the FAmilies array
            if( aFather.getSurname() == Families[i].getFather().getSurname() ||
                theMother.getSurname() == Families[i].getMother().getSurname()  ){
                    return true;
            }     
        }
    return false;
}
}