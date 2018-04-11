/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package fvpapplication;

import java.util.Scanner;

/**
 *
 * @author ramazan
 */
public class FVPapplication {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        // TODO code application logic here
        
        int selection = 0;
        System.out.println("------ Fuction Visualition Program -------");
        System.out.println("Please choose an interface for function visulation\n"
                +"1- Console Userinterface\n" + "2- Graphical Userinterface\n"
                +"3- Exit");
        
        Scanner inUser = new Scanner(System.in);
        
        while( selection == 0 ){
          selection = inUser.nextInt();
          
          if( selection == 1 ){  
            FVPUserInterface consoleUI = new FVPConsoleUI();
            consoleUI.processCommands();
          }else if( selection == 2 ){
              //Grap UI
             FVGUI funcVisGUI = new FVGUI();
          }else if( selection == 3 ){
              System.out.println("The Function Visulation Program was ended...");
              System.exit(0);
          }else{
              selection=0;
              System.out.println("Please enter valid choice(1-3)!\n\n");
          }
        }
    
    
    }
}
