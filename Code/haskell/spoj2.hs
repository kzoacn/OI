main = do 
	n<-getLine
	x<-getLine
	print $ sum $ ((map read).words) x
