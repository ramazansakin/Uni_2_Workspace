/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */


import java.util.*;
import java.io.*;
/**
 * Huffman coder class.
 * Instantiates the HuffmanTree generic class using Character as the type
 * parameter.
 * @author Orhan Aksoy
 */
public class HuffmanCoder {
    private HuffmanTree<Character> hTree = new HuffmanTree<Character>();

    private final double probs[] = {0.0651738,  // a
                                    0.0124248,  //
                                    0.0217339,  // c
                                    0.0349835,  // d
                                    0.1041442,  // e
                                    0.0197881,  // f
                                    0.015861,  // g
                                    0.0492888,  // h
                                    0.0558094,  // i
                                    0.0009033,  // j
                                    0.0050529,  // k
                                    0.033149,  // l
                                    0.0202124,  // m
                                    0.0564513,  // n
                                    0.0596302,  // o
                                    0.0137645,  // p
                                    0.0008606,  // q
                                    0.0497563,  // r
                                    0.051576,  // s
                                    0.0729357,  // t
                                    0.0225134,  // u
                                    0.0082903,  // v
                                    0.0171272,  // w
                                    0.0013692,  // x
                                    0.0145984,  // y
                                    0.0007836,  // z
                                    0.1918182}; // space #26

    /**
     * Createa a new huffman tree with default (english) frequency distribution
     */
    public HuffmanCoder() {
        hTree = new HuffmanTree<Character>();
        
       hTree.resetFrequencyHeap();
       for (int i=0; i<26; ++i)  {
            hTree.addFrequency((char)(i+'a'), probs[i]);

       }
       hTree.addFrequency(' ', probs[26]);
        // Print the frequency list to the console
        hTree.printProbabilities();
        // Using the frequency list, construct the huffman tree
        hTree.constructTree();
    }
    /**
     * Creates a new Huffman tree of Characters, using the input text file to
     * calculate character frequencies and setup the tree.
     * 
     *
     * @param textFile Used to calculate character frequencies.
     */
    public void createTreeFromFile(String fileName)  {
        try {
            BufferedReader reader = new BufferedReader(new FileReader(fileName));
            Heap<Character> myHeap = new Heap<Character>();

            // REad and store all characters into a heap.
            char [] ch = new char[1];

            while ( reader.read(ch) > -1 ) {
                myHeap.add(ch[0]);
            }
            int charCount = myHeap.getCount();

            // Put the character probabilites into the huffman tree.

            hTree.resetFrequencyHeap();
            

            Character readChar = (Character)myHeap.getFirst();
            System.out.println("Total chars in the heap: " + myHeap.getCount());
            Character newChar = readChar;
            int count = 1;

            // In this loop, the stored characters from the heap are taken out
            // one by one from the root position. This way, we know that the
            // consecutive items are the same, so the frequency calculation ie
            // easier.
            do {

                while ( readChar == (newChar = myHeap.getFirst())) {
                    count++;
                }
                if (readChar == null) {
                 break;
                }
                hTree.addFrequency(readChar, ((double)count)/charCount);
                System.out.println("Added frequency: " + readChar + " -> " + ((double)count)/charCount);
                count = 1;
                readChar = newChar;
            } while (readChar != null);

            // Print the frequency list to the console
            hTree.printProbabilities();
            // Using the frequency list, construct the huffman tree
            hTree.constructTree();

       } catch (IOException e) {
            e.printStackTrace();
        }
    }

