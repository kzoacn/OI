primes :: [Integer]
primes = 2: 3: sieve (tail primes) [5,7..]
 where 
  sieve (p:ps) xs = h ++ sieve ps [x | x <- t, x `rem` p /= 0]  
                                -- or:  filter ((/=0).(`rem`p)) t
                  where (h,~(_:t)) = span (< p*p) xs
main = do
	print $  primes !! (400000)
