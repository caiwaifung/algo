import qualified Data.ByteString.Char8 as B
import           Data.Functor
import           Data.List
import           Data.Maybe

getInts :: IO [Int]
getInts = map (fst . fromJust . B.readInt) <$> B.words <$> B.getContents
pair []       = []
pair (x:y:rs) = (x, y) : pair rs
clamp u v w = max u $ min v $ w

main = do
    _:f:xs <- getInts
    print $ solve f (pair xs)

solve :: Int -> [(Int, Int)] -> Integer
solve f ps = base + bonus where
    base = sum . map toInteger $ [min u v | (u, v) <- ps]
    bonus = sum . map toInteger . take f . reverse . sort $ [clamp 0 u (v - u) | (u, v) <- ps]
