import Data.Functor
import Data.List

getInts :: IO [Int]
getInts = map read <$> words <$> getContents

main = getInts >>= putStrLn . intercalate " " . map show . solve

solve :: [Int] -> [Int]
solve (n:xs) = map snd . sort $ zip is es
    where (ys, is) = unzip . reverse . sort $ zip xs [0..]
          (zs, es) = unzip . scanl1 min $ zip ys [1,2..]
