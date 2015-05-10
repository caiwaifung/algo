import Data.Char
import Data.List
import Data.Maybe
import Control.Monad
import qualified Data.Set as Set

input = concat [ "ejp mysljylc kd kxveddknmc re jsicpdrysi"
               , "rbcpc ypc rtcsra dkh wyfrepkym veddknkmkrkcd"
               , "de kr kd eoya kw aej tysr re ujdr lkgc jv"
               ]

output = concat [ "our language is impossible to understand"
                , "there are twenty six factorial possibilities"
                , "so it is okay if you want to just give up"
                ]

lst = zip (filter isLower input) (filter isLower output)

unknownI = ['a'..'z'] \\ map fst lst
unknownO = ['a'..'z'] \\ map snd lst

mapping = lst ++ zip unknownI (permutations unknownO !! tryID)

func x = fromMaybe x (x `lookup` mapping)

tryID = 1

main = do
    tests <- fmap read getLine
    forM_ [1..tests] $ \test -> do
        str <- getLine
        putStrLn $ "Case #" ++ show test ++ ": " ++ map func str
