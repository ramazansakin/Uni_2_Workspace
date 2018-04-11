package HW9_121044001_p02;
import HW9_121044001_p01.Person;
public class Family{
	private Person father;
	private Person mother;
	private Person[] children;
	private int numOfChildren;
	private static int numOfFamilies=0;
	public Family(Person fFather,Person fMother)throws Throwable{
		if(fFather.getSex()!='m'||fMother.getSex()!='f')
			throw new Throwable("Invalid input for Family constructer");
		father = fFather;
		mother = fMother;
		numOfChildren=0;
		children = new Person[5];
		numOfFamilies++;
	}
	//--------GETTERS------------
	public Person getMother(){
		return mother;
	}

	public Person getFather(){
		return father;
	}

	public int getNumOfChildren(){
		return numOfChildren;
	}

	public static int getNumOfFamilies(){
		return numOfFamilies;
	}
	//Takes two families return true if they are the same families false otherwise
	public boolean compare(Family other){
		if(father!=other.getFather()||mother!=other.getMother()){
			return false;
		}
		if(numOfChildren!=other.getNumOfChildren()){
			return false;
		}
		for(int i=0;i<numOfChildren;i++){
			if(at(i)!=other.at(i))
				return false;
		}
		return true;
	}

	public Person at(int index){
		return children[index];//Returns the child at that index
	}

	public boolean add(Person newChild){//Adds new child to the family
		if(numOfChildren==children.length){
			Person[] temp = children;
			children = new Person[children.length * 2];
			for(int i=0;i<temp.length;i++)
				children[i]=temp[i];
		}
		children[numOfChildren]=newChild;
		numOfChildren++;
		return true;
	}

	public void remove(int index){//removes given child
		for(int i=index;i<numOfChildren-1;i++)
			children[i]=children[i+1];
		if(index<numOfChildren)
			numOfChildren--;
	}

	public String toString(){//toString method
		String str = father + "\n" + mother;
		for(int i=0;i<numOfChildren;i++)
			str = str + "\n" + children[i];
		return str;
	}
	protected void finalize () {//decrase the number of living family objects
		numOfFamilies--;
    }
    public static boolean isRelatives(Person p1,Person p2,Family[] families){
    	for(Family family:families)//Find if two given persons are relative
    		if(family.isIn(p1)&&family.isIn(p2))
    			return true;
    	return false;
    }
    public boolean isIn(Person p){
    	if(p==father||p==mother)
    		return true;//Finds if given person is in that family
    	for(int i=0;i<numOfChildren;i++)
    		if(children[i]==p)
    			return true;
    	return false;
    }
}