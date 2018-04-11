
package pkg111044069hw08;

import java.util.Scanner;

/**package
 * @author Ramazan Sakin  -- 111044069
 */
public class Main {

    
    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        
        String initState;
        int searchType;
        int stepNum = 0;
        
        BreadthFirstSearch search1;
        Graph puzzleGraph = new ListGraph(1000, false);
        
        // search all statements
        
        DepthFirstSearch search2 = new DepthFirstSearch(puzzleGraph);

        Scanner input=new Scanner(System.in);
        System.out.println("Please enter the initial node in row-wise( use for space )");
        initState = input.nextLine();
        
        System.out.println( "Please enter the search type (1 for BFS, 2 for DFS)" );
        searchType = input.nextInt();
        
        if( searchType == 1 ){
            search1 = new BreadthFirstSearch();
            stepNum = ListGraph.edgeNum;
        
        }else{
            // depthFirst search doesn_t work !!!
            //search2.depthFirstSearch(1);    // starts 1 for rewieving 
        }
        
        if( ListGraph.edgeNum != -1 )
            System.out.printf("Your solution takes %d steps\n", stepNum );
        else
            System.out.println("The result was not found!!!");
        
        
    }
    
    
    
    
}
