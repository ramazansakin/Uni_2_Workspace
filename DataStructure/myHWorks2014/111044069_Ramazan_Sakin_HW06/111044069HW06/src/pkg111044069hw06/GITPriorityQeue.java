
package pkg111044069hw06;

import java.util.NoSuchElementException;
import java.util.Stack;

/**
 * @author ramazan
 */
public class GITPriorityQeue<E> extends BinaryTree<Object> implements PriorityQueue<E>{
    
    /** An optional reference to a Comparator object. */
    private comparatorr < Car > comparator;
    static int numberOfNode = 0;
    static final int MAX_ROUTE = 20;
    private Object[] elems = new Object[100];
    
    public GITPriorityQeue() {
        elems = new Object[100];
        numberOfNode = 0;
        root=null;
        comparator = null;
    }
     
    /** Creates a heap-based priority queue with the specified initial
       capacity that orders its elements according to the specified
       comparator.
       @param cap The initial capacity for this priority queue
       @param comp The comparator used to order this priority queue
       @throws IllegalArgumentException if cap is less than 1
    */
    public GITPriorityQeue(int cap, comparatorr< E > comp) {
        elems = new Object[100];
        numberOfNode = 0;
        if (cap < 1)
            throw new IllegalArgumentException();
        root = null;
        comparator = (comparatorr<Car>) comp;
    }
    
    /** Insert an item into the priority queue.
      pre: The BinaryTree theData is in heap order.
      post: The item is in the priority queue and
            theData is in heap order.
      @param item The item to be inserted
    */
    @Override
    public boolean offer(E item) {
        Stack<Node<E>> nodes = new Stack<>();
        
        for(int i=0; i<numberOfNode-1; ++i){
            if( elems[i] != null && compare(item, (E) elems[i])==0 )
                return false;
        }
            
        if( root == null ){
            root =   (Node<Object>)new Node<>(item);
            ++numberOfNode;
            elems[numberOfNode-1]=(E)item;
            return true;
        }else{
            ++numberOfNode;
            int[] route = new int[MAX_ROUTE];
            Node<E> temp = (Node<E>) root;
            int count=0, nodeNumber = numberOfNode;
            elems[numberOfNode-1]=(E)item;
            
            while( nodeNumber > 1 ){
                route[count] = nodeNumber%2;
                ++count;
                nodeNumber/=2;
            }

            //--count;
            while( count > 0 && temp != null ){
                if( route[count-1] == 0 ){
                    nodes.push(temp);
                    if( count > 1 )
                        temp=temp.right;
                }else{
                    nodes.push(temp);
                    if( count > 1 )
                        temp=temp.left;
                }
                --count;
            }
            
            Node<E> tempNode = new Node<>(null);
            if( route[0] == 0 )
                tempNode = (temp.right = new Node<>(item));
            else
                tempNode = (temp.left = new Node<>(item));
            
            if( !nodes.empty() ){
                
                Node<E> node2 = nodes.pop();
                if( compare( tempNode.data, node2.data ) < 0   )
                    swap( tempNode, node2 );
                else
                    return true;

                while( !nodes.empty() ){
                    Node<E> node = nodes.pop();
                    if( compare( node2.data , node.data  ) < 0 )
                        swap( node2, node );
                    else
                        break;
                    node2=node;
                }
            }
            
            return true;
        }
    }

