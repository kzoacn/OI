max' ()
max' (x:xs)
	| length xs == 0 = x
	|  otherwise =max x max'(xs)