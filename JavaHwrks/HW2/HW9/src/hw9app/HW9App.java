/* 
 * File     : 101044009_P1.java
 * Author   : Sabri Mevis
 * ID       : 101044009
 * Platform : NetBeans IDE 7.3.1
 * 
 * Designed by Sabri Mevis on January 3, 2013, 10:26 AM
 */
package hw9app;

/**
 *
 * @author sabri
 */
public class HW9App {
    
    /** 
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        // TODO code application logic here
        HW9UI interfce = new HW9UI(); //Create an object of UI
        interfce.getjList1().setListData(new String[0]);//Clear default List
        interfce.getjList2().setListData(new String[0]);//Clear default List
        interfce.setVisible(true);//Run interface
        interfce.setTitle("Family Groups ~ Designed by Sabri Meviş"); //Set interface Title
        interfce.fillList(); //fill List
        interfce.handlePersonList(); //listen list
    }    
}
