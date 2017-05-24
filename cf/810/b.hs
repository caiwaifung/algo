import           Data.Functor
import           Data.List

getInts :: IO [Int]
getInts = map read <$> words <$> getContents
parsePairs []       = []
parsePairs (x:y:rs) = (x, y) : parsePairs rs
clamp u v w = max u $ min v $ w

main = getInts >>= print . go where
    go (_:f:xs) = solve f (parsePairs xs)

solve :: Int -> [(Int, Int)] -> Integer
solve f ps = base + bonus where
    base = sum . map toInteger $ [min u v | (u, v) <- ps]
    bonus = sum . map toInteger . take f . reverse . sort $ [clamp 0 u (v - u) | (u, v) <- ps]
