class BigFraction {
	private BigInteger x, y;
	public BigFraction() {
		x = new BigInteger("0");
		y = new BigInteger("1");
	}
	public BigFraction(BigInteger _x, BigInteger _y) {
		x = _x; y = _y;
	}
	public BigFraction(String _sx, String _sy) {
		x = new BigInteger(_sx);
		y = new BigInteger(_sy);
	}
	public BigFraction adjust() {
		BigInteger tmp = x.gcd(y);
		return new BigFraction(x.divide(tmp), y.divide(tmp));
	}
	public BigFraction add(BigFraction b) {
		BigInteger tx=x.multiply(b.y).add(y.multiply(b.x));
		BigInteger ty=y.multiply(b.y);
		return new BigFraction(tx, ty).adjust();
	}
	public BigFraction multiply(BigFraction b) {
		BigInteger tx=x.multiply(b.x);
		BigInteger ty=y.multiply(b.y);
		return new BigFraction(tx, ty).adjust();
	}
	public String toString() {
		return x.toString() + "/" + y.toString();
	}
};
