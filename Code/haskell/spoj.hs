f :: (Num a,Eq a) => a->a 
f x 
	| x==0 =1
	| otherwise = x*f(x-1)
main = do
	n<-getLine
	x<-sequence $ replicate (read n) getLine
	mapM_ (print.f.read) x
