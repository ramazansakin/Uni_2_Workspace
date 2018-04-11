import java.util.*;
/**
 * Graph data structure.
 *
 * @author Orhan Aksoy
 */
public class Graph {

    /** The list of edge lists per node */
    private ArrayList<LinkedList<Edge>> edgeList = new ArrayList<LinkedList<Edge>>();

    /**
     * Adds an edge to the graph
     *
     * @param edge The edge to be added.
     */
    public void addEdge(Edge edge) {
        /*
         * Check the source node for the new edge. If the list for the source that
         * this edge originates hasn't been created yet, create all the lists up
         * to this node.
         */
        while (edge.getSource() >= edgeList.size()) {
            edgeList.add(new LinkedList<Edge>());
        }
        /* Add the edge to the list of the source */
        edgeList.get(edge.getSource()).add(edge);
    }

    /**
     * REturns the number of edges originating at a pixel
     * @param source The pixel id of the source
     * @return The number of edges connected to this source.
     */
    public int edgeCount(int source) {
        if (source < edgeList.size()) {
            return edgeList.get(source).size();
        }
        return 0;
    }

    /**
     * Returns an iterator for the edges *
     * @param source The source from which the edge iterator will return edges.
     * @return The Iterator object for the edges.
     */
    public Iterator<Edge> edgeIterator(int source) {
        if (source < edgeList.size()) {
            return edgeList.get(source).iterator();
        }
        return null;
    }

    /**
     * Represents a relationship between two vertices.
     */
    public static class Edge {
        /** The source node id of the edge */
        private int dest;
        /** The destination node id of the edge */
        private int source;
        /** The weight of the edge */
        private int weight;


        /**
         * Constructs an edge between two vertices: source and destination
         * @param source Source vertex
         * @param dest Destination vertex
         */
        public Edge(int source, int dest, int weight) {
            this.source = source;
            this.dest = dest;
            this.weight = weight;
        }

        /**
         * Returns the source node id of the edge.
         * @return The source node id.
         */
        public int getSource() {
            return source;
        }
        /**
         * Returns the destination node id of the edge.
         * @return The destination node id.
         */
        public int getDestination() {
            return dest;
        }
        /**
         * Returns the weight  of the edge.
         * @return The weight  of the edge.
         */
        public int getWeight() {
            return weight;
        }
        /** Return true if two edges are equal. Edges
            are equal if the source and destination
            are equal. Weight is not conidered.
            @param obj The object to compare to
            @return true if the edges have the same source
            and destination
        */
        public boolean equals(Object obj) {
            if (obj instanceof Edge) {
                Edge edge = (Edge) obj;
                return (source == edge.source && dest == edge.dest);
            } 
            return false;
        }

        /** Return a hash code for an edge.  The hash
            code is the source shifted left 16 bits
            exclusive or with the dest
            @return a hash code for an edge
        */
        public int hashCode() {
            return (source << 16) ^ dest;
        }
    };
}
