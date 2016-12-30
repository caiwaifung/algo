import Data.Functor

getInts :: IO [Int]
getInts = map read <$> words <$> getContents

parsePairs [] = []
parsePairs (x:y:rs) = (x, y) : parsePairs rs
