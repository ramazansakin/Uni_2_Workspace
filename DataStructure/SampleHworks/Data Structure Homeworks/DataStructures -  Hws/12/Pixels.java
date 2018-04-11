import java.awt.*;
import java.util.*;

/**
 * Pixel store data structure.
 * 
 *
 * @author Orhan Aksoy
 */
public class Pixels  {
    
    /** The reference point for the 2D graph */
    private Point reference = null;
    /** The list of pixels */
    private LinkedList<Pixel> pixelList = new LinkedList<Pixel>();

    /**
     * Creates a new Pixels object and sets the reference point.
     * @param ref The reference point of the graph.
     */
    Pixels(Point ref) {
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
     * Adds a new pixel to the pixel store.
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
//        Color pixelColor;
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
