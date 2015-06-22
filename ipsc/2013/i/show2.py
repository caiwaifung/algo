from PIL import Image

f = open('i2.in', 'r')
lines = f.readlines()
f.close()

n = int(lines[0].strip())
parse_line = lambda xs: [int(x) for x in xs.strip().split(' ')]
data = [parse_line(line) for line in lines[1:]]

f = open('ans.txt', 'r')
lines = f.readlines()
ans = [int(x) for x in lines[0].strip().split(' ')]
f.close()

for d in data:
    assert(len(d) == 1024)
assert(len(ans) == 1024)

img = Image.new('L', (28*40, 28*40))
pixels = img.load()
for i in range(28):
    for j in range(28):
        cur = i * 28 + j
        if cur >= n: continue
        x0, y0 = i * 40, j * 40
        for x in range(32):
            for y in range(32):
                pixels[y0 + y, x0 + x] = data[cur][x * 32 + y]

img.show()
