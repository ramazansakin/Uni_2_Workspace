
package pkg111044069hw06;

/**
 * @author ramazan
 */
public class Main {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        
        /* To show that Inserting and removing an element to a GitPriorityQueue
          using Heap ( Binary Tree )  */
        GITPriorityQeue<Integer> GitIntPri = new GITPriorityQeue<>();
        
        GitIntPri.offer(20);
        GitIntPri.offer(15);
        GitIntPri.offer(12);
        GitIntPri.offer(32);
        GitIntPri.offer(25);
        
        System.out.println(GitIntPri.toString());
        
        Integer a = GitIntPri.remove();
        
        System.out.println("Rempoved value is : "+ a);
        System.out.println("Peekek value is : "+GitIntPri.peek());
        System.out.println(GitIntPri.toString());
        
        a = GitIntPri.remove();
        
        System.out.println("Rempoved value is : "+ a);
        System.out.println("Peekek value is : "+GitIntPri.peek());
        System.out.println(GitIntPri.toString());
        
        a = GitIntPri.remove();
        
        System.out.println("Rempoved value is : "+ a);
        System.out.println("Peekek value is : "+GitIntPri.peek());
        System.out.println(GitIntPri.toString());
        
        a = GitIntPri.remove();
        
        System.out.println("Rempoved value is : "+ a);
        System.out.println(GitIntPri.toString());
        
        System.out.println("#############################################################");
        GITPriorityQeue<String> myQueue = new GITPriorityQeue<>();
        
        myQueue.offer("Ramazan");
        myQueue.offer("Hüseyin");
        myQueue.offer("Abdullah");
        myQueue.offer("Huzefye");
        myQueue.offer("Mustafa");
        myQueue.offer("Ibrahim");
        myQueue.offer("Kazım");
        System.out.println(myQueue.toString());
        System.out.println("Removed element is : "+myQueue.remove());
        System.out.println(myQueue.toString());
        System.out.println("Removed element is : "+myQueue.remove());
        System.out.println(myQueue.toString());
        
        System.out.println("#############################################################");
        GITPriorityQeue<Character> myQueue2 = new GITPriorityQeue<>();
        myQueue2.offer('r');
        myQueue2.offer('a');
        myQueue2.offer('m');
        /* To show that Heap doesn't take same elemet again! */
        boolean status = myQueue2.offer('a');
        if( !status )
            System.out.println("The same element is also in the heap : a" );
        
        /* If the element is different from heap's elements, the element  */
        status = myQueue2.offer('z');
        if( !status )
            System.out.println("The same element is also in the heap! ");
        myQueue2.offer('a');
        myQueue2.offer('n');
        myQueue2.offer('s');
        myQueue2.offer('a');
        myQueue2.offer('k');
        myQueue2.offer('i');
        myQueue2.offer('n');
        
        System.out.println(myQueue2.toString());
        
        System.out.println("#############################################################");
        System.out.println("Comparator for Car, compares cars' accordinfg to their cost");
        
        /* fiyatlaarı biraz tahmini yaptım hocam yanlıslık olabilir */
        Car opel = new Car("Opel", "Astra", 34.400 );
        Car fiat = new Car("Fiat", "Albea", 32.500 );
        Car mercedes = new Car("Mercedes", "E-252", 60.000 );
        Car nissan = new Car("Nissan", "Quashi", 52.000 );
        Car porche = new Car("Porche", "Cayenne", 350.000 );
        Car dogan = new Car("Dogan", "SLX", 8.350);
                
        comparatorr<Car> comp = new comparatorr<>();
        GITPriorityQeue<Car> carQueue = new GITPriorityQeue<>(6, comp);
        
        carQueue.offer(opel);
        carQueue.offer(fiat);
        carQueue.offer(dogan);
        carQueue.offer(mercedes);
        carQueue.offer(porche);
        
        System.out.println(carQueue.toString());
        
    }
}
