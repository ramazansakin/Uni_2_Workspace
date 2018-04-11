/**
 * Driver application for Multiple Heap implementation.
 * 
 * @author Orhan Aksoy - 09104302
 */
import java.util.*;
public class Main {

    /**
     * Tests the multiple heap data structure using three different test
     * methods: Test1, Test2 and Test3.
     * 
     * @param args the command line arguments
     */
    public static void main(String[] args) {


        TestStudent[] studentArray = {  new TestStudent("student1", 5, 40),
                                        new TestStudent("student3", 1, 60),
                                        new TestStudent("student2", 3, 65),
                                        new TestStudent("student4", 8, 55)};

        System.out.println("====== MULTIPLE HEAP TESTS =========================\n");
        System.out.println("The input student array is:");
        for (TestStudent s : studentArray) {
            System.out.println(s);
        }


        Test1(studentArray.clone());
        Test2(studentArray.clone());
        Test3(studentArray.clone());
    }
    /**
     * Tests the multiple heap class using the TestStudent objects.
     *
     * In this test, only one criteria will be used in the heap. It will
     * be according to the number of the students.
     *
     * The output should be a list of students ordered according to their
     * student numbers
     *
     */
    private static void Test1(TestStudent[] studentArray) {

        System.out.println("====== Test 1 =====================================\n");
        System.out.println("Students ordered wrt their student numbers:\n");

         // Only one criteria will be used in the heap. It will be according
        // to the name of the student.
        Comparator [] compArray = { new TestStudent.CompareStudentNumber()};

        MultipleHeap myHeap = new MultipleHeap<TestStudent>(compArray);

        for (TestStudent i : studentArray) {
            myHeap.add(i);
        }

        TestStudent t;
        while ( (t = (TestStudent)myHeap.getFirst(0)) != null) {
            System.out.println("getFirst(Criteria 0) returned " + t);
        }

        System.out.println("====== Test 1 ends ================================\n");
    }
    /**
     * Tests the multiple heap class using the TestStudent objects.
     *
     * In this test, two criteria will be used in the heap. It will
     * be according to the name and note of the students.
     *
     * The first item according to these criteria will be same : student 1.
     *
     * After that, this student is removed from the list. In this case, the second
     * student according to the student name and note are different. So, they
     * are listed.
     * 
     */
    private static void Test2(TestStudent[] studentArray) {

        System.out.println("====== Test 2 =====================================\n");
        System.out.println("Students ordered wrt their student names and notes:\n");

         //Two criteria will be used in the heap. They will be according
        // to the name(criteria 0) and the notes (criteria 1) of the students.
        Comparator [] compArray = { new TestStudent.CompareStudentName(),
                                    new TestStudent.CompareStudentNote()};

        MultipleHeap myHeap = new MultipleHeap<TestStudent>(compArray);

        for (TestStudent i : studentArray) {
            myHeap.add(i);
        }

        System.out.println("Observe that the same student is at the top" +
                " with respect to both student name and note\n");

        System.out.println("findFirst(Criteria 0) returned " + myHeap.findFirst(0));
        System.out.println("findFirst(Criteria 1) returned " + myHeap.findFirst(1));

        System.out.println("\nNow, remove the first item\n");

        System.out.println("getFirst(Criteria 0) returned " + myHeap.getFirst(0));

        System.out.println("\nObserve that two different students are listed now" +
                " with respect to the student name and note\n");

        System.out.println("findFirst(Criteria 0) returned " + myHeap.findFirst(0));
        System.out.println("findFirst(Criteria 1) returned " + myHeap.findFirst(1));


        System.out.println("====== Test 2 ends ================================\n");
    }

    /**
     * Tests the multiple heap class using the TestStudent objects.
     *
     * In this test, tree criteria will be used in the heap. It will
     * be according to the name, number and note of the students.
     *
     * Various findFirst/getFirst calls are made and the output is shown.
     *
     */
    private static void Test3(TestStudent[] studentArray) {
        System.out.println("====== Test 3 =====================================\n");
        System.out.println("Students ordered wrt their names (criteria 0),");
        System.out.println("numbers (criteria 1) and notes (criteria 2)\n");

        Comparator [] compArray = { new TestStudent.CompareStudentName(),
                                    new TestStudent.CompareStudentNumber(),
                                    new TestStudent.CompareStudentNote()};

        MultipleHeap myHeap = new MultipleHeap<TestStudent>(compArray);

        for (TestStudent i : studentArray) {
            myHeap.add(i);
        }

        System.out.println("findFirst(Criteria 0) returned " + (TestStudent)myHeap.findFirst(0));
        System.out.println("findFirst(Criteria 1) returned " + (TestStudent)myHeap.findFirst(1));
        System.out.println("findFirst(Criteria 2) returned " + (TestStudent)myHeap.findFirst(2));
        System.out.println("\n");
        System.out.println("getFirst(Criteria 0) returned " + (TestStudent)myHeap.getFirst(0));
        System.out.println("\n");
        System.out.println("findFirst(Criteria 0) returned " + (TestStudent)myHeap.findFirst(0));
        System.out.println("findFirst(Criteria 1) returned " + (TestStudent)myHeap.findFirst(1));
        System.out.println("findFirst(Criteria 2) returned " + (TestStudent)myHeap.findFirst(2));
        System.out.println("\n");
        System.out.println("getFirst(Criteria 0) returned " + (TestStudent)myHeap.getFirst(0));
        System.out.println("getFirst(Criteria 1) returned " + (TestStudent)myHeap.getFirst(1));
        System.out.println("getFirst(Criteria 2) returned " + (TestStudent)myHeap.getFirst(2));

        System.out.println("getFirst(Criteria 0) returned " + (TestStudent)myHeap.getFirst(0));
        System.out.println("====== Test 3 ends ================================\n");

    }
}
