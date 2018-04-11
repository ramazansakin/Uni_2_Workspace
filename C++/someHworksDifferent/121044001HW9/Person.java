package HW9_121044001_p01;
public class Person{
	private String name;
	private String surname;
	private int yearOfBirth;
	private char sex;
	public Person()throws Throwable{//No parameter constructer
		this("No Name","No Surname",1985,'m');//calls other constructer
	}
	public Person(String pName,String pSurname,int pYearOfBirth,char pSex) throws Throwable{
		name = pName;//Sets name and surname
		surname = pSurname;
		if(pYearOfBirth < 1900)
			throw new Throwable("Birth year can't be lower than 1900");
		yearOfBirth = pYearOfBirth;//Controls the input if it is invalid throws exception
		if(pSex != 'm' && pSex != 'f')
			throw new Throwable("Sex can't be other than 'm' or 'f'");
		sex = pSex;
	}
    //---------GETTERS-----------
	public String getName(){
		return name;
	}

	public String getSurname(){
		return surname;
	}

	public int getYearOfBirth(){
		return yearOfBirth;
	}

	public char getSex(){
		return sex;
	}
	//-----------SETTERS---------
	public boolean setName(String pName){
		name = pName;
		return true;
	}

	public boolean setSurname(String pSurname){
		surname = pSurname;
		return true;
	}

	public boolean setYearOfBirth(int pYearOfBirth){
		if(pYearOfBirth<1900)
			return false;
		yearOfBirth= pYearOfBirth;
		return true;
	}

	public boolean setSex(char pSex){
		if(pSex!='m'&&pSex!='f')
			return false;
		sex=pSex;
		return true;
	}

	public String toString(){//toString method
		return name + " " + surname + " " + yearOfBirth + " " + sex;
	}
}