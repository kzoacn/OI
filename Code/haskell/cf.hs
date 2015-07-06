main = do
	x<-getLine
	print $ f (map read $words x) !! 0 $ (map read $words x) !! 1

f x y = x+y
