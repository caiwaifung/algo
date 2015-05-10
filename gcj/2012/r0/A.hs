import Data.Char
import Data.List
import Data.Maybe
import Control.Monad
import qualified Data.Set as Set

input = concat [ "ejp mysljylc kd kxveddknmc re jsicpdrysi"
               , "rbcpc ypc rtcsra dkh wyfrepkym veddknkmkrkcd"
               , "de kr kd eoya kw aej tysr re ujdr lkgc jv"
	       , "aoz"
               ]

output = concat [ "our language is impossible to understand"
                , "there are twenty six factorial possibilities"
                , "so it is okay if you want to just give up"
		, "yeq"
                ]

lst = zip (filter isLower input) (filter isLower output)

unknownI = ['a'..'z'] \\ map fst lst
unknownO = ['a'..'z'] \\ map snd lst

mapping = lst ++ zip unknownI (permutations unknownO !! 0)

func x = fromMaybe x (find (\p -> ((fst p)==x)) mapping)

main = do
    tests <- fmap read getLine
    forM_ [1..tests] $ \test -> do
        str <- getLine
        putStrLn $ "Case #" ++ show test ++ ": " ++ map func str
