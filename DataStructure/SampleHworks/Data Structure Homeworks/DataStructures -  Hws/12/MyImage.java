import java.awt.image.*;
import java.io.*;
import javax.imageio.*;
import javax.swing.JOptionPane;

/**
 * Custom Image class that provides reading/writing gray-scale images.
 *
 * @author Orhan Aksoy
 */
public class MyImage {
    /** The BufferedImage object representing the bitmap */
    private BufferedImage image;

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
    private boolean loadImageFromFile(String fileName) throws IOException {
        File imgFile = new File(fileName);
        
        BufferedImage img = ImageIO.read(imgFile);
        
       if ( img.getType() != BufferedImage.TYPE_BYTE_GRAY) {
            JOptionPane.showMessageDialog(null, "Image type can only be TYPE_BYTE_GRAY.");

            return false;
       }
       image = img;
       return true;

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

}
