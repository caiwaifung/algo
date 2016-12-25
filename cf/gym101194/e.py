import sys

def solve():
    n = int(sys.stdin.readline().strip())
    xs = []
    for i in range(n):
        nums = [float(s) for s in sys.stdin.readline().strip().split(':')]
        a = int(nums[0] * 1000)
        b = int(nums[1] * 1000)
        xs.append((a, a + b))
    for i in range(n):
        for j in range(i+1, n):
            if xs[i][0] * xs[j][1] > xs[j][0] * xs[i][1]:
                xs[i], xs[j] = xs[j], xs[i]
    ru, rv = 1, 1
    for i in range(n):
        u, v = xs[i]
        if ru * v <= u * rv:
            return i
        ru = ru * v - u * rv
        rv *= v
    return n

ncs = int(sys.stdin.readline().strip())
for cs in range(ncs):
    print "Case #%d:" % (cs+1), solve()