    /**
     * Encodes the file using the stored huffman tree.
     * Stores the encryipted file with the name <filename>.huff
     * @param fileName The file to be encoded.
     */
    public void encodeFile(String fileName)  {

        try {
            BufferedReader reader = new BufferedReader(new FileReader(fileName));

            // REad and store all characters
            LinkedList<Byte> outputBuffer = new LinkedList<Byte>();

            // The following two parameters are length and code references
            // to be filled in the HuffmanTree.getCode methods.
            // The the getCode method returns true, the length[0] value will have
            // the number of bits that the character is occupying and the code[0]
            // value will have the code itself.
            int [] length = {0};
            int [] code = {0};

            // The tmpInt variable is used during packing the bits. Every time
            // The getCode method is called, a few bits are appended to this variable
            // WHen all of its bits are filled with code, then this value is
            // written to the output buffer.
            // The bitLen variable exists for the same purpose, and points to
            // the bit position inside tmpInt that the next code will be placed into
            byte tmpInt = 0;
            int bitLen = 0;

            // Total characters will be counted. This is an 'int' variable, and will
            // be the first value inside the coded file.
            int charCount = 0;

            // Reference to be filled by the reader.read method.
            char [] ch = new char[1];

            // Read characters one by one until EOF
            while ( reader.read(ch) > -1 ) {
                    ++charCount;
                    // Initialize the length and code contents
                    length[0] = 0;
                    code[0] = 0;

                    // Get the code  of the character from the huffman tree
                    // And the number of bits that the code occupies.
                    if (hTree.getCode(ch[0], code, length)) {

                        // First, check if the bits can fit into the current
                        // byte. If so, just append the bits inside tmpInt.
                        if ((bitLen + length[0]) < 8) {
                            tmpInt |= (byte)(code[0] << (8-bitLen-length[0]));
                            bitLen += length[0];
                        // Check if we have exactly 8 bits. If so, write it
                        // on the buffer and initialize variables.
                        } else if (bitLen + length[0] == 8) {
                            outputBuffer.add((byte)(tmpInt | (code[0])));
                            bitLen = 0;
                            tmpInt = 0;
                        // If we're going to execute the following block, this
                        // means that we're going to put a byte in the output
                        // buffer and reorganize tmpInt and bitLen
                        } else {

                            // excess value represents the number of bits
                            // that will be left out after writing the current
                            // byte out.
                            int excess = length[0] - (8 - bitLen);

                            // this is the byte that will be written first.
                            tmpInt |= (code[0] >> excess);
                            outputBuffer.add(tmpInt);

                            // Now, check if the left-out bit count is less than
                            // 8. If so, just store it and keep on normal
                            // operation
                            if (excess < 8) {
                                tmpInt = (byte)((code[0] << (8-excess)) & 0xff);
                                bitLen = excess;
                            } else {
                                // THe number of left out bits (excess) is higher
                                // than 8. This means that the first 8 bits will
                                // be written and the left will be stored.
                                // TODO: This implementation supports up to 16
                                // bits of huffman codes. SHould be resolved.
                                tmpInt = (byte)((code[0] >> (excess-8)) & 0xff);
                                outputBuffer.add(tmpInt);
                                tmpInt = (byte)(code[0] << (16 - excess));
                                bitLen = excess - 8;
                            }
                        }
                    }
                
            }
            // There are a few bits left out. They can safely be written at
            // the beginning of the last integer, because the total number of
            // characters will be written at the beginning of the file for the
            // reader to use.

            if (bitLen > 0) {
                outputBuffer.add(tmpInt);
             }

            // Now, create the file
            // Before the actual data, an integer is written at the front representing the
            // number of coded characters in the file.

            DataOutputStream outputStream = new DataOutputStream(new FileOutputStream(fileName + ".huff"));
            outputStream.writeInt(charCount);
            for (Byte b : outputBuffer) {
                outputStream.writeByte(b);
            }
            outputStream.close();
            reader.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }


    /**
     * Decodes the file using the stored huffman tree.
     * Writes the decoded file with the name <filename>.decoded
     *
     * @param fileName The file to be decoded.
     */
    public void decodeFile(String fileName)  {
        try {
            DataInputStream inputStream = new DataInputStream(new FileInputStream(fileName));
            FileOutputStream outStream = new FileOutputStream(fileName + ".decoded");
            int charCount = inputStream.readInt();
            
            Character ch;

            // This loop reads coded characters from the file byte by byte
            // and for each bit in the byte, calls the 'decode' method of the
            // Huffman Tree in the same order of the bits.
            // When a character is decoded, the decode function returns a
            // character instead of 'null', so we recognize it and write it
            // into the file.

            while (charCount > 0) {

                // The first integer in the coded file represents the number
                // of coded characters in the file.
               byte inByte = inputStream.readByte();

                // Get the 8 bits in decreasing order (from left to right)
                // and send it to the huffman decoder using the method
                // 'HuffmanTree.decode'.
                for (int i=7; i>=0; --i) {
                    if ((ch = hTree.decode((inByte & (1<<i))>>i)) != null) {
                        // When the HuffmanTree.decode returns a character
                        // instead of a 'null', write it on the disk.
                        outStream.write(ch);
                        // Chech if the total number of characters is reached.
                        // If so, quit.
                        if (--charCount == 0) {
                            break;
                        }
                    }

                }

            }
            outStream.close();
            inputStream.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
    /**
     * Loads the Huffman.dat file representing
     * the Huffman tree.
     * 
     */
//    public void loadHuffmanTree() {
 //       try {
 //           hTree = HuffmanTree.readFromFile();
 //           System.out.println("Huffman tree loaded successfully from Huffman.dat");
 //       } catch (IOException e) {
 //           System.out.println("Could not load the huffman tree from file");
 //       }
 //   }
}
