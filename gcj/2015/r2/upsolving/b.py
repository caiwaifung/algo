f = open('/Users/caiwaifung/Downloads/B-large-practice.in', 'r')
#f = open('b.in', 'r')
lines = f.readlines()
f.close()

def ok(N, V, X, R, C, t):
    '''
    print 'ok:',N,V,X
    for i in range(N):
        print R[i], C[i]
    '''

    rest = V
    s = 0
    for i in range(N):
        cur = min(rest, R[i] * t)
        rest -= cur
        s += cur * C[i]
    if rest > 0:
        return False
    if s > V * X:
        return False

    rest = V
    s = 0
    for i in reversed(range(N)):
        cur = min(rest, R[i] * t)
        rest -= cur
        s += cur * C[i]
    if s < V * X:
        return False
    return True


def solve(N, V, X, R, C):
    #print N, V, X
    #for i in range(N):
        #print R[i], C[i]
    times = 10000000
    V = V * times
    le = 0
    ri = 100000000 * times
    while le < ri:
        mid = (le + ri) / 2
        if ok(N, V, X, R, C, mid):
            ri = mid
        else:
            le = mid + 1
    if not ok(N, V, X, R, C, le):
        print 'IMPOSSIBLE'
    else:
        ans = float(le) / float(times)
        print '{0:.9f}'.format(ans)


cases = int(lines[0].strip())
ind = 1
for cs in range(cases):
    N = int(lines[ind].split(' ')[0].strip())
    V = int(float(lines[ind].split(' ')[1].strip()) * 10000 + 0.3)
    X = int(float(lines[ind].split(' ')[2].strip()) * 10000 + 0.3)
    ind += 1

    tmp = []
    for i in range(N):
        r = int(float(lines[ind].split(' ')[0].strip()) * 10000 + 0.3)
        c = int(float(lines[ind].split(' ')[1].strip()) * 10000 + 0.3)
        tmp.append((c, r))
        ind += 1
    tmp = sorted(tmp)
    R = [t[1] for t in tmp]
    C = [t[0] for t in tmp]

    print 'Case #{}:'.format(cs + 1),
    solve(N, V, X, R, C)




