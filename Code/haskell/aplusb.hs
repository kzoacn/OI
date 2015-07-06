main = do
	a<-getLine
	b<-getLine
	putStrLn $ show $ (read a :: Int)+(read b :: Int)

