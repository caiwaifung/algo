import Data.Functor
import Data.List (nub, zip4)
import Data.Bits
import Debug.Trace
import Control.Monad.ST

modNum = 1000000007 :: Integer

modIt :: Integer -> Integer
modIt a = mod a modNum

(//) = div
(%%) = mod
(/|) :: Integer -> Integer -> Bool
a /| b = mod b a == 0

(***) :: Integer -> Integer -> Integer
a *** b = modIt $ a * b

(^^^) :: Integer -> Integer -> Integer
a ^^^ 0 = 1
a ^^^ b = cur *** ((a *** a) ^^^ (div b 2))
    where cur = if b .&. 1 == 1 then a else 1


extGCD :: Integer -> Integer -> (Integer, Integer, Integer)
extGCD a 0 = (a, 1, 0)
extGCD a b = (d, ny, nx - (a // b) * ny)
    where (d, nx, ny) = extGCD b (a %% b)

main :: IO ()
main = getInts >>= putStrLn . show . solve . parsePairs . tail where
    getInts = map read <$> words <$> getContents
    parsePairs [] = []
    parsePairs (x:y:rs) = (x,y) : parsePairs rs

---------------------------------------------------------------------
solve :: [Pair] -> Integer
solve (p:[]) = fst p
solve (p:rs) = case sol of Multi (i, _) (_, _) -> answer i
                           Single (i, _) -> answer i
                           All -> answer 0
                           None -> -1
    where sol = foldl intersect All . map projToX $ map (solve0 p) rs
          answer i = (fst p) *** ((snd p) ^^^ i)

-- (a1,b1), (a2,b2) -> (i,j) s.t. a1*b1^i = a2*b2^j
solve0 :: Pair -> Pair -> Solution
solve0 (a1, b1) (a2, b2) = ans
    where primes = nub . concat . map factorize $ [a1, a2, b1, b2]
          [a1', b1', a2', b2'] = map (toVec primes) [a1, b1, a2, b2]
          f' (x1, y1, x2, y2) = f (x1, x2) (y1, y2)
          ans = foldl intersect All . map f' $ zip4 a1' b1' a2' b2'

factorize :: Integer -> [Integer]
factorize 1 = []
factorize n = let xs = filter (/| n) [2 .. floor . sqrt $ fromIntegral n] in
    if xs == [] then [n] else let x = head xs in x:factorize (n // x)

toVec [] n = []
toVec (p:rs) n = getNum p n : toVec rs n where
    getNum p n = if p /| n then 1 + getNum p (n // p) else 0

---------------------------------------------------------------------
-- (a1,a2), (b1,b2) -> (i,j) s.t. a1+b1*i = a2+b2*j
-- a, b -> t=(i,j) s.t. a+bt is on line x=y
f :: Pair -> Pair -> Solution
f (a1, a2) (0, 0) = if a1 == a2 then All else None

f (a1, a2) (0, b2) = let (x, y) = (a1-a2, b2) in 
    if mod x y /= 0 || div x y < 0 then None else Multi (0, div x y) (1, 0)

f (a1, a2) (b1, 0) = let (x, y) = (a2-a1, b1) in 
    if mod x y /= 0 || div x y < 0 then None else Multi (div x y, 0) (0, 1)

f (a1, a2) (b1, b2) = let (g, i0, j0) = extGCD b1 b2 in
    if g /| (a2-a1) 
        then let d = (a2-a1)//g
                 (i, j, di, dj) = (i0*d, -j0*d, b2//g, b1//g)
             in simplify i j di dj
        else None

---------------------------------------------------------------------
type Pair = (Integer, Integer)

parallel :: Pair -> Pair -> Bool
parallel (x1, y1) (x2, y2) = x1 * y2 == x2 * y1

data Solution = Multi Pair Pair | Single Pair | None | All deriving (Show, Eq)
getMulti (Multi (i,j) (di,dj)) = (i, j, di, dj)

projToX :: Solution -> Solution
projToX s = case s of Multi (i, _) (di, _) -> Multi (i, 0) (di, 0)
                      Single (i, _) -> Single (i, 0)
                      None -> None
                      All -> Multi (0, 0) (1, 0)

simplify i0 j0 di dj = Multi (i0'', j0'') (di, dj)
    where
        t1 = max 0 $ max (div (-i0-1) di) (div (-j0-1) dj) + 1
        i0' = i0 + t1 * di
        j0' = j0 + t1 * dj
        t2 = max 0 $ min (div i0 di) (div j0 dj)
        i0'' = i0' - t2 * di
        j0'' = j0' - t2 * dj

contains :: Pair -> Solution -> Bool
contains _ All = True
contains _ None = False
contains p (Single a) = p == a
contains (x, y) (Multi (i, j) (di, dj)) = 
    (i<=x && j<=y && parallel (di,dj) (dx,dy) && (v/|u) && (u//v)>=0)
    where (dx, dy) = (x-i, y-j)
          (u, v) = (dx+dy, di+dj)

intersect :: Solution -> Solution -> Solution
intersect None _ = None
intersect _ None = None
intersect a All = a
intersect All a = a
intersect (Single p) a = if contains p a then Single p else None
intersect a (Single p) = if contains p a then Single p else None
intersect m1@(Multi s1 d1) m2@(Multi s2 d2) = if parallel d1 d2 then res1 else res2
    where
        res1 = let (dx, dy) = (fst s1 - fst s2, snd s1 - snd s2) in
            if not (parallel (dx,dy) d1) 
                then None 
                else let tmp = if fst d1 > 0 then f (fst s1, fst s2) (fst d1, fst d2)
                                             else f (snd s1, snd s2) (snd d1, snd d2)
                     in if tmp == None 
                          then None 
                          else let (i, _, di, _) = getMulti tmp
                                   s = (fst s1 + fst d1 * i, snd s1 + snd d1 * i)
                                   d = (fst d1 * di, snd d1 * di)
                               in Multi s d
        makeLine x1 y1 x2 y2 = (a, b, -(a*x1+b*y1))
            where a = y2 - y1
                  b = x1 - x2
        res2 = if (t/|x0) && (t/|y0) && contains (x,y) m1 && contains (x,y) m2
                 then Single (x, y)
                 else None
            where (a1, b1, c1) = makeLine (fst s1) (snd s1) (fst s1 + fst d1) (snd s1 + snd d1)
                  (a2, b2, c2) = makeLine (fst s2) (snd s2) (fst s2 + fst d2) (snd s2 + snd d2)
                  t = a1*b2-a2*b1
                  x0 = b1*c2-c1*b2
                  y0 = c1*a2-a1*c2
                  (x, y) = (x0//t, y0//t)

