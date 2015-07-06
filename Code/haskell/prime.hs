prime = findp [2..]
	where findp (p:xs)=p:[x|x<-xs,x `mod` p /=0]

main = do
{-	n<-getLine -}
	print $ take 100 prime
{-	print $ prime !! (read n) -}
