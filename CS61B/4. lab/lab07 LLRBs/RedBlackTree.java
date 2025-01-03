package src;

public class RedBlackTree<T extends Comparable<T>> {

    /* Root of the tree. */
    public RBTreeNode<T> root;

    public static class RBTreeNode<T> {

        public final T item;
        public boolean isBlack;
        public RBTreeNode<T> left;
        public RBTreeNode<T> right;

        /**
         * Creates a RBTreeNode with item ITEM and color depending on ISBLACK
         * value.
         *
         * @param isBlack
         * @param item
         */
        RBTreeNode(boolean isBlack, T item) {
            this(isBlack, item, null, null);
        }

        /**
         * Creates a RBTreeNode with item ITEM, color depending on ISBLACK
         * value, left child LEFT, and right child RIGHT.
         *
         * @param isBlack
         * @param item
         * @param left
         * @param right
         */
        public RBTreeNode(boolean isBlack, T item, RBTreeNode<T> left,
                          RBTreeNode<T> right) {
            this.isBlack = isBlack;
            this.item = item;
            this.left = left;
            this.right = right;
        }
    }

    /**
     * Creates an empty RedBlackTree.
     */
    public RedBlackTree() {
        root = null;
    }

    /**
     * Flips the color of node and its children. Assume that NODE has both left
     * and right children
     *
     * @param node
     */
    void flipColors(RBTreeNode<T> node) {
        //YOUR CODE HERE
        if (node.left != null) node.left.isBlack = !node.left.isBlack;
        if (node.right != null) node.right.isBlack = !node.right.isBlack;

    }


    /**
     * Rotates the given node to the right. Returns the new root node of
     * this subtree. For this implementation, make sure to swap the colors
     * of the new root and the old root!
     *
     * @param node
     * @return
     */
    RBTreeNode<T> rotateRight(RBTreeNode<T> node) {
        //YOUR CODE HERE
        checkInput(node);
        RBTreeNode<T> x = node.left;
        node.left = x.right;
        x.right = node;
        boolean color = node.isBlack;
        node.isBlack = x.isBlack;
        x.isBlack = color;
        //return new root x
        return x;
    }

    /**
     * Rotates the given node to the left. Returns the new root node of
     * this subtree. For this implementation, make sure to swap the colors
     * of the new root and the old root!
     *
     * @param node
     * @return
     */
    RBTreeNode<T> rotateLeft(RBTreeNode<T> node) {
        //YOUR CODE HERE
        checkInput(node);
        RBTreeNode<T> x = node.right;
        node.right = x.left;
        x.left = node;
        boolean color = node.isBlack;
        node.isBlack = x.isBlack;
        x.isBlack = color;
        //return new root x
        return x;
    }

    /**
     * Helper method that returns whether the given node is red. Null nodes (children or leaf
     * nodes) are automatically considered black.
     *
     * @param node
     * @return
     */
    private boolean isRed(RBTreeNode<T> node) {
        return node != null && !node.isBlack;
    }

    /**
     * Inserts the item into the Red Black Tree. Colors the root of the tree black.
     *
     * @param item
     */
    public void insert(T item) {
        root = insert(root, item);
        root.isBlack = true;
    }

    /**
     * Inserts the given node into this Red Black Tree. Comments have been provided to help break
     * down the problem. For each case, consider the scenario needed to perform those operations.
     * Make sure to also review the other methods in this class!
     *
     * @param node
     * @param item
     * @return
     */
    private RBTreeNode<T> insert(RBTreeNode<T> node, T item) {
        if (item == null)
            throw new IllegalArgumentException("item can't be null!");
        //Insert (return) new red leaf node.
        if (node == null)
            return new RBTreeNode<>(false, item);
        //Handle normal binary search tree insertion.
        //standard BST solution
        if (item.compareTo(node.item) > 0)
            node.right = insert(node.right, item);
        else if (item.compareTo(node.item) < 0)
            node.left = insert(node.left, item);
        else
            return node;
        //Rotate left operation
        if (isRed(node.right) && !isRed(node.left))
            node = rotateLeft(node);
        //Rotate right operation
        if (isRed(node.left) && isRed(node.left.left))
            node = rotateRight(node);
        //Color flip
        if (isRed(node.left) && isRed(node.right))
            flipColors(node);

        return node;
    }

    private void checkInput(RBTreeNode<T> node) {
        if (node == null || node.left == null)
            throw new IllegalArgumentException("Node or its children cannot be null for flipColors operation.");
    }


}
