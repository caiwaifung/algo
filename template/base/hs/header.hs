import qualified Data.ByteString.Char8 as B
import           Data.Functor
import           Data.List
import           Data.Maybe
import qualified Data.Set              as S

getInts :: IO [Int]
getInts = map (fst . fromJust . B.readInt) <$> B.words <$> B.getContents
getIntegers :: IO [Integer]
getIntegers = map (fst . fromJust . B.readInteger) <$> B.words <$> B.getContents
pair []       = []
pair (x:y:rs) = (x, y) : pair rs
clamp u v w = max u $ min v $ w
