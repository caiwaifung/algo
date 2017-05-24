import qualified Data.ByteString.Char8 as B
import           Data.Functor
import           Data.List
import           Data.Maybe

getInts :: IO [Int]
getInts = map read <$> words <$> getContents
parsePairs []       = []
parsePairs (x:y:rs) = (x, y) : parsePairs rs

getInts :: IO [Int]
getInts = map (fst . fromJust . B.readInt) <$> B.words <$> B.getContents
pair []       = []
pair (x:y:rs) = (x, y) : pair rs
clamp u v w = max u $ min v $ w
