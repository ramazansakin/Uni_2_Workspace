import java.util.Comparator;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Iterator;
import java.util.LinkedList;
import java.util.PriorityQueue;
import java.util.Set;

/**
 * Class for running Dijkstra's shortest path
 * algorithm on Graph2D graphs.
 *
 * @author Orhan Aksoy
 */
public class DijkstraShortestPath {

    /** The graph on which the algorithm will run */
    private Graph2D graph = null;
    /**
     * The comparator object for comparing distances of two pixel
     * nodes from the starting point.
     */
    private CompareDistance compDistance = new CompareDistance();

    /** The distance map holding (node, distance from starting point) pairs */
    private HashMap<Integer, Integer> distanceMap = new HashMap<Integer, Integer>();
    /** The predecessor map holding (node, predecessor) pairs */
    private HashMap<Integer, Integer> prevNodeMap = new HashMap<Integer, Integer>();

    /** The S set containing the processed nodes */
    private Set<Integer> S = new HashSet<Integer>();

    /**
     * The (V-S) set containing the nodes to be processed, having
     * a distance value from the starting point less than infinite. This set of
     * nodes are stored in a Heap (PriorityQueue) for performance gain
     * in getting the node with the smallest distance.
     */
    private PriorityQueue<Integer> vMinusS = new PriorityQueue<Integer>(1000, compDistance);

    /** The rest of the (V-S) set from the Dijkstra Algorithm that also contain
     * the nodes to be processed, but whose distances from the starting point
     * are infinite. The only requirements on this set are 'add' and 'remove'
     * operations, so they're implemented as a hash set to improve performance.
     */
    private Set<Integer> vMinusS_far = new HashSet<Integer>();

    /** The starting node */
    private int start = -1;

    /**
     * Constructs a DijkstraShortestPath object using the provided Graph2 object.
     * @param graph The Graph2D object on which the algorithm will run.
     */
    public DijkstraShortestPath(Graph2D graph) {
        this.graph = graph;

   }

    /**
     * Runs the Dijkstra's shortest path algorithm on the graph with the source
     * point provided by the user.
     *
     * @param source The index to the source node in the graph.
     */
    public void calculate(int source) {
        start = source;

        /** Reset the containers */
        vMinusS.clear();
        S.clear();
        distanceMap.clear();
        prevNodeMap.clear();

        Iterator<Graph2D.Pixel> pixelIt = graph.pixelIterator();

        int pixelIndex = 0;

        // Put all pixels in the graph other than the source into the
        // vMinus_far set (which have infinite distance from the source)
        // Also put -1 for distance and predecessor values of all nodes.

        while (pixelIt.hasNext()) {
            Graph2D.Pixel p = pixelIt.next();
            if (source == pixelIndex) {
                vMinusS.add(pixelIndex);
            } else {
                vMinusS_far.add(pixelIndex);
            }
            distanceMap.put(pixelIndex, -1);
            prevNodeMap.put(pixelIndex, -1);
            ++pixelIndex;
        }



        // For all nodes connected directly to the starting node, set the
        // distance and predecessor values. Also, remove them from the vMinusS_far
        // set and put them into the vMinusS set since their distances
        // are not infinite anymore.

        Iterator<Graph2D.Edge> edgeIt = graph.edgeIterator(start);

        while (edgeIt.hasNext()) {
            Graph2D.Edge edge = edgeIt.next();
            int dest = edge.getDestination();
            distanceMap.put(dest, edge.getWeight());
            prevNodeMap.put(dest, start);
            vMinusS_far.remove(dest);
            vMinusS.add(dest);
        }
        distanceMap.put(start, 0);
        prevNodeMap.put(start, start);

        /* The algorithm is initialized now. 
         * The loop below runs the algorithm as described :
         *
         * 1. Get the node in the vMinusS set which has the smallest distance
         *    to the starting point
         * 2. Add it to the S set.
         * 3. Using the node just added to the S set, update the distance and
         *    predecessor maps. Following the update, the updateDistances method
         *    also determines the new connected nodes and removes them from
         *    the set vMinusS_far and puts them into the binary heap vMinusS.
         * 4. This loop continues until all of the nodes in the vMinusS set
         *    is processed.
         *
         */
        Integer id = vMinusS.poll();
        S.add(id);
         while (vMinusS.size() > 0) {
            id = vMinusS.poll();
            S.add(id);
            updateDistances(id);
        }
    }

