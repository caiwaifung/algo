import Debug.Trace
import Data.Functor
import Data.List

discretize :: (Ord a, Bounded a, Show a) => [a] -> [Int]
discretize xs = map (negate . snd) . sort $ zip is es where
    (ys, is) = unzip . sort $ zip xs [0..]
    (zs, es) = unzip $ scanl1 max (zip ys [0,-1..])

suffixArrayRank :: String -> [Int]
suffixArrayRank str = foldl step (map fromEnum str :: [Int]) itrs where
    itrs = 0 : takeWhile (< length str) [2^i | i <- [0..]]
    step s len = discretize $ zip s (drop len s ++ [-1,-1..])

suffixArray = snd . unzip . sort . (flip zip) [0..] . suffixArrayRank

getInts :: IO [Int]
getInts = map read <$> words <$> getContents

main = putStrLn . show $ sum $ suffixArray (take 100000 ['a'..]) 
