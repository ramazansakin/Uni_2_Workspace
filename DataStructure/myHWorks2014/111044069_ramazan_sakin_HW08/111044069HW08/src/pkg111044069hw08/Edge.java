
package pkg111044069hw08;

/**
 * @author Ramazan SAKİN
 */
public class Edge {
    
   private int dest;
   private int source;
   protected String state;
   
   // stat is state of the board ( puzzle board )
   public Edge( int dest, int source, String stat ){
       this.dest = dest;
       this.source = source;
       state = new String(stat);
   }

    /**
     * @return the dest
     */
    public int getDest() {
        return dest;
    }

    /**
     * @param dest the dest to set
     */
    public void setDest(int dest) {
        this.dest = dest;
    }

    /**
     * @return the source
     */
    public int getSource() {
        return source;
    }

    /**
     * @param source the source to set
     */
    public void setSource(int source) {
        this.source = source;
    }

   
   
    
    
}

