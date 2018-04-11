import java.awt.*;
import java.util.*;

/**
 * 2D Graph data structure.
 * Extends the Graph by storing Pixels and keeping them in a list.
 *
 * @author Orhan Aksoy
 */
public class Graph2D extends Graph {

    /** The list of pixels */
    private LinkedList<Pixel> pixelList = new LinkedList<Pixel>();

    /** The reference point for the 2D graph */
    private Point reference = null;

    /**
     * The default constructor.
     */
    Graph2D() {

    }

    /**
     * Creates a Graph2D object in reference to a specified point.
     * @param ref
     */
    Graph2D(Point ref) {
        reference = ref;
    }

    /**
     * REturns the reference point of the pixels.
     * @return The reference point of the pixels.
     */
    Point getReference() {
        return reference;
    }

    /**
     * Adds a new pixel to the graph.
     * @param x The x coordinate of the new pixel.
     * @param y The y coordinate of the new pixel
     * @return The index to the added point.
     */
    public int addPoint(int x, int y, int rgb) {
        int id = pixelList.size();
        pixelList.add(new Pixel(new Point(x, y), rgb));
        return id;
    }

    /**
     * Returns the number of pixels in the graph.
     * @return The nmber of pixels in the graph
     */
    public int pixelCount() {
        return pixelList.size();
    }

    /**
     * Returns the number of edges in the graph
     * @return The number of edges in the graph
     */
    public int edgeCount() {
        return pixelList.size();
    }

    /**
     * Returns a pixel object indexed by an id.
     * @param id The id of the pixel to be returned.
     * @return The identified pixel. Null if it does not exist.
     */
    public Pixel getPixel(int id) {
        if (id >= pixelList.size()) { // TODO: Remove for performance?
            return null;
        }
        return pixelList.get(id);
    }

    /**
     * Adds a new edge to the graph
     * @param p1 The source node id of the new edge.
     * @param p2 The destination node id of the new edge.
     */
    public void addEdge(int p1, int p2, int weight) {
        addEdge(new Graph.Edge(p1, p2, weight));
    }

    /**
     * Returns an iterator to the list of pixels.
     * @return An iterator to the list of pixels.
     */
    public Iterator<Pixel> pixelIterator() {
        return pixelList.iterator();
    }

    /**
     * Pixel data structure containing the pixel coordinates and color.
     */
    public static class Pixel {
        /** The coordinate of the pixel */
        Point coord;
        /** The color of the pixel */
        int pixelColor;
        /**
         * Creates a new Pixel object.
         * @param pt The coordinates of the pixel.
         * @param color The color of the pixel.
         */
        Pixel(Point pt, int color) {
            coord = pt;
            pixelColor = color;
        }
        /**
         * Returns the coordinates of the pixel.
         * @return The coordinates of the pixel.
         */
        public Point getLocation() {
            return coord;
        }
        /**
         * Returns the color of the pixel
         * @return The color of the pixel.
         */
        public int getColor() {
            return pixelColor;
        }
    }
}
