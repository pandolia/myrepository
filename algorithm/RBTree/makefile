all: rbtree/TreeVisual.class rbtree/RBTree.class
	java rbtree.TreeVisual

jar: rbtree/TreeVisual.class rbtree/RBTree.class MANIFEST.MF
	jar cvfm rbtree.jar MANIFEST.MF rbtree

rbtree/TreeVisual.class: rbtree/TreeVisual.java
	javac rbtree/TreeVisual.java

rbtree/RBTree.class: rbtree/RBTree.java
	javac rbtree/RBTree.java