/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package fvpapplication;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Graphics;
import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.InputMismatchException;
import java.util.Scanner;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.swing.JFrame;
import javax.swing.JPanel;

/**
 *
 * @author ramazan
 */
public class FVPConsoleUI implements FVPUserInterface{

    private Scanner readerCommand = null;     
    protected String[] allData;
    private JFrame VisProgram;
    private FunctionGraphics graphs;
    
    public FVPConsoleUI() {
        graphs = new FunctionGraphics();
        readerCommand = new Scanner(System.in);
        allData = new String[40];
        VisProgram = new JFrame();
        allData = new String[50];

    }
    
    @Override
    public void processCommands() {
        int selection=-1;
        
            while(selection == -1){
                System.out.println("1- Read file and Show the functions visualition");
                System.out.println("2- Clear the visualition");
                System.out.println("3- Exit");
             
            try {
                selection = readerCommand.nextInt(); // Read the next choice.
                readerCommand.nextLine(); // Skip trailing newline.
                switch (selection) {
                    case 1:
                        System.out.println("--------------------------------------");
                        readFileandShowFuncVis(selection);
                    break;
                    case 2:
                        System.out.println("--------------------------------------");
                        readFileandShowFuncVis(selection);
                    break;
                    case 3:
                        System.out.println("--------------------------------------");
                        System.out.println("The Function Visulation Program was ended...");
                        System.exit(0);
                    break;
                    default:
                        System.out.println("Invalid selection!!!"+
                                "Please enter again");
                }
                }catch( InputMismatchException e ){
                    System.out.println("You entered invalid selection!");
                    System.out.println("Please enter 1-3 for selection!");
                    readerCommand.nextLine();
                    
                } catch (FileNotFoundException ex) {
                    Logger.getLogger(FVPConsoleUI.class.getName()).log(Level.SEVERE, null, ex);
            }
            selection=-1;
        } 
    }
    
    public void readFileandShowFuncVis(int selection ) throws FileNotFoundException{
        
        int counter=0;
        
        if( selection != 2 ){
        System.out.println("Please enter the file name that has the functions");
        String fileName = readerCommand.nextLine();
        
        BufferedReader reader = new BufferedReader(new FileReader(fileName));
        String[] datas = new String[5]; 
        
        int status=-1;
        while( status == -1 ){
            try {
                String line;
                while( (line = reader.readLine()) != null ){
                    datas = line.split(", ");
                    for( int i=0; i<4; ++i ){
                        allData[counter] = datas[i];
                        ++counter;
                    }
                    status=1;
                }
            } catch (IOException e){
                System.out.println("Invalid File name!!Please, write valid file name");
            }
        }
        
        }
        
        // to remove all graphics
        if( selection == 2)
            counter=0;
        
        graphs.getFuncInfos(allData, counter );          
        VisProgram.add(graphs);
        VisProgram.setSize(600, 600);
        VisProgram.setTitle("VisualizationProgramGUI");
        VisProgram.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        VisProgram.setLocationRelativeTo(null);
        VisProgram.setVisible(true);
        
    }
    
    
}

