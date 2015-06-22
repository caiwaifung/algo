import Control.Exception.Base
import Debug.Trace
import Data.Functor
import Data.List
import Data.Char

splitEvenOdd :: [a] -> ([a], [a])
splitEvenOdd = foldr f ([], []) where f v (xs, ys) = (ys, v:xs)

main = getLine >>= putStrLn . show . solve . splitEvenOdd

solve :: (String, String) -> Integer
solve (os, xs0) = go os xs rs (1, 0) where
    xs = map (toInteger . digitToInt) xs0 
    rs = getRs os (tail xs)

getRs :: [Char] -> [Integer] -> [(Integer, Integer)]
getRs [] [] = [(1, 0)]
getRs (o:os) (x:xs) = (if o == '+' then (1, u * x + v) else (u * x, v)) : rs where 
    rs = getRs os xs
    (u, v) = head rs

go :: [Char] -> [Integer] -> [(Integer, Integer)] -> (Integer, Integer) -> Integer
go os xs rs l = max (go1 os xs rs l) (go2 os xs rs l)

go1 
