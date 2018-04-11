
import java.util.*;

/**
 * Extended AVL Tree class definition.
 *
 * Adds two constructors to the AVLTree class:
 *
 * @author Orhan Aksoy
 */
public class ExtendedAVLTree<E extends Object & Comparable<E>> extends AVLTree<E> {

  public enum TREETYPE{LOGN, COMPLETE, WORSTCASE};

  public ExtendedAVLTree() {
      super();
  }
  /**
   * Constructs an Extended AVL Tree with only one item
   * @param item THe item that will be stored in the root.
   */
  public ExtendedAVLTree(E item) {
      super();
      add(item);
  }

  public ExtendedAVLTree(E [] items, TREETYPE type) {
      LinkedList<E> itemList = new LinkedList<E>();
      for (E item : items) {
          itemList.add(item);
      }

      Collections.sort(itemList);

      switch (type) {
          case LOGN:
              createLogNAvlTree(itemList);
              break;
          case COMPLETE:
              createCompleteAvlTree(itemList);
              break;
          case WORSTCASE:
              createWorstCaseAvlTree(itemList);
              break;
          default:
      };
  }

  /**
   * Creates a nearly-full tree.
   * Adds the sorted items to the AVL Tree in order. Adding the items in
   * increasing order will make the level above the added item always full,
   * so the search time will always be log(N)
   *
   * @param itemList LinkedList of items that are going to be filled into the AVL tree.
   *
   */
  private void createLogNAvlTree(LinkedList<E> itemList) {
      if (itemList.size() == 0) {
          return;
      }

      // THe list is already sorted in the constructor.

      for (E value : itemList) {
          add(value);
      }
  }
 /**
   * Creates a complete tree.
   * First, creates a tree with all of the values set to '0'. Then, traverses
   * the tree in-order and fills the actual values into the tree from the
   * input list.
   *
   * @param itemList LinkedList of items that are going to be filled into the AVL tree.
   *
   */
  private void createCompleteAvlTree(LinkedList<E> itemList) {
      if (itemList.size() == 0) {
          return;
      }

      // Calculate the height of the biggest full tree that can be built
      // using the input items.
      int maxCompleteHeight = (int)((Math.log(itemList.size()+1))/(Math.log(2)));

      // Build the full tree (content is all '0' yet.)
      ExtendedAVLTree<E> fullTree = buildFullAvlTree(maxCompleteHeight);

      // The number of items in the full tree is 2^m-1. Calculate the number
      // of items left for the last row.

      int itemsRemaining = itemList.size() - fullTree.size();

      // If the number of items in the item list is exactly 2^m-1, then fill
      // the full tree and quit.
      if (itemsRemaining == 0) {
          fillTreeInOrder(fullTree, itemList);

      // The items left for the last row will be the items 0, 2, 4, 6, ...
      // of the input list. So, remove them from the original list, so the
      // number of items left in the original list will be exactly 2^m-1.
      // THen, the addition of these removed elements will keep the tree
      // in its complete form.
      } else {
          LinkedList<E> excessItems = new LinkedList<E>();
          // Here, we remove the items #0, #2, #4, #6, etc and store them
          // in the excess list.
          for (int i=0; i<itemsRemaining; ++i) {
              excessItems.add(itemList.remove(i));
          }
          // Now, fill in the actual values from the list. Since the items list
          // is already sorted, filling them into the tree with in-order traversal
          // will make the tree a BST.
          fillTreeInOrder(fullTree, itemList);
          // Add the excess items in the tree. THe tree will still keep its
          // complete form, since the excess items were selected properly
          // to fit into their bottom-left locations after BST additions.
          for (E excessItem : excessItems) {
              fullTree.add(excessItem);
          }
      }
      root = fullTree.root;
  }


  /**
   * Builds a Full Avl Tree with the provided height.
   * THe items will all have the value of '0' initially.
   * @param height The height of the full tree to be created
   * @return The created full tree.
   */

  private static ExtendedAVLTree buildFullAvlTree(int height) {

       if (height == 1) {
          return new ExtendedAVLTree(0);
      }
      ExtendedAVLTree leftTree = buildFullAvlTree(height - 1);
      ExtendedAVLTree rightTree = buildFullAvlTree(height - 1);

      ExtendedAVLTree newTree = new ExtendedAVLTree(0);

      newTree.root.left = leftTree != null ? leftTree.root : null;
      newTree.root.right = rightTree != null ? rightTree.root : null;
      return newTree;
  }