    /* Removes an item from the priority queue and 
      sorts the heap spesific priority */
    @Override
    public E remove() {
        
        if( root == null )
            throw new NoSuchElementException();

        E returnVal = (E)root.data;
        
        int[] route = new int[MAX_ROUTE];
        int count=0, nodeNumber = numberOfNode;
        
        if( nodeNumber == 1 ){
            root = null;
            return returnVal;
        }
        
        while( nodeNumber > 1 ){
            route[count] = nodeNumber%2;
            ++count;
            nodeNumber/=2;
        }
        
        Node<E> temp = (Node<E>) root;
        while( count > 0 && temp != null ){
            if( route[count-1] == 0 ){
                if( count > 1 )
                    temp=temp.right;
            }else{
                if( count > 1 )
                    temp=temp.left;
            }
            --count;
        }
        
        if( route[0] == 0 ){
            swap((Node<E>) root, temp.right );
            temp.right = null;
        }else{
            swap((Node<E>) root, temp.left );
            temp.left = null;
        }
        
        Node<E> tempNod = (Node<E>) root;
            
        while( true ){
            if( tempNod.right == null && tempNod.left == null )
                break;
            
            //System.out.println(compare(tempNod.data, tempNod.right.data));
            if( tempNod.right != null && compare(tempNod.data, tempNod.right.data ) > 0
                && compare( tempNod.right.data, tempNod.left.data ) < 0    ){
                
                swap(tempNod, tempNod.right );
                tempNod = tempNod.right;
            }else if( tempNod.left != null && compare(tempNod.data, tempNod.left.data) > 0
                    &&  compare(tempNod.left.data, tempNod.right.data ) < 0 ){
                swap(tempNod, tempNod.left );
                tempNod = tempNod.left;
            }else
                break;
        }
        --numberOfNode;
        return returnVal;
    }
    
    /* Removes an item from the priority queue and 
      sorts the heap spesific priarity */
    @Override
    public E poll() {
        if( root == null )
            return null;
        E returnVal = (E)root.data;
        
        int[] route = new int[MAX_ROUTE];
        int count=0, nodeNumber = numberOfNode;
        
        if( nodeNumber == 1 ){
            root = null;
            return returnVal;
        }
        
        while( nodeNumber > 1 ){
            route[count] = nodeNumber%2;
            ++count;
            nodeNumber/=2;
        }
        Node<E> temp = (Node<E>) root;
        int count2=count;
        while( count > 0 && temp != null ){
            if( route[count-1] == 0 ){
                if( count > 1 )
                    temp=temp.right;
            }else{
                if( count > 1 )
                    temp=temp.left;
            }
            --count;
        }
        
        if( route[0] == 0 ){
            swap((Node<E>) root, temp.right );
            temp.right = null;
        }else{
            swap((Node<E>) root, temp.left );
            temp.left = null;
        }
        
        Node<E> tempNod = (Node<E>) root;
            
        while( true ){
            if( tempNod.right == null && tempNod.left == null )
                break;
            
            //System.out.println(compare(tempNod.data, tempNod.right.data));
            if( tempNod.right != null && compare(tempNod.data, tempNod.right.data ) > 0
                && compare( tempNod.right.data, tempNod.left.data ) < 0    ){
                swap(tempNod, tempNod.right );
                tempNod = tempNod.right;
            }else if( tempNod.left != null && compare(tempNod.data, tempNod.left.data) > 0
                    &&  compare(tempNod.left.data, tempNod.right.data ) < 0 ){
                swap(tempNod, tempNod.left );
                tempNod = tempNod.left;
            }else
                break;
        }
        --numberOfNode;
        return returnVal;
    }

    /* take the root's data without removing it */
    @Override
    public E peek() {
        if( root != null )
            return (E)root.data;
        else
            return null;
    }
    
    /* take the root's data without removing it */
    @Override
    public E element() {
        if( root != null )
            return (E)root.data;
        else
            throw new NoSuchElementException();
    }
    
    /* swap two Node's datas for order */
    private void swap( Node<E> left, Node<E> right  ){
        E temp;
        if( right != null && left != null ){
            temp = right.data;
            right.data = left.data;
            left.data = temp;
        }
    }
    
    /** Compare two items using either a Comparator objects compare method
       or their natural ordering using method compareTo.
       pre: If comparator is null, left and right implement Comparable<E>.
       @param left One item
       @param right The other item
       @return Negative int if left less than right,
          0 if left equals right,
          positive int if left > right
       @throws ClassCastException if items are not Comparable
   */
    /* compares two cars according to any charasteristic that they have */
    private int compare( E left, E right ){
        
        if (comparator != null) { // If a Comparator was defined.
            return comparator.compare((Car)left, (Car)right);
        }else { // Use left's compareTo method.
            return ( (Comparable < E > ) left).compareTo(right);
        }
    }
    
    
}

