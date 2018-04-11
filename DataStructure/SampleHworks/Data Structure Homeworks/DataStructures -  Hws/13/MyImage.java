import java.awt.Color;
import java.awt.Graphics2D;
import java.awt.Point;
import java.awt.color.ColorSpace;
import java.awt.image.*;
import java.io.*;
import java.util.Iterator;
import java.util.ListIterator;
import javax.imageio.*;

/**
 * Custom Image class that provides reading/writing gray-scale images.
 *
 * @author Orhan Aksoy
 */
public class MyImage {
    /** The BufferedImage object representing the bitmap */
    private BufferedImage image;

    /** The pixel graph */
    Graph2D pixelGraph = null;

    // The color difference weight factors used in creating the pixel graph

    /** The minimum weight of the edges in the created graph */
    private final double MINIMUM_WEIGHT = 1;
    /** The maximum weight of the edges in the created graph */
    private final double MAXIMUM_WEIGHT = 1000;
    /** Maximum difference of colors in the image */
    private final double MAXIMUM_DIFF = 1000;
    /** The exponential constant in the weight calculation expression
     *
     *                         -k*Color_Diff(i, j)
     * w(i, j) = Max_Weight * e
     *
     */
    private final double WEIGHT_CONSTANT = Math.log(MINIMUM_WEIGHT/MAXIMUM_WEIGHT)/(-MAXIMUM_DIFF);

    /**
     * Create a new MyImage object with the specified size.
     * Set all the pixels to white.
     *
     * @param width The width of the image
     * @param height The height of the image
     */
    public MyImage(int width, int height) {
        image = new BufferedImage(width, height, BufferedImage.TYPE_BYTE_INDEXED);
        byte[] data = ((DataBufferByte)image.getRaster().getDataBuffer()).getData();
        for (int i = 0; i< data.length; ++i) {
            data[i] = (byte)0xff;
        }

    }
    /**
     * Creates the pixel graph from the image.
     */
    public Graph2D createPixelGraph() {

        System.out.println("Creating pixel graph");
        pixelGraph = new Graph2D();

        int width = image.getWidth();
        int height = image.getHeight();

        for (int y= 0; y < height; ++y ) {
            for (int x = 0; x < width; ++x) {
                pixelGraph.addPoint(x, y, image.getRGB(x, y));
            }
        }



        for (int y= 0; y < height; ++y ) {
            for (int x = 0; x < width; ++x) {

                int id = y*width + x;
                int curColor = image.getRGB(x, y);

                if (x + 1 < width) {
                    int colorDiff = colorDiff(image.getRGB(x+1, y), curColor);
                    pixelGraph.addEdge(new Graph2D.Edge(id, id+1, (int)(MAXIMUM_WEIGHT*Math.exp(-WEIGHT_CONSTANT*colorDiff))));
                    pixelGraph.addEdge(new Graph2D.Edge(id+1, id, (int)(MAXIMUM_WEIGHT*Math.exp(-WEIGHT_CONSTANT*colorDiff))));
                }

                if (y + 1 < height) {
                    int colorDiff = colorDiff(image.getRGB(x, y+1), curColor);
                    pixelGraph.addEdge(new Graph2D.Edge(id, id + width, (int)(MAXIMUM_WEIGHT*Math.exp(-WEIGHT_CONSTANT*colorDiff))));
                    pixelGraph.addEdge(new Graph2D.Edge(id+width, id, (int)(MAXIMUM_WEIGHT*Math.exp(-WEIGHT_CONSTANT*colorDiff))));
                }
                if ((x + 1 < width) &&  (y + 1 < height)){
                    int colorDiff = colorDiff(image.getRGB(x+1, y+1), curColor);
                    pixelGraph.addEdge(new Graph2D.Edge(id+1, id+width, (int)(MAXIMUM_WEIGHT*Math.exp(-WEIGHT_CONSTANT*colorDiff))));
                    pixelGraph.addEdge(new Graph2D.Edge(id+width, id+1, (int)(MAXIMUM_WEIGHT*Math.exp(-WEIGHT_CONSTANT*colorDiff))));
                }
                if ((x - 1 > 0) &&  (y + 1 < height)){
                    int colorDiff = colorDiff(image.getRGB(x-1, y+1), curColor);
                    pixelGraph.addEdge(new Graph2D.Edge(id, id+width-1, (int)(MAXIMUM_WEIGHT*Math.exp(-WEIGHT_CONSTANT*colorDiff))));
                    pixelGraph.addEdge(new Graph2D.Edge(id+width-1, id, (int)(MAXIMUM_WEIGHT*Math.exp(-WEIGHT_CONSTANT*colorDiff))));
                }


            }
        }
        System.out.println("Pixel graph created");
        return pixelGraph;
    }

