data Tree a=Empty | Node a (Tree a) (Tree a) deriving(Show,Read,Eq)

new :: a->Tree a
new x = Node x Empty Empty

ins :: (Ord a) =>a->Tree a->Tree a
ins x Empty = new x
ins x (Node a lef rig)
	| x==a = Node x lef rig
	| x<a = Node a (ins x lef) rig
	| x>a = Node a lef (ins x rig)

find :: (Ord a) => a->Tree a->Bool

find x Empty = False

find x (Node a lef rig)
	| x==a  = True
	| x<a = find x lef
	| x>a = find x rig







