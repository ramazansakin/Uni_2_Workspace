package HW9_121044001_p03;
import HW9_121044001_p01.Person;
import HW9_121044001_p02.Family;
import HW9_121044001_p04.Handler;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.Dimension;//Packages used
import java.awt.FlowLayout;
import java.awt.GridLayout;
import javax.swing.BoxLayout;
import javax.swing.*;
import javax.swing.event.*;
import java.util.Vector;

public class GUI extends JFrame{
	public JList personList;//List for persons
	public JScrollPane personListScroll;//ScrollPane ued with personList
	public JButton addPerson;//"Add Person" Button
	public JButton removePerson;//remove Person Button
	public JButton informationPerson;//information button
	public JButton changePerson;//Change Person Button
	public DefaultListModel personNames;//Person Names for the list
	public Vector<Person> persons;//Vector who carries Persons in the list

	public JList familyList;//list for Families
	public JScrollPane familyListScroll;//Scroll Pane used with familyList
	public JButton addFamily;//Add Family Button
	public JButton removeFamily;//Remove Family Button
	public DefaultListModel familyNames;//Family names for the list
	public Vector<Family> families;//Vector which carries Families in the List
	public GUI(){
		super("Murat Yavuz Keskin 121044001 HW09");//title of program
		JPanel familyPanel = new JPanel();//Panel for Family Components
		JPanel personPanel = new JPanel();//Panel for Person Componentss
		JPanel familyButtonPanel = new JPanel();//Panel for Family Buttons
		JPanel personButtonPanel = new JPanel();//Panel for Person Buttons
		Handler eventHandler;//event Handler
		familyNames = new DefaultListModel();
		families = new Vector<Family>();
		addFamily = new JButton("Add Family");
		removeFamily = new JButton("Remove Family");
		familyList = new JList(familyNames);		//Creating Components
		familyListScroll = new JScrollPane(familyList);
		familyListScroll.setPreferredSize(new Dimension (150,250));
		personNames = new DefaultListModel();
		persons = new Vector<Person>();
		addPerson = new JButton("Add Person");
		removePerson = new JButton("Remove Person");
		informationPerson = new JButton("Information");
		changePerson = new JButton("Change Person");
		addPerson.setEnabled(false);
		removePerson.setEnabled(false);
		informationPerson.setEnabled(false);
		changePerson.setEnabled(false);
		personList = new JList(personNames);
		personListScroll = new JScrollPane(personList);
		personListScroll.setPreferredSize(new Dimension(150, 250));
		eventHandler = new Handler(this);

		familyPanel.add(familyListScroll);
		familyButtonPanel.add(addFamily);
		familyButtonPanel.add(removeFamily);//Adding components to Panels
		personPanel.add(personListScroll);
		personButtonPanel.add(addPerson);
		personButtonPanel.add(removePerson);
		personButtonPanel.add(changePerson);
		personButtonPanel.add(informationPerson);
		familyButtonPanel.setPreferredSize(new Dimension(300,25));
		personButtonPanel.setPreferredSize(new Dimension(300,25));//Setting Panel Sizez
		familyButtonPanel.setLayout(new GridLayout(0,1));//Setting Layouts (inf. rows 1 col)
		personButtonPanel.setLayout(new GridLayout(0,2));//(inf. rows 2 cols)
		familyPanel.add(familyButtonPanel);//adding button panels to Panels
		personPanel.add(personButtonPanel);
		familyPanel.setPreferredSize(new Dimension(300,450));//Setting sizes
		personPanel.setPreferredSize(new Dimension(300,450));
		setLayout(new FlowLayout());//setting Layouts
		familyPanel.setLayout(new BoxLayout(familyPanel, BoxLayout.Y_AXIS));
		personPanel.setLayout(new BoxLayout(personPanel, BoxLayout.Y_AXIS));

		add(familyPanel);//Adding Panels to JFrame
		add(personPanel);
		this.setSize(650 , 500);//setting frame size
		setResizable(false);//setting not resizable
		this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);//this mean when you Close Frame it exits application
	}
}