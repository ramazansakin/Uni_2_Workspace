package HW9_121044001_p04;
import HW9_121044001_p01.Person;
import HW9_121044001_p02.Family;
import HW9_121044001_p03.GUI;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;//Packages used
import java.awt.Dimension;
import java.awt.FlowLayout;
import javax.swing.*;
import javax.swing.event.*;
import java.util.Vector;
public class Handler implements ActionListener,ListSelectionListener {
	//This class is an ActionListener and ListSelectionListener
	public JList personList;
	public JScrollPane personListScroll;
	public JButton addPerson;
	public JButton removePerson;
	public JButton informationPerson;
	public JButton changePerson;
	public DefaultListModel personNames;
	public Vector<Person> persons;
	public JList familyList;//Components used comes from GUI
	public JScrollPane familyListScroll;
	public JButton addFamily;
	public JButton removeFamily;
	public DefaultListModel familyNames;
	public Vector<Family> families;
	public Handler(GUI objects){
		personList = objects.personList;
		addPerson = objects.addPerson;
		removePerson = objects.removePerson;
		changePerson = objects.changePerson;
		informationPerson = objects.informationPerson;
		personNames = objects.personNames;
		persons = objects.persons;
		familyList = objects.familyList;
		addFamily = objects.addFamily;//Taking components
		removeFamily = objects.removeFamily;
		familyNames = objects.familyNames;
		families = objects.families;
		addFamily.addActionListener(this);
		removeFamily.addActionListener(this);
		familyList.addListSelectionListener(this);
		removePerson.addActionListener(this);
		addPerson.addActionListener(this);//Adding Listeners
		informationPerson.addActionListener(this);
		changePerson.addActionListener(this);
	}
	public void valueChanged(ListSelectionEvent listSelectionEvent){
		//when there is a selection in familyList
		personNames.clear();//clears personList
		persons.clear();
		if(familyList.getSelectedIndex()>=0){
			addPerson.setEnabled(true);//If there is a selected Family
			removePerson.setEnabled(true);
			informationPerson.setEnabled(true);//Enables Person buttons
			changePerson.setEnabled(true);
			persons.add(families.elementAt(familyList.getSelectedIndex()).getFather());
			personNames.addElement(families.elementAt(familyList.getSelectedIndex()).getFather().getName());
			persons.add(families.elementAt(familyList.getSelectedIndex()).getMother());
			personNames.addElement(families.elementAt(familyList.getSelectedIndex()).getMother().getName());
			for(int i=0;i<families.elementAt(familyList.getSelectedIndex()).getNumOfChildren();i++){
				persons.add(families.elementAt(familyList.getSelectedIndex()).at(i));//adds all family members to List
				personNames.addElement(families.elementAt(familyList.getSelectedIndex()).at(i).getName());
			}
		}
		else{
			addPerson.setEnabled(false);
			removePerson.setEnabled(false);//If there is no selected family disables Person Buttons
			informationPerson.setEnabled(false);
			changePerson.setEnabled(false);
		}
	}	
	public void actionPerformed(ActionEvent event){
		//Nutton Listener
		if(event.getSource()==addFamily){//if pressed to the addFamily Button
			String fname = JOptionPane.showInputDialog("Enter the name of father:");
			if(fname==null||fname.equals(""))
				return;
			String fsyear = JOptionPane.showInputDialog("Enter the year of birth of father:");
			if(fsyear==null||fsyear.equals(""))
				return;//Gets information about Family
			int fyear = Integer.parseInt(fsyear);
			String mname = JOptionPane.showInputDialog("Enter the name of mother:");
			if(mname==null||mname.equals(""))
				return;
			String msyear = JOptionPane.showInputDialog("Enter the year of birth of mother:");
			if(msyear==null||msyear.equals(""))
				return;
			int myear = Integer.parseInt(msyear);
			String surname = JOptionPane.showInputDialog("Enter the family name:");
			if(surname==null||surname.equals(""))
				return;
			try{
				families.add(new Family(new Person(fname,surname,fyear,'m'),new Person(mname,surname,myear,'f')));
				familyNames.addElement(surname);//Tries to create one
			}
			catch (Throwable e) {//if there is an error print its massage to screen
				JOptionPane.showMessageDialog(new JFrame(),e.getMessage());
			}
		}
		else if(event.getSource()==removeFamily){//remove family
			if(familyList.getSelectedIndex()>=0){//if there is a selected family
				families.remove(familyList.getSelectedIndex());
				familyNames.remove(familyList.getSelectedIndex());//removes it
			}
		}
		else if(event.getSource()==addPerson){//add person
			String[] options = {"Male","Female"};
			String name = JOptionPane.showInputDialog("Enter the name of new person:");
			if(name==null||name.equals(""))//Gets information about new person
				return;
			String syear = JOptionPane.showInputDialog("Enter the year of birth of new person:");
			if(syear==null||syear.equals(""))
				return;
			int year = Integer.parseInt(syear);
			int result = JOptionPane.showOptionDialog(new JFrame(),"What is the sex of new Person","",JOptionPane.YES_NO_OPTION,JOptionPane.QUESTION_MESSAGE,null,options,options[0]); 
			char sex;
			if(result==JOptionPane.YES_OPTION)
				sex = 'm';
			else if(result==JOptionPane.NO_OPTION)
				sex = 'f';
			else
				return;
			Person newChild;
			try{//tries to create it and adds it to selected family
				newChild = new Person(name,families.elementAt(familyList.getSelectedIndex()).getFather().getSurname(),year,sex);
				persons.add(newChild);
				personNames.addElement(name);
				families.elementAt(familyList.getSelectedIndex()).add(newChild);
			}
			catch (Throwable e) {//if there is an error prints the error massage
				JOptionPane.showMessageDialog(new JFrame(),e.getMessage());				
			}
		}
		else if(event.getSource()==removePerson){//remove person
			if(personList.getSelectedIndex()>=2){//if the person is not father or mother
				families.elementAt(familyList.getSelectedIndex()).remove(personList.getSelectedIndex() - 2);
				persons.remove(personList.getSelectedIndex());//removes it from family
				personNames.remove(personList.getSelectedIndex());
			}
		}
		else if(event.getSource()==informationPerson){//information
			if(personList.getSelectedIndex()>=0)//prints the information about selected person
				JOptionPane.showMessageDialog(new JFrame(),persons.elementAt(personList.getSelectedIndex()));
		}
		else if(event.getSource()==changePerson){//change person
			if(personList.getSelectedIndex()>=0){
				String[] options = {"Male","Female"};
				String name = JOptionPane.showInputDialog("Enter the name of new person:",persons.elementAt(personList.getSelectedIndex()).getName());
				if(name!=null&&!name.equals(""))//Change the info of person selected
					persons.elementAt(personList.getSelectedIndex()).setName(name);
				String syear = JOptionPane.showInputDialog("Enter the year of birth of new person:",persons.elementAt(personList.getSelectedIndex()).getYearOfBirth());
				if(syear!=null&&!syear.equals("")){
					int year = Integer.parseInt(syear);
					persons.elementAt(personList.getSelectedIndex()).setYearOfBirth(year);
				}
				int i = 0;
				if(persons.elementAt(personList.getSelectedIndex()).getSex()=='f')
					i = 1;
				int result = JOptionPane.showOptionDialog(new JFrame(),"What is the sex of new Person","",JOptionPane.YES_NO_OPTION,JOptionPane.QUESTION_MESSAGE,null,options,options[i]); 
				char sex;
				if(result==JOptionPane.YES_OPTION)
					sex = 'm';
				else if(result==JOptionPane.NO_OPTION)
					sex = 'f';
				personNames.set(personList.getSelectedIndex(),name);
			}
		}
	}
}