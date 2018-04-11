import java.awt.Point;
import java.util.*;

/**
 * The polygon class.
 *
 * @author Orhan Aksoy
 */
public class Polygon  {
    /** The list of vertices of the polygon */
    List<Point> vertices = new LinkedList<Point>();

    /**
     * Adds a new vertex to the polygon.
     * @param x The x coordinate of the new vertex.
     * @param y The y coordinate of the new vertex.
     */
    void addVertex(int x, int y) {
        vertices.add(new Point(x, y));
    }

    /**
     * Removes all vertices
     */
    void reset() {
        vertices.clear();
    }

    /**
     * REturns an iterator to the vertices.
     * @return An iterator to the vertices.
     */
    ListIterator vertexIterator() {
        return vertices.listIterator();
    }
    /**
     * REturns the number of vertices.
     * @return The number of vertices.
     */
    public int getVertexCount() {
        return vertices.size();
    }
    
    boolean isPointInside(int x, int y) {
        boolean c = false;
        int nvert = vertices.size();
        int i, j;
        for (i = 0, j = nvert-1; i < nvert; j = i++) {
            if ( ((vertices.get(i).getY() > y) != (vertices.get(j).getY() >y)) &&
                (x < (vertices.get(j).getX()-vertices.get(i).getX()) * (y-vertices.get(i).getY()) / (vertices.get(j).getY()-vertices.get(i).getY()) + vertices.get(i).getX()) )
            c = !c;
        }
        return c;
    }


}