    /**
     * This method checks all nodes connected to the node specified, and
     * determines if the distance of these nodes from the starting point
     * passing to itself is less than their previous distance values on
     * the distance map. If the new distance is smaller, than it updates the
     * distance and predecessor maps.
     * If some of these new nodes had infinite distances before, than it
     * replaces them from the vMinusS_far set into the vMinusS heap.
     *
     * @param source The node through which this new calculations will be done.
     */
    private void updateDistances(int source) {
        Iterator<Graph.Edge> it = graph.edgeIterator(source);
        int currentDistance = distanceMap.get(source);

        // Current distance should never be -1 because this method is only
        // called for nodes from vMinusS set.
        assert (currentDistance != -1);

        // For all nodes connected to this node, check their new distances
        // and update them on the tables if necessary.
        while (it.hasNext()) {
            Graph.Edge edge = it.next();
            int dest = edge.getDestination();

            // If the target is the starting point, then skip.
            if (dest == this.start) {
                continue;
            }

            // The current distance of this connected node on the distance table
            int targetDistance = distanceMap.get(dest);
            // The (possible) new distance of this connected node passing through us.
            int distanceThroughSrc = edge.getWeight() + currentDistance;

            // If the target distance is infinite (represented by -1) or
            // the new target distance is less, then update the tables.
            if ((targetDistance == -1) || (distanceThroughSrc < targetDistance)) {

                // Update the distance map.
                distanceMap.put(dest, distanceThroughSrc);

                // Update the predecessor map
                prevNodeMap.put(dest, source);

                // If this node wasn't connected before, replace it from the
                // vMinusS_far set into the vMinusS heap.
                if (targetDistance == -1) {
                    vMinusS_far.remove(dest);
                    vMinusS.add(dest);
                }
            }

        }
    }

    /**
     * This method returns the shortest path of a node from the starting point.
     * It should only be called following a call to 'calculate(source)'.
     *
     * @param destination The destination to which the path will be returned.
     * @return A LinkedList of POints representing the shortest path from the
     * start to the destination.
     */
    public LinkedList<Integer> getShortestPath(int destination) {
        LinkedList<Integer> path = new LinkedList<Integer>();

        int destId = prevNodeMap.get(destination);
        while ( (destId != start) && (destId != -1)  ) {
            path.push(destId);
            destId = prevNodeMap.get(destId);
        }
        
        return path;
    }


    /**
     * The comparator object used by the binary heap.
     */
    public class CompareDistance implements Comparator<Integer> {
        public int compare(Integer left, Integer right) {
            return distanceMap.get(left) - distanceMap.get(right);
        }
            
    }

    /**
     * Prints out the current output.
     */
    public void print() {
        System.out.println("Origin: " + graph.getPixel(start).getLocation());
        System.out.println("Edges:");
        Iterator<Graph2D.Pixel> pixelIt = graph.pixelIterator();
        int id = 0;
        while (pixelIt.hasNext()) {
            pixelIt.next();
            System.out.print("Pixel " + (id) + ": ");
            Iterator<Graph2D.Edge> edgeIt = graph.edgeIterator(id++);
            while (edgeIt.hasNext()) {
                Graph2D.Edge edge = edgeIt.next();
                System.out.print(" -> " + edge.getDestination() + "(w=" + edge.getWeight() + "), ");
            }
            System.out.println();
        }

        Iterator<Integer> it = distanceMap.keySet().iterator();
        while (it.hasNext()) {
            Integer key = it.next();
            System.out.println(" Distance: " +  distanceMap.get(key) + ", prevNode: " + prevNodeMap.get(key).intValue());
        }

     }
}