  /**
   * Creates a worst-case AVL tree with the provided list of items.
   *
   * @param items THe items to be stored in the AVL tree.
   */
  private void createWorstCaseAvlTree(LinkedList<E> items) {
      int nodeCount = items.size();

      // THe height of an AVL Tree can be calculated by the following
      // inequality:
      //
      // height <= 1.44 log (N+2) - 0.33
      //                   2
      int height = (int)((1.4404*Math.log(nodeCount+2)/Math.log(2))-0.33);

      // THis calculated height is a maximum limit. SO, in order to find the
      // correct height, a corresponding worst case tree is created and
      // the node count is checked. If it is bigger than our node count,
      // the height is decremented and the same check is made.
      ExtendedAVLTree tree;
      do {
          tree = buildWorstCaseAvlTree(height--);
      } while (nodeCount < tree.size());

      // Now, fill in the actual values from the list. Since the items list
      // is already sorted, filling them into the tree with in-order traversal
      // will make the tree a BST.
      fillTreeInOrder(tree, items);


      // We know that the current height cannot be exceeded with the items
      // left. The items were sorted in increasing order, so the items left
      // all have big values, so they're going to be added to the right side.
      // As a result, the height of the left tree will not be changed.
      while (items.size() > 0) {
          ((AVLTree)tree).add( (E)items.remove(0));
      }

      root = tree.root;

  }
  /**
   * Builds a worst case AVL Tree with the provided height.
   * @param height The height of the tree to be created
   * @return A worst case AVL Tree with the provided height.
   */
  private static ExtendedAVLTree buildWorstCaseAvlTree(int height) {
      
      //Here, the values put in the tree have no
      // significance. THe only reason that the values '0' and '-1' are put
      // into the tree is that we want a root and a left child only. Later,
      // all of the items in the tree wil be replaced by the real values.
      ExtendedAVLTree newTree = new ExtendedAVLTree(0);
      newTree.add(-1);

      // For an explicit build call with height = 1
      if (height == 1) {
          return new ExtendedAVLTree(0);
      // THis is the base case for the recursion. 
      } else if (height == 2) {
         return newTree;
      }
      // TODO: Gereksiz recursion var. Duzeltilecek.
//      return new ExtendedAVLTree(0, buildWorstCaseAvlTree(height - 1), buildWorstCaseAvlTree(height-2));
      ExtendedAVLTree leftTree = buildWorstCaseAvlTree(height - 1);
      ExtendedAVLTree rightTree = buildWorstCaseAvlTree(height - 2);


      newTree.root.left = leftTree != null ? leftTree.root : null;
      newTree.root.right = rightTree != null ? rightTree.root : null;

      return newTree;

  }



  /**
   * This method accepts a binary tree structure, and traverses it in-order.
   * For each node during the traversal, an item from the input list is taken out from the
   * beginning and its value is set to the visited node.
   * This traversal is done after ensuring that the input list is sorted, so that
   * the binary tree is kept as a BST.
   * @param tree The tree that will be filled
   * @param inputs THe list of inputs to be put into the tree.
   */
  private static void fillTreeInOrder(BinaryTree tree, List inputs) {

      Collections.sort(inputs);
      fillTreeInOrder(tree.root, inputs);
  }
  /**
   * This method accepts a binary tree structure, and traverses it in-order.
   * For each node during the traversal, an item from the sorted input list is
   * taken out from the beginning and its value is set to the visited node.
   * @param localRoot The local root
   * @param inputs The input list.
   */
  private static void fillTreeInOrder(Node localRoot, List inputs) {
      if (inputs.size() == 0) {
          return;
      }
      if (localRoot.left != null) {
          fillTreeInOrder(localRoot.left, inputs);
      }
      localRoot.data = inputs.remove(0);
      if (localRoot.right != null) {
          fillTreeInOrder(localRoot.right, inputs);
      }



  }
  public int size() {
      return size(root);
  }

  protected int size(Node localRoot) {
      if (localRoot == null) {
          return 0;
      }
      return 1 + size(localRoot.right) + size(localRoot.left);
  }

  /**
   * Returns the height of the tree
   * @return The height of the tree.
   */
  public int getHeight() {
      return getHeight(root);
  }

  /**
   * Returns the height of the tree from the provided node downwards
   * @param <E> The type of the items in the tree
   * @param node The root from which the height will be calculated
   * @return The height of the tree starting from the provided node.
   */
  private static int getHeight(Node node) {
      if ( node == null) {
          return 0;
      } else {
          return 1 + Math.max(getHeight(node.left), getHeight(node.right));
      }
  }

}
