max' [x] = x
max' (x:xs)
	| x> maxTail = x
	| otherwise =maxTail
	where maxTail = max' xs