/**
 * TestStudent class is a test class to be used in storing within the multiple
 * heap data structure. It has three attributes according to which the heap
 * will sort instances of it.
 * 
 * @author Orhan Aksoy = 09104302
 */
import java.util.*;

public class TestStudent {
    private String name;
    private int number;
    private int note;

    /**
     * Creates a new TestStudent object
     * @param name Name of teh student
     * @param number Number of the student
     * @param note GPA of the student
     */
    public TestStudent(String name, int number, int note) {
        this.name = name;
        this.note = note;
        this.number = number;
    }
    /**
     * Creates a string representation of this object.
     * @return
     */
    public String toString() {
       return ("(" + name + ", " + number + ", " + note + ")");
    }

    /**
     * Used to compare students according to their names
     */
    public static class CompareStudentName implements Comparator<TestStudent> {
        public int compare(TestStudent val1, TestStudent val2) {
            return val1.name.compareTo(val2.name);
        }
    }
    /**
     * Used to compare students according to their numbers
     */
    public static class CompareStudentNumber implements Comparator<TestStudent> {
        public int compare(TestStudent val1, TestStudent val2) {
            return val1.number == val2.number ? 0 : (val1.number < val2.number ? -1 : 1);
        }
    }
    /**
     * Used to compare students according to their notes
     */
    public static class CompareStudentNote implements Comparator<TestStudent> {
        public int compare(TestStudent val1, TestStudent val2) {
            return val1.note == val2.note ? 0 : (val1.note < val2.note ? -1 : 1);
        }
    }

}
