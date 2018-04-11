package pkg111044069hw08;

import java.util.*;
import java.io.*;

/** A ListGraph is an extension of the AbstractGraph abstract class
*   that uses an array of lists to represent the edges.
*   @author Koffman and Wolfgang
*/

public class ListGraph
    extends AbstractGraph {

  // Data Field
  /** An array of Lists to contain the edges that
      originate with each vertex. */
    private List < Edge > [] edges;
    private String[] stat;
    static int edgeNum = 0;
    private int numVer;
  
  /** Construct a graph with the specified number of
      vertices and directionality.
      @param numV The number of vertices
      @param directed The directionality flag
   */
  public ListGraph(int numV, boolean directed) {
    super(numV, directed);
    edges = new List[numV];
    for (int i = 0; i < numV; i++) {
      edges[i] = new LinkedList < Edge > ();
    }
    
    directed = false;
    stat = new String[numV];
    numVer = numV;
    
    // recursive function to create possible states 
    createGrapStates( "123456780" );
    
  }

  /** Determine whether an edge exists.
      @param source The source vertex
      @param dest The destination vertex
      @return true if there is an edge from source to dest
   */
  public boolean isEdge(int source, int dest, String status ) {
    return edges[source].contains(new Edge(source, dest, status ));
  }

  /** Insert a new edge into the graph.
      @param edge The new edge
   */
  public void insert(Edge edge) {
      
    edges[edge.getSource()].add(edge);
    if (!isDirected()) {
        
      edges[edge.getDest()].add(new Edge(edge.getDest(),
                                         edge.getSource(), edge.state ));
    }
  }

  public Iterator < Edge > edgeIterator(int source) {
    return edges[source].iterator();
  }

  /** Get the edge between two vertices. If an
      edge does not exist, an Edge with a weight
      of Double.POSITIVE_INFINITY is returned.
      @param source The source
      @param dest The destination
      @return the edge between these two vertices
   */
  public Edge getEdge(int source, int dest, String Status ) {
    Edge target =
        new Edge(source, dest, Status );
    for (Edge edge : edges[source]) {
      if (edge.equals(target))
        return edge; // Desired edge found, return it.
    }
    // Assert: All edges for source checked.
    return target; // Desired edge not found.
  }


    private void createGrapStates(String state ) {
        
        char tempC = 0;
        char tempC2;
        
        // creating possible states 
        for (int i = 1; i < 9; i++) {
            for (int j = i+1; j < 9; j++) {
                String copyString = new String(state);
                tempC = copyString.charAt(i);
                tempC2 = copyString.charAt(j);
                copyString.replace(tempC, tempC2);
                Edge e = new Edge( edgeNum+i , edgeNum+j, copyString );
                insert(e);
                stat[edgeNum] = new String(copyString);
            }
        }
        edgeNum+=9;
        
        String nextState = new String(state);
        for (int i = 0; i < 8; i++){
            tempC = nextState.charAt(0);
            nextState.replace( nextState.charAt(i), nextState.charAt(i+1) );
        }
        nextState.replace(nextState.charAt(8), tempC );
        
        // compare first state
        if( !copmareStrings(state , "123456780") )  //  - 123456780 - first state
            createGrapStates(nextState);
        
    }
    
    public boolean copmareStrings( String s1, String s2 ){
        
        for (int i = 0; i < s1.length() ; i++) {
            if (s1.charAt(i) != s2.charAt(i) )
                return false;
        }
        
      return true;
    }

    
    @Override
    public boolean isEdge(int source, int dest) {
        return true;
    }

    
    @Override
    public Edge getEdge(int source, int dest) {
        return null;
    }
    
    public void search(  ){
        
        
    }
    

}

