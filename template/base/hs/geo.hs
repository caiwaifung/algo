geoMult :: Num a => (a, a) -> (a, a) -> (a, a) -> a
geoMult (x0, y0) (x1, y1) (x2, y2) = (x1 - x0) * (y2 - y0) - (x2 - x0) * (y1 - y0)
