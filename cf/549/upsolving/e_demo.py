from matplotlib import pyplot

#a = [(-2, -1), (4,0), (5,2)]
#b = [(-3,-4), (3,2), (1,5)]

a=[(-9140,650), (-9126,669), (-9112,688)]
b=[(-9084,726), (-9098,707), (-9070,745)]


ax = [x for (x, y) in a]
ay = [y for (x, y) in a]
bx = [x for (x, y) in b]
by = [y for (x, y) in b]
print a, b
pyplot.plot(ax, ay, 'r*')
pyplot.plot(bx, by, 'b*')
pyplot.xlim(-9200, -9000)
pyplot.ylim(600, 800)
pyplot.show(block=True)
