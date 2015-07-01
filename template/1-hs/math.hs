import Data.List

-- problem 31. determine whether a given integer number is prime
isPrime :: Int -> Bool
isPrime n = find ((== 0) . mod n) [2 .. (floor $ sqrt $ fromIntegral n)] == Nothing

-- problem 32. GCD
myGCD :: Int -> Int -> Int
myGCD a b = if b == 0 then a else myGCD b (a `mod` b)

-- problem 33. coprime
coprime :: Int -> Int -> Bool
coprime a b = myGCD a b == 1

-- problem 34. totient-phi
totient :: Int -> Int
totient 1 = 1
totient n = (div q p) * (p - 1) * totient (div n q)
	where
		p = head [x | x <- [2..], mod n x == 0]
		f n p = if mod n p /= 0 then 1 else p * f (div n p) p
		q = f n p

-- problem 35. determine the prime factors of a given positive integer
primeFactors :: Int -> [Int]
primeFactors 1 = []
primeFactors n = p : primeFactors (div n p)
	where p = head [x | x <- [2..], mod n x == 0]

-- problem 36. determine the prime factors of a given positive integer
primeFactorsMult :: Int -> [(Int, Int)]
primeFactorsMult 1 = []
primeFactorsMult n = (p, f n p) : primeFactorsMult (div n (g n p))
	where 
		p = head [x | x <- [2..], mod n x == 0]
		f n p = if mod n p /= 0 then 0 else 1 + f (div n p) p
		g n p = if mod n p /= 0 then 1 else p * g (div n p) p

-- problem 39. a list of prime numbers in a given range
primesR :: Int -> Int -> [Int]
primesR l r = filter isPrime [l .. r]

-- problem 40. Goldbach's conjecture
goldbach :: Int -> (Int, Int)
goldbach n = head [(x, n - x) | x <- [2 .. n-2], isPrime x, isPrime (n-x)]

-- problem 41. Goldbach list
goldbachList :: Int -> Int -> [(Int, Int)]
goldbachList l r = map goldbach [l, l+2 .. r]

-- main routine
main :: IO ()
main = putStrLn . show $ product (take 10 [x | x <- [1..], isPrime x])
