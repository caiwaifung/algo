import Debug.Trace
import Data.Functor
import Data.List
import Data.Array.IO

discretize :: (Ord a, Bounded a) => [a] -> [Int]
discretize xs = map (negate . snd) . sort $ zip is es where
    (ys, is) = unzip . sort $ zip xs [0..]
    (zs, es) = unzip . scanl1 max $ zip ys [0,-1..]

suffixArrayRank :: String -> [Int]
suffixArrayRank str = foldl step (map fromEnum str :: [Int]) itrs where
    itrs = (0:) . takeWhile (< length str) $ iterate (*2) 1
    step s len = discretize . zip s $ drop len s ++ repeat (-1)

suffixArray :: String -> ([Int], [Int])
suffixArray str = (sa, rank) where
    rank = suffixArrayRank str
    sa = map snd . sort . (flip zip) [0..] $ rank

-----------------------------------------------------------------

getInts :: IO [Int]
getInts = map read <$> words <$> getContents

main = putStrLn . show $  suffixArray "abacaabac" --(take 100000 ['a'..]) 

