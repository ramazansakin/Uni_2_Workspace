import java.awt.*;
import java.awt.Point;
import java.awt.image.BufferedImage;
import java.util.*;
import javax.swing.*;

/**
 * The image selector class. This class provides the functionality to create
 * a Graph2D object surrounded by a polygon formed by following edges on the
 * image passing through points provided by the user..
 *
 * @author Orhan Aksoy
 */
public class ImageSelector {
    
    /** The polygon formed by the marked vertices */
    public Polygon selectionPoly = new Polygon();

    /** The class calculating the shortest path */
    private DijkstraShortestPath dp = null;

    /** The pixel graph containing the pixel color differences of the image */
    private Graph2D pixelGraph = null;

    /** Stores the image being displayed */
    protected  MyImage image=null;

    /**
     * Sets the image on which the selection will take place.
     *
     * @param img The image to be displayed.
     */
    public void setImage(MyImage img) {
        image = img;
        pixelGraph = img.createPixelGraph();
        dp = new DijkstraShortestPath(pixelGraph);

        // The following two lines are used for debugging purposes only.
        // MyImage weightImage = MyImage.createPixelDiffImage(image.getBufferedImage(), image.pixelGraph);
        // displayImage(weightImage, "Weight image");

    }

    /**
     * Creates the Graph2D object representing the image surrounded by the
     * current polygon using a breadth-first search.
     *
     * This method should be called to finalize the selection.
     *
     * @return The Graph2D object representing the selected image.
     */
    public Graph2D select() {

        if (image == null) {
            System.out.println("Image must be set before calling select.");
            return null;
        }

        System.out.println("Extracting image using " + selectionPoly.getVertexCount() + " vertices.");

        // Create the border image for testing for edges
        MyImage borderImage = MyImage.createBorderImage(image.getBufferedImage(), selectionPoly);
        BufferedImage bImage = borderImage.getBufferedImage();

        // THe border image is displayed for debug purposes only.
        // So, disable it.
        // displayBorderImage(borderImage);

        // Pick a point inside the polygon. This point will be the first point
        // in the 2d graph. THen, a breadth-first algorithm will be run to
        // create the graph2d object starting from this point.
        Point start = getStartPointOfPoly(selectionPoly);
        Point ref = new Point(start);
         Graph2D pixelStore = new Graph2D(ref);

        // The pixel queue to be used during breadh-first algorithm run.
        Queue<Point> pixelQueue = new LinkedList<Point>();

        // THe first pixel in the graph. The pixel locations will be stored
        // in reference to the first point (the 'ref' point).
        Integer source = pixelStore.addPoint(0, 0, getPixel(image.getBufferedImage(), start.x, start.y));

        // Add the first pixel to the queue and the map.
        pixelQueue.offer(start);
 
        // The breadth-first algorithm.
        // For every pixel in the queue, finds the new adjacent pixels that are
        // not on the border of the polygon and adds them to the queue and the
        // corresponding edge to the graph.
        // For every pixel added to the queue, sets the corresponding pixel
        // on the border image to blue (which means that pixel is 'identified').
        // For every pixel that is put into the graph, sets the corresponding
        // pixel on the border image to black (which means that pixel is 'visited').

        BufferedImage bufferedImage = image.getBufferedImage();

        while (pixelQueue.isEmpty() == false ) {

            start = pixelQueue.remove();
            Point pt = new Point(start.x, start.y);
            setPixel(bImage, pt, Color.BLACK);
            
            // Check the left pixel
            if (( start.x > 1 ) && (isWhite(bImage, start.x-1, start.y))) {
                pt = new Point(start.x-1, start.y);
                // Set the pixel state to 'identified' and add it to the queue.
                setPixel(bImage, pt, Color.BLUE);
                pixelQueue.offer(pt);
                // Add the pixel to the store
                pixelStore.addPoint(pt.x - ref.x, pt.y - ref.y, getPixel(bufferedImage, pt.x, pt.y));
            }
            // Check the right pixel
            if (( start.x < image.getWidth()-1 ) && (isWhite(bImage, start.x+1, start.y))) {
                pt = new Point(start.x+1, start.y);
                // Set the pixel state to 'identified' and add it to the queue.
                setPixel(bImage, pt, Color.BLUE);
                pixelQueue.offer(pt);
                // Add the pixel to the store
                pixelStore.addPoint(pt.x - ref.x, pt.y - ref.y, getPixel(bufferedImage, pt.x, pt.y));
            } 
            // Check the pixel on top
            if (( start.y > 1 ) && (isWhite(bImage, start.x, start.y-1))) {
                pt = new Point(start.x, start.y-1);
                // Set the pixel state to 'identified' and add it to the queue.
                setPixel(bImage, pt, Color.BLUE);
                pixelQueue.offer(pt);
                // Add the pixel to the store
                pixelStore.addPoint(pt.x - ref.x, pt.y - ref.y, getPixel(bufferedImage, pt.x, pt.y));
            }
            // Check the pixel on bottom.
            if (( start.y < image.getHeight()-1 ) && (isWhite(bImage, start.x, start.y+1))) {
                pt = new Point(start.x, start.y+1);
                // Set the pixel state to 'identified' and add it to the queue.
                setPixel(bImage, pt, Color.BLUE);
                pixelQueue.offer(pt);
                // Add the pixel to the store
                pixelStore.addPoint(pt.x - ref.x, pt.y - ref.y, getPixel(bufferedImage, pt.x, pt.y));
            }
        }
        return pixelStore;
    }

    /**
     * Sets the color of a pixel.
     * @param image The BufferedImage object representing the image
     * @param pt The location of the pixel to be set.
     * @param color The new color of the pixel.
     */
    private void setPixel(BufferedImage image, Point pt, Color color) {
          image.setRGB(pt.x, pt.y, color.getRGB());

    }
    /**
     * Returns an iterator to the vertices of the enclosing polygon
     * @return The vertex iterator.
     */
    public ListIterator<Point> vertexIterator() {
        return selectionPoly.vertexIterator();
    }

    /** 
     * Resets the enclosing polygon.
     */
    public void resetPolygon() {
        selectionPoly.reset();
    }
    /**
     * Adds a new vertex to the enclosing polygon.
     * @param x The x coordinate of the vertex.
     * @param y The y coordinate of the vertex.
     */
    public void addPolygonVertex(int x, int y) {
        int pixelId = y*image.getWidth() + x;
        System.out.println("Starting Dijkstra");
        Long refTime = System.currentTimeMillis();
         dp.calculate(pixelId);
        System.out.println("Dijkstra calculated in " + (System.currentTimeMillis() - refTime) + " msecs");
       

        if (selectionPoly.getVertexCount() > 0 ) {
            Point lastPoint = selectionPoly.getLastVertex();
            int destPixelId = lastPoint.y*image.getWidth() + lastPoint.x;

            LinkedList<Integer> path = dp.getShortestPath(destPixelId);
            Iterator<Integer> points = path.descendingIterator();
            while (points.hasNext()) {
                Point nextPoint = pixelGraph.getPixel(points.next()).getLocation();
                selectionPoly.addVertex(nextPoint.x, nextPoint.y);
            }
        } else {
            selectionPoly.addVertex(x, y);
        }
        System.out.print("GC Running...");
        System.gc();
        System.out.println("done.");
    }
    /**
     * Check if two RGB colors match.
     * @param c1 The first color
     * @param c2 The second color
     * @return True if two parameters are equal.
     */
    private static boolean compColor(int c1, int c2) {

        return (((c1 & 0x00ff0000) >> 16) == (c2 & 0x00ff0000) >> 16) &&
                (((c1 & 0x0000ff00) >> 8) == (c2 & 0x0000ff00) >> 8) &&
                (((c1 & 0x000000ff)  == (c2 & 0x000000ff)));

    }

    /**
     * Returns the RGB value of a pixel.
     * @param image The BufferedImage object representing the image.
     * @param x THe x coordinate of the pixel
     * @param y The y coordinate of the pixel
     * @return The RGB value of the pixel.
     */
    private int getPixel(BufferedImage image, int x, int y) {
        return image.getRGB(x, y);
    }

    /**
     * Checks if a pixel is white.
     * @param image The BufferedImage object representing the image.
     * @param x THe x coordinate of the pixel
     * @param y The y coordinate of the pixel
     * @return True if the pixel is white.
     */
    private boolean isWhite(BufferedImage image, int x, int y) {
        int color = image.getRGB(x, y);
        getPixel(image, x, y);
        int  red   = (color & 0x00ff0000) >> 16;
            int  green = (color & 0x0000ff00) >> 8;
            int  blue  =  color & 0x000000ff;

            return ((red >= 0xfc) && (green >= 0xfc) && (blue >= 0xfc));
    }
    /**
     * This method picks a point inside the polygon.
     *
     *
     * @return A point inside the polygon.
     */
    public static Point getStartPointOfPoly(Polygon poly) {
       Point ret = new Point(0, 0);

        ListIterator<Point> vertices = poly.vertexIterator();

        // FInd the average value of y and minimum and maximum values of x.

        int minX = -1;
        int maxX = -1;
        while (vertices.hasNext()) {
                Point v = vertices.next();
                if (minX == -1) {
                    minX = v.x;
                    maxX = v.x;
                } else if (v.x < minX) {
                    minX = v.x;
                } else if (v.x > maxX) {
                    maxX = v.x;
                }

                ret.y += v.y;
        }


        ret.y /= poly.getVertexCount();


        // Starting from minimum of x and average of y, increment one by one
        // until maxx and on the way, check if we're in the polygon. The first point
        // inside the polygon and the last point are stored and its average
        // is the resultant x.

        int detmin = -1;
        int detmax = maxX;


        for (int i=minX; i<=maxX; ++i) {
            if (poly.isPointInside(i, ret.y)) {
                if (detmin == -1) {
                    detmin = i;
                }
            } else {
                if (detmin > -1) {
                    detmax = i-1;
                    break;
                }
            }
        }
        if (detmin > -1) {
            ret.x = (int)((detmin + detmax)/2);
            return ret;
        }
        return null;
    }


    /**
     * Displays an image on a frame for debug purposes.
     * @param img THe  image to be displayed.
     */
    private static void displayImage(MyImage img, String title) {
        JFrame f = new JFrame(title);
        f.getContentPane().add(new JLabel(new ImageIcon(img.getBufferedImage())));
        f.pack();
        f.setLocationRelativeTo(null);
        f.setVisible(true);
    }

}
