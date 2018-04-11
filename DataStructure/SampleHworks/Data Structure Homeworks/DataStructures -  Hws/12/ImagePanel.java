import javax.swing.*;
import java.awt.*;
import java.awt.event.MouseListener;
import java.awt.event.MouseEvent;
import java.awt.event.MouseMotionListener;
import java.awt.image.BufferedImage;
import java.awt.image.WritableRaster;
import java.util.Iterator;
import java.util.ListIterator;
/**
 * The ImagePanel class extends the JPanel and contains the functinality to
 * display and modify the images.
 *
 * @author Orhan Aksoy
 */
public class ImagePanel extends JPanel implements MouseListener, MouseMotionListener {

    /** Stores the selected image created just after the polygon creation */
    private Pixels selectedImage = null;
    /** Stores the pasteImage while the image is being moved using the mouse */
    private Pixels pasteImage = null;
    /** Stores the mouse position while the paste image is being moved */
    private Point mousePosition = new Point(0, 0);

    /** Stores the image being displayed */
    protected  BufferedImage ci=null;
    /** The polygon formed by the marked vertices */
    public Polygon selectionPoly = new Polygon();

    /** Set if we're in polygon-draw mode. */
    private boolean isDrawingPolygon = false;

    /** Creates an ImagePanel object using the image buffer */
    public ImagePanel(BufferedImage si) {
      this.ci=si;
      setPreferredSize(new Dimension(si.getWidth(null),si.getHeight(null)));
      addMouseListener(this);
      addMouseMotionListener(this);
    }

    /**
     * Called when the polygon is complete.
     */
    void processPolygonSelection() {

        /** Create the Pixels object by using the ImageSelector.select
         * method and store it.
         */
        selectedImage = ImageSelector.select(ci, selectionPoly);

    }

    /**
     * Returns the current BufferedImage object
     * @return The current BUfferedImage object.
     */
    public Image getDisplayedImage() {
        return this.ci;
    }

    /**
     * Returns the selected(copied) Pixels object.
     * @return The selected(copied) Pixels object.
     */
    public Pixels getSelectedImage() {
        return selectedImage;
    }

    /**
     * Sets the paste image. After this method is called, the paste image is
     * bound to the mouse and moves with it until a mouse click event.
     *
     * @param image The image to be pasted.
     */
    public void setPasteImage(Pixels image) {
        pasteImage = image;
    }

    /**
     * Updates the current view throught the provided Graphics object.
     * @param g THe graphics object.
     */
    @Override
    public void update(Graphics g) {

        BufferedImage targetImage = null;
        if (ci != null) {
            WritableRaster raster = ci.copyData( null );
            targetImage = new BufferedImage( ci.getColorModel(), raster, ci.isAlphaPremultiplied(), null );
            /* Draw the selected polygon if exists */

            Graphics g2 = targetImage.createGraphics();

            ListIterator<Point> vertices = selectionPoly.vertexIterator();

            int radius = 1;
            Point prevVertex = null;
            Point v = null;
            Point firstVertex = null;
            while (vertices.hasNext()) {
                v = vertices.next();
                if (firstVertex == null) {
                    firstVertex = v;
                }
                g2.drawOval(v.x - radius, v.y - radius, 2 * radius, 2 * radius);
                g2.setColor(Color.BLACK);
                g2.fillOval(v.x - radius, v.y - radius, 2 * radius, 2 * radius);

                if (prevVertex != null) {
                    g2.drawLine(prevVertex.x, prevVertex.y, v.x, v.y);
                }
                prevVertex = v;
            }
            if (!isDrawingPolygon && (v != null)) {
                g2.drawLine(v.x, v.y, firstVertex.x, firstVertex.y);
            }

            /* Draw the paste image if exists */

            if (pasteImage != null) {
                drawGraph2D(targetImage, mousePosition, pasteImage);

            }
            g.drawImage(targetImage, 0,0,targetImage.getWidth(null),targetImage.getHeight(null), this);
        }else {
            super.update(g);
        }
     }

    /**
     * THe paint event handler.
     * @param g The Graphics object
     */
    @Override
    public void paint(Graphics g) {
        update(g);
    }
    /**
     * The mouse click event handler.
     * @param e THe mouse event object.
     */
    public void mouseClicked(MouseEvent e) {
        if ( e.getClickCount() == 1 ) {

            // This is a single click. If an image is being pasted, merge the
            // current image and the paste image.
            // IF no image is being pasted, add a new vertes to the current
            // polygon.

            if (pasteImage != null) {
                drawGraph2D(ci, new Point(e.getX(), e.getY()), pasteImage);
                pasteImage = null;
                selectionPoly.reset();
            } else {

                // Single click case, so add a vertex
                if (!isDrawingPolygon) {
                    isDrawingPolygon = true;
                    selectionPoly.reset();
                }
                selectionPoly.addVertex(e.getX(), e.getY());
            }
        } else {
            // Double click, so finalize the polygon.
            processPolygonSelection();
            isDrawingPolygon = false;
        }
        repaint();
    }

    /**
     * Draw the provided Pixels object to a specific location using the
     * Graphics object g. After this call, the current image is merged with
     * the image represented by the Pixels object.
     * @param img The BufferedImage object onto which the Pixels image will be put.
     * @param start The starting location of the Pixels image.
     * @param imageGraph The Pixels object to be put.
     */
    private void drawGraph2D(BufferedImage img, Point start, Pixels imageGraph) {
        Iterator<Pixels.Pixel> it = imageGraph.pixelIterator();
        while (it.hasNext()) {
            Pixels.Pixel pix = it.next();
            int x = pix.getLocation().x + start.x;
            int y = pix.getLocation().y + start.y;
            if ((x < ci.getWidth(null)) && (y < ci.getHeight(null)) && (x >= 0) && (y >= 0)) {

                int rgb = pix.getColor();
                img.setRGB(x, y, rgb);

            }
        }
    }

    /**
     * Fills the selection area with the specified color.
     * @param rgb The rgb to be filled.
     */
    public void fillSelectedImage(int rgb) {
        if (selectedImage != null) {
            Iterator<Pixels.Pixel> it = selectedImage.pixelIterator();
            while (it.hasNext()) {
                Pixels.Pixel pix = it.next();
                int x = pix.getLocation().x + selectedImage.getReference().x;
                int y = pix.getLocation().y + selectedImage.getReference().y;
                ci.setRGB(x, y, rgb);
            }
            repaint();
        }
    }

  public void mousePressed(MouseEvent e) {}
  public void mouseReleased(MouseEvent e) {}
  public void mouseEntered(MouseEvent e) {}
  public void mouseExited(MouseEvent e) {}
  public void mouseDragged(MouseEvent e) {};

  /**
   * Called when the mouse is moved on the panel. This method sets the current
   * mouse position and initiates a repaint event for the panel.
   *
   * @param e THe mouse event object.
   */
  public void mouseMoved(MouseEvent e) {

      if (pasteImage == null) {
          return;
      }
      mousePosition.x = e.getX();
      mousePosition.y = e.getY();
      repaint();
  }
}
