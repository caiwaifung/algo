import Data.Functor
import Data.List (nub, zip4)
import Data.Bits

type Pair = (Integer, Integer)
modNum = 1000000007 :: Integer
modIt :: Integer -> Integer
modIt a = mod a modNum
modMul :: Integer -> Integer -> Integer
modMul a b = modIt $ a * b
modPow :: Integer -> Integer -> Integer
modPow a b = if b == 0 then 1 else modIt $
    (if b .&. 1 == 1 then a else 1) * modPow (modMul a a) (div b 2)
divides :: Integer -> Integer -> Bool
divides a b = (mod b a) == 0

extGCD :: Integer -> Integer -> (Integer, Integer, Integer)
extGCD a 0 = (a, 1, 0)
extGCD a b = (d, ny, nx - (a `div` b) * ny)
    where (d, nx, ny) = extGCD b (a `mod` b)

main :: IO ()
main = getInts >>= putStrLn . show . solve . parsePairs . tail where
    getInts = map read <$> words <$> getContents
    parsePairs [] = []
    parsePairs (x:y:rs) = (x, y) : parsePairs rs
--main = putStrLn . show $ modPow (123::Integer) (321::Integer)
--main = putStrLn . show $ factorize (modNum::Integer)

---------------------------------------------------------------------
data Solution = Multi Pair Pair | Single Pair | None | All
getSrc (Multi p _) = p
getDir (Multi _ p) = p

projToX :: Solution -> Solution
projToX s = case s of Multi (i, _) (di, _) -> Multi (i, 0) (di, 0)
                      Single (i, _) -> Single (i, 0)
                      None -> None
                      All -> Multi (0, 0) (1, 0)

simplify i0 j0 di dj = Multi (i0'', j0'') (di, dj) -- TODO
    where
        t1 = max 0 $ max (div (-i0-1) di) (div (-j0-1) dj) + 1
        i0' = i0 + t1 * di
        j0' = j0 + t1 * dj
        t2 = max 0 $ min (div i0 di) (div j0 dj)
        i0'' = i0' - t2 * di
        j0'' = j0' - t2 * dj

contains :: Pair -> Solution -> Bool
contains _ _ = False -- TODO

parallel :: Pair -> Pair -> Bool
parallel (x1, y1) (x2, y2) = x1 * y2 == x2 * y1

intersect :: Solution -> Solution -> Solution
intersect None _ = None
intersect _ None = None
intersect a All = a
intersect All a = a
intersect (Single p) a = if contains p a then Single p else None
intersect a (Single p) = if contains p a then Single p else None
intersect (Multi s1 d1) (Multi s2 d2) = if parallel d1 d2 then func1 else func2
    where
        func1 = if not (parallel (dx dy) d1) then None else val
            where (dx, dy) = (fst s1 - fst s2, snd s1 - snd s2)
                  tmp = if fst d1 > 0 then f (fst s1, fst d1) (fst s2, fst d2)
                                      else f (snd s1, snd d1) (snd s2, snd d2)
                  val = case tmp of Multi
        func2 = 

---------------------------------------------------------------------
solve :: [Pair] -> Integer
solve (p:[]) = modIt $ fst p
solve (p:rs) = case sol of Multi (i, _) (_, _) -> answer i
                           Single (i, _) -> answer i
                           All -> answer 0
                           None -> -1
    where sol = foldl intersect All . map projToX $ map (go p) rs
          answer i = modIt $ fst p * modPow (snd p) i

---------------------------------------------------------------------
-- (a1,b1), (a2,b2) -> (i,j) s.t. a1*b1^i = a2*b2^j
go :: Pair -> Pair -> Solution
go (a1, b1) (a2, b2) = foldl intersect All . map f' $ zip4 a1' b1' a2' b2'
    where primes = nub (factorize a1 ++ factorize a2 ++ factorize b1 ++ factorize b2)
          [a1', b1', a2', b2'] = map (toVec primes) [a1, b1, a2, b2]
          f' (x1, y1, x2, y2) = f (x1, y1) (x2, y2)

factorize :: Integer -> [Integer]
factorize 1 = []
factorize n = let xs = filter (`divides` n) [2 .. floor . sqrt $ fromIntegral n] in
    if xs == [] then [n] else let x = head xs in x:factorize (div n x)

toVec [] n = []
toVec (p:rs) n = getNum p n : toVec rs n where
    getNum p n = if p `divides` n then 1 + getNum p (div n p) else 0

---------------------------------------------------------------------
-- (a1,b1), (a2,b2) -> (i,j) s.t. a1+b1*i = a2+b2*j
f :: Pair -> Pair -> Solution
f (a1, 0) (a2, 0) = if a1 == a2 then All else None
f (a1, 0) (a2, b2) = let (x, y) = (a1-a2, b2) in 
    if mod x y /= 0 || div x y < 0 then None else Multi (0, div x y) (1, 0)
f (a1, b1) (a2, 0) = let (x, y) = (a2-a1, b1) in 
    if mod x y /= 0 || div x y < 0 then None else Multi (div x y, 0) (0, 1)
f (a1, b1) (a2, b2) = if (a2 - a1) `mod` g == 0 then val else None
    where 
        (g, i0', j0') = extGCD b1 (-b2)
        d = (a2 - a1) `div` g
        (i0, j0) = (i0' * d, j0' * d)
        (di, dj) = (b2 `div` g, b1 `div` g)
        val = simplify i0 j0 di dj

---------------------------------------------------------------------

