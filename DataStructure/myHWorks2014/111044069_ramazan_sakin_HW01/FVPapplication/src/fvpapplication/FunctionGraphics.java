/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package fvpapplication;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Graphics;
import java.awt.Polygon;
import javax.swing.JPanel;

/**
 * @author ramazan
 */
public class FunctionGraphics extends JPanel{
    
    private String[] functionInfos;
    private int numOfFunc;
    
    public FunctionGraphics() {
        setLayout(new BorderLayout());
        functionInfos = new String[60];
        
    }
    
    
    public void paintComponent(Graphics g ){
        super.paintComponent(g);
        
        //black main lines  of x and y 
        g.drawLine( 20, getHeight()/2, getWidth()-20, getHeight()/2);
        g.drawLine(getWidth()/2, 20, getWidth()/2, getHeight()-20);
        
        // gray lines
        g.setColor(Color.lightGray);
        g.drawLine( 20, getHeight()/2+getWidth()/6, getWidth()-20, getHeight()/2+getWidth()/6);
        g.drawLine(getWidth()/2+getWidth()/6, 20, getWidth()/2+getWidth()/6, getHeight()-20);
        
        g.drawLine( 20, getHeight()/2-getWidth()/6, getWidth()-20, getHeight()/2-getWidth()/6);
        g.drawLine(getWidth()/2-getWidth()/6, 20, getWidth()/2-getWidth()/6, getHeight()-20);
        
        g.setColor(Color.black);
        g.drawString("Y", getWidth()/2+5, 25);
        g.drawString("X", 20, getHeight()/2-5);
        g.drawString("0", getWidth()/2+3, getHeight()/2+12);
        
         for( int i=0; i<numOfFunc/4;++i ){
             setColor(functionInfos[i*4+3], g);
             setFunction(functionInfos[i*4], functionInfos[4*i+1], functionInfos[4*i+2], g);
         }
       
    }
    
    public void setColor( String color, Graphics theGrap ){
        
        switch( color ){
            case "red":
                theGrap.setColor(Color.red);
                break;
            case "blue":
                theGrap.setColor(Color.blue);
                break;
            case "green":
                theGrap.setColor(Color.green);
                break;
            case "yellow":
                theGrap.setColor(Color.yellow);
                break;
            case "orange":
                theGrap.setColor(Color.orange);
                break;
            case "cyan":
                theGrap.setColor(Color.cyan);
                break;
            case "magenta":
                theGrap.setColor(Color.magenta);
                break;
            default:
                theGrap.setColor(Color.black);  //default color
        }
   
    }
    
    void setFunction( String funcName, String fLowBound, String fUpBound, Graphics g   ){
        Polygon p = new Polygon();
        int mult = getWidth()/15; // to show functions bigger
        
        // convert String to double for function's range
        double low = Double.parseDouble(fLowBound);
        double up = Double.parseDouble(fUpBound);
        
        switch( funcName ){
            case "x":     // x
                for( double x=low; x<=up; x+=0.5 )
                    p.addPoint( (int)(mult*x)+getWidth()/2, -(int)(mult*x)+getHeight()/2 );
                break;
            case "x^2":     // x^2
                for (double x = low; x <= up; x+=0.1)
                    p.addPoint( (int)(mult*x)+getWidth()/2, (int)(-mult*Math.pow(x, 2))+getHeight()/2 );
                break;
            case "e^x":     // e^x   exp(x)
                for (double x = low; x <= up; x+=0.1 )
                    p.addPoint( (int)(mult*x)+getWidth()/2, (int)(-mult*(Math.exp(x))) + getHeight()/2);
                break;    
            case "log(x)":     // log(x)
                for( double x=low; x<=up; x+=0.1 )
                    p.addPoint( (int)(x*mult)+getWidth()/2, (int)(-mult*Math.log(x))+getHeight()/2);
                break;
            case "2^x":     // 2^x
                for( double x=low; x<=up; x+=0.1  )
                    p.addPoint( (int)(mult*x)+getWidth()/2, (int)(-mult*Math.pow(2, x)) + getHeight()/2 );
                break;
            case "sin(x)":     // sin(x)
                for (double x = low; x <= up; x+=0.1)
                    p.addPoint((int)(x*mult) +getWidth()/2 , getHeight()/2-(int)(Math.sin(x)*mult));
                break;    
            case "cos(x)":     // cos(x)
                for (double x = low; x <= up; x+=0.1 )
                    p.addPoint( (int)(x*mult) +getWidth()/2, getHeight()/2-(int)(Math.cos(x)*mult) );
                break;
            case "cot(x)":     // cot(x)
                for (double x = low; x <= up; x+=0.1){
                    p.addPoint((int)(x*mult) +getWidth()/2 , getHeight()/2-(int)(mult*(1/Math.tan(x)) ) );
                }
                break;
            case "tan(x)":     // tan(x)
                for ( double x = low; x <= up; x+=0.1 ){
                    p.addPoint( (int)(x*mult) +getWidth()/2 , getHeight()/2-(int)(mult*Math.tan(x)) );
                }
                break;
            case "sqrt(x)":     // tan(x)
                for ( double x = low; x <= up; x+=0.1 ){
                    p.addPoint( (int)(x*mult) +getWidth()/2 , getHeight()/2-(int)(mult*Math.sqrt(x)) );
                }
                break;
            default:
                System.out.printf("There is no function like %s!!!\n", funcName );
        }
        // draw the function to Panel
        g.drawPolyline(p.xpoints, p.ypoints, p.npoints);
   
    }

    public void getFuncInfos( String[] datas, int num ){
        functionInfos = datas;
        numOfFunc=num;
    }    
    
    
}