    /**
     * REturns a measure of color difference between two rgba values.
     * Diff = |red1-red2| + |green1-green2| + |blue1-blue2|
     *
     * @param rgba1 The first color to be compared
     * @param rgba2 The second color to be compared
     * @return The color difference value.
     */
    private static int colorDiff(int rgba1, int rgba2) {
            int  red   = ((rgba1 & 0x00ff0000) >> 16) - ((rgba2 & 0x00ff0000) >> 16);
            int  green = ((rgba1 & 0x0000ff00) >> 8) - ((rgba2 & 0x0000ff00) >> 8);
            int  blue  =  (rgba1 & 0x000000ff) - (rgba2 & 0x000000ff);

            return Math.abs(red) + Math.abs(green) + Math.abs(blue);
    }

    /**
     * Returns true if an image has been loaded.
     * @return True if an image has been loaded.
     */
    public boolean isLoaded() {
        return (image != null);

    }
    /**
     * Constructs the MyImage object from the file specified
     * @param fileName The image file to be loaded.
     * @throws IOException Thrown if the file load operation fails.
     */
    public MyImage(String fileName) throws IOException {
        loadImageFromFile(fileName);
    }
    /**
     * Constructs the MyImage object from the file
     * @param fileName The image file .
     * @throws IOException Thrown if the file load operation fails.
     */
    public MyImage(File imgFile) throws IOException  {
        image = ImageIO.read(imgFile);
    }

    /**
     * Returns the BufferedImage object storing the image.
     * @return The BufferedImage object storing the image.
     */
    public BufferedImage getBufferedImage() {
        return image;
    }

    /**
     * Returns the image width.
     * @return THe image width.
     */
    public int getWidth() {
        return image.getWidth();
    }
    /**
     * Returns the image height.
     * @return THe image height.
     */
    public int getHeight() {
        return image.getHeight();
    }

    /**
     * Loads an image file and converts it into grey scale format..
     * @param fileName The image file to be loaded.
     * @throws IOException Thrown if the file load operation fails.
     */
    private void loadImageFromFile(String fileName) throws IOException {
        File imgFile = new File(fileName);
        
        image = ImageIO.read(imgFile);
    }

    /**
     * Saves the current image.
     * @param path The name of the file _with_ its path
     * @param name The name of the file
     * @throws IOException Thrown if the file cannot be saved.
     */
    public void save(String path, String name) throws IOException {

        File saveFile = null;
        String formatName = null;

        int idx = name.lastIndexOf(".");

        if (idx == -1) {
            saveFile = new File(path + ".bmp");
            formatName = new String("BMP");
        } else {
            formatName = path.substring(idx+1).toUpperCase();
            saveFile = new File(path);
        }
        ImageIO.write(image, "BMP", saveFile);
    }

    /** 
     * On an offline image, draw pixel diff image. This image is used for
     * debugging
     */

    /**
     * On an offline image, draw pixel diff image. This image is used for
     * debugging purposes only.
     *
     * @param image The image from which the pixel diff will be created
     * @param graph The source of the pixel diff (Graph2D)
     * @return The pixel diff image.
     */
    public static MyImage createPixelDiffImage(BufferedImage image, Graph2D graph) {
        System.out.println("Creating pixel diff image");
        MyImage diffImage = new MyImage(image.getWidth(), image.getHeight());

        Iterator<Graph2D.Pixel> pixels = graph.pixelIterator();
        Graphics2D g = diffImage.getBufferedImage().createGraphics();

        int pixelCount = 0;
        System.out.println("Image size: " + diffImage.getWidth() + " x " + diffImage.getHeight());
        System.out.println("Total pixel count: " + graph.pixelCount());

        BufferedImage img = diffImage.getBufferedImage();

        for (int i=0; i<graph.pixelCount(); ++i) {
            Iterator<Graph2D.Edge> edgeIt = graph.edgeIterator(i);
            if (edgeIt == null) {
                continue;
            }
            while (edgeIt.hasNext()) {
                Graph2D.Edge edge = edgeIt.next();
                Point dLoc = graph.getPixel(edge.getDestination()).getLocation();
                img.setRGB(dLoc.x, dLoc.y, edge.getWeight());
            }
        }

        g.dispose();
        return diffImage;
    }

    /**
     * On an offline image, draw the border polygon. During creating the
     * pixel store, this image will be checked for testing the edges.
     *
     * @param image The image from which the border image will be created
     * @param poly The polygon surrounding the image
     * @return The border image.
     */
    public static MyImage createBorderImage(BufferedImage image, Polygon poly) {
        MyImage borderImage = new MyImage(image.getWidth(), image.getHeight());

        ListIterator<Point> vertices = poly.vertexIterator();

        Graphics2D g = borderImage.getBufferedImage().createGraphics();
        g.setColor(Color.RED);

        Point prev = null;
        Point v = null;
        Point firstVertex = null;
        while (vertices.hasNext()) {

            v = vertices.next();
            if (firstVertex == null) {
                firstVertex = v;
            }
            if (prev != null) {
                g.drawLine(prev.x, prev.y, v.x, v.y);
            }
            prev = v;
        }
        g.drawLine(firstVertex.x, firstVertex.y, v.x, v.y);
        g.dispose();
        return borderImage;
    }
}
