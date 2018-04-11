package HW8_121044001_Main;
import HW8_121044001_p1.Person;
import HW8_121044001_p2.Family;
public class Main{
	public static void main(String[] args) throws Throwable {
		Family[] f=new Family[5];
		for(int i=0;i<5;i++){
			f[i]= new Family(new Person(i + "." + "m",i + ".",1970 + i,'m'),new Person(i + "." + "f",i + ".",1970 + i,'f'));
			for(int j = 0; j<=i;j++)
				f[i].add(new Person(i + "." + j + "." + "c",i + ".", 1990+i+j,'m'));
		}

		System.out.printf("Our families are:\n");
		for(Family a : f)
			System.out.printf("%s\n\n",a);
		System.out.printf("Testing Of Setters Of the Person\n");
		f[0].at(0).setName("Ayşe");
		f[0].at(0).setSurname("Deneme");
		f[0].at(0).setYearOfBirth(1994);
		f[0].at(0).setSex('f');
		System.out.printf("%s\n",f[0].at(0));
		System.out.printf("there are now %d families\n",Family.getNumOfFamilies());
		if(Family.isRelatives(f[1].getFather(),f[1].at(1),f))
			System.out.printf("%s and %s are relatives\n",f[1].getFather(),f[1].at(1));
		else
			System.out.printf("%s and %s are not relatives\n",f[1].getFather(),f[1].at(1));

		if(Family.isRelatives(f[0].getFather(),f[3].at(2),f))
			System.out.printf("%s and %s are relatives\n",f[0].getFather(),f[3].at(2));
		else
			System.out.printf("%s and %s are not relatives\n",f[0].getFather(),f[3].at(2));
	}
	
}