import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.Dimension;
import javax.swing.*;
import java.io.*;
/**
 * Represents the outer frame of the application. Contains the title menu and
 * handles menu selection events. Also, contains the ImagePanel object which
 * contains the actual image.
 */
public class ImageFrame extends JFrame implements ActionListener {

    /** The MyImage object referencing the image */
    private MyImage image = null;

    /** The menu bar */
    private JMenuBar menuBar = new JMenuBar();


    /** THe copied image pixel store */
    private Graph2D selectedImage = null;

    ImagePanel panel = null;
    /**
     * Constructs an ImageFrame object.
     */
    public ImageFrame() {
        super("HW 13 - Image Frame");
        setMinimumSize(new Dimension(250, 100));
        setResizable(false);
        createMenuBar();
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLocationRelativeTo(null);
    }

    /**
     * Sets the current image. Before setting the new image, removes the ImagePanel
     * object and makes initialization.
     *
     * @param image THe new image.
     */
    public void setImage(MyImage image)  {
        if (panel != null) {
            remove(panel);
        }
        this.image = image;
        panel = new ImagePanel(image);

        add(panel);
        pack();

    }

    /**
     * Creates the menu bar and attaches event handlers.
     */
    private void createMenuBar() {

        // Add the menubar to the frame
        setJMenuBar(menuBar);

        // Define and add two drop down menu to the menubar
        JMenu fileMenu = new JMenu("File");
        JMenu editMenu = new JMenu("Edit");
        menuBar.add(fileMenu);
        menuBar.add(editMenu)    ;

        JMenuItem openAction = new JMenuItem("Open");
        JMenuItem saveAction = new JMenuItem("Save");
        JMenuItem exitAction = new JMenuItem("Exit");


        fileMenu.add(openAction);
        fileMenu.add(saveAction);
        fileMenu.add(exitAction);

       JMenuItem copyAction = new JMenuItem("Copy");
       JMenuItem fillAction = new JMenuItem("Fill");
       JMenuItem pasteAction = new JMenuItem("Paste");

        editMenu.add(copyAction);
        editMenu.add(fillAction);
        editMenu.add(pasteAction);

        openAction.addActionListener(this);
        saveAction.addActionListener(this);
        exitAction.addActionListener(this);
        copyAction.addActionListener(this);
        fillAction.addActionListener(this);
        pasteAction.addActionListener(this);


    }
    /**
     * Called when a menu item is selected.
     * @param arg0 The action object associated with the menu event.
     */
    public void actionPerformed(ActionEvent arg0) {
        String cmd = arg0.getActionCommand();
        if (cmd.compareToIgnoreCase("open") == 0) {

            // The action is 'File open'.
            // Open the JFileChooser dialog to get the name of the file to be
            // opened.

            JFileChooser fc = new JFileChooser();
            int returnVal = fc.showOpenDialog(this);

            if (returnVal == JFileChooser.APPROVE_OPTION) {
                File file = null;
                try {
                    // Read the file and create the MyImage object. Then, set
                    // the current image.

                    file = fc.getSelectedFile();
                    MyImage newImage = new MyImage(file.getAbsolutePath());
                    if (newImage.isLoaded()) {
                        setImage(newImage);
                    }

                } catch(IOException e) {
                    System.out.println("Error loading file " + file.getName());
                }
            }
        } else if (cmd.compareToIgnoreCase("save") == 0) {
            // The action is 'File save'.
            // Open the JFileChooser dialog to get the name of the file to be
            // saved.
            JFileChooser fc = new JFileChooser();
            fc.setDialogType(JFileChooser.SAVE_DIALOG);
            fc.setApproveButtonText("Save");
            fc.setDialogTitle("Save");
            int returnVal = fc.showOpenDialog(this);
            if (returnVal == JFileChooser.APPROVE_OPTION) {
                File file = null;
                try{
                    file = fc.getSelectedFile();
                    image.save(file.getAbsolutePath(), file.getName());

                } catch(IOException e) {
                    System.out.println("Error saving file " + file.getName());
                }
            }
        } else if (cmd.compareToIgnoreCase("copy") == 0) {
            // The action is 'Copy'.
            // Store the selected image .

            selectedImage = panel.getSelectedImage();
        } else if (cmd.compareToIgnoreCase("paste") == 0) {
            // The action is 'Paste'.
            // Paste the selected image .
            if (selectedImage != null) {
                panel.setPasteImage(selectedImage);
            }
        } else if (cmd.compareToIgnoreCase("fill") == 0) {
            if (panel == null) {
                return;
            }
            // The action is 'Fill'.
            // Fill the selected region .
            final JColorChooser chooser = new JColorChooser();
            JDialog dialog = JColorChooser.createDialog(this,
                "Fill Color", true, chooser, null, null);
            dialog.setVisible(true);

           panel.fillSelectedImage(chooser.getColor().getRGB());
        } else if (cmd.compareToIgnoreCase("exit") == 0) {
            dispose();
        }
    }
}
