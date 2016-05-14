package rbtree;

public class RBTree<Key extends Comparable<Key>, Value>
{
	private static final boolean BLACK = true;
	private static final boolean RED = false;
	private Node root;
	private int size;

	public class Node
	{
		private Key key;
		private Value val;
		private Node left, right;
		private boolean color;

		private Node(Key key, Value val, boolean color)
		{
			this.key = key;
			this.val = val;
			this.color = color;
			this.left = null;
			this.right = null;
		}

		public Key key() { return key; }
		public Value val() { return val; }
		public Node left() { return left; }
		public Node right() { return right; }
		public boolean isRed() { return color == RED; }
	}

	public RBTree() { root = null; size = 0; }
	public boolean isRed(Node h) { return h != null && h.color == RED; }
	public int size() { return size; }
	public Node root() { return root; }

	// if $key in this tree, update that node with $val, reture false
	// else, insert a new node {$key, $val}, return true
	public boolean insert(Key key, Value val)
	{
		int oldSize = size;
		root = insert(root, key, val);
		return size > oldSize;
	}

	// if $key in this tree, delete that node
	// else, raise null pointer exception.
	public void delete(Key key)
	{
		root = delete(root, key);
	}

	// if $key in this tree, return that node
	// else, return null
	public Node find(Key key)
	{
		Node x = root;
		while (x != null) {
			int cmp = key.compareTo(x.key);
			if (cmp == 0) {
				break;
			} else if (cmp < 0) {
				x = x.left;
			} else {
				x = x.right;
			}
		}
		return x;
	}

	private Node insert(Node h, Key key, Value val)
	{
		if (h == null) {
			size++;
			return new Node(key, val, RED);
		}

		int cmp = key.compareTo(h.key);
		if (cmp == 0) {
			h.val = val;
			return h;
		} else {
			if (cmp < 0) {
				h.left = insert(h.left, key, val);
			} else {
				h.right = insert(h.right, key, val);
			}
			return fixUp(h);
		}
	}

	// require: h != null
	private Node fixUp(Node h)
	{
		if (isRed(h.left) && isRed(h.right)) {
			colorFlip(h);
		} else if (isRed(h.right)) {
			h = rotateLeft(h);
		} else if (isRed(h.left) && isRed(h.left.left)) {
			h = rotateRight(h);
			colorFlip(h);
		}
		return h;
	}

	// require: h != null && isRed(h.right)
	private Node rotateLeft(Node h)
	{
		Node x = h.right;
		h.right = x.left;
		x.left = h;
		x.color = h.color;
		h.color = RED;
		return x;
	}

	// require: h != null && isRed(h.left)
	private Node rotateRight(Node h)
	{
		Node x = h.left;
		h.left = x.right;
		x.right = h;
		x.color = h.color;
		h.color = RED;
		return x;
	}

	// require: h != null
	private void colorFlip(Node h)
	{
		h.color = ! h.color;
		h.left.color = ! h.left.color;
		h.right.color = ! h.right.color;
	}

	private Node delete(Node h, Key key)
	{
		if (key.compareTo(h.key) < 0) {
			if (!isRed(h.left) && !isRed(h.left.left)) {
				h = moveRedLeft(h);
			}
			h.left = delete(h.left, key);
		} else {
			if (isRed(h.left)) {
				h = rotateRight(h);
			}
			if (key.compareTo(h.key) == 0 && h.right == null) {
				size--;
				return null;
			}
			if (!isRed(h.right) && !isRed(h.right.left)) {
				h = moveRedRight(h);
			}
			if (key.compareTo(h.key) == 0) {
				Node x = getMin(h.right);
				h.key = x.key;
				h.val = x.val;
				h.right = deleteMin(h.right);
			} else {
				h.right = delete(h.right, key);
			}
		}
		return fixUp(h);
	}

	// require: isRed(h) && h.left != null &&
	//          !isRed(h.left) && !isRed(h.left.left)
	private Node moveRedLeft(Node h)
	{
		colorFlip(h);
		if (isRed(h.right.left)) {
			h.right = rotateRight(h.right);
			h = rotateLeft(h);
			colorFlip(h);
		}
		return h;
	}

	// require: isRed(h) && h.right != null &&
	//          !isRed(h.right) && !isRed(h.right.left)
	private Node moveRedRight(Node h)
	{
		colorFlip(h);
		if (isRed(h.left.left)) {
			h = rotateRight(h);
			colorFlip(h);
		}
		return h;
	}

	// require: h != null
	private Node getMin(Node h)
	{
		while (h.left != null) {
			h = h.left;
		}
		return h;
	}

	private Node deleteMin(Node h)
	{
		if (h.left == null) {
			size--;
			return null;
		}
		if (!isRed(h.left) && !isRed(h.left.left)) {
			h = moveRedLeft(h);
		}
		h.left = deleteMin(h.left);
		return fixUp(h);
	}

	public boolean testLLRB()
	{
		if (root != null) { root.color = BLACK; }
		return blackLinks(root) != -1;
	}

	// if node $h is a valid left-lean-red-black tree, return the number of
	// black links of a path from $h to any of its leaf-node(nil-node).
	// else return -1.
	private int blackLinks(Node h)
	{
		if (h == null) {
			return 0;
		}
		if (isRed(h.right)) {
			return -1;
		}
		if (h.color == RED && isRed(h.left)) {
			return -1;
		}
		int black_links = blackLinks(h.left);
		if (black_links == -1 ||
			black_links != blackLinks(h.right)) {
			return -1;
		}
		if (h.color == BLACK) {
			black_links++;
		}
		return black_links;
	}
}