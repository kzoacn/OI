prime = findp [2..]
	where findp(p:xs)=p:findp [x|x<-xs , x `mod` p /=0]
main = do
	n<-getLine
	print $ prime !! (read n)
