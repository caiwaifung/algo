from matplotlib import pyplot
import numpy as np

a = np.loadtxt('t.txt')
a = a[:, 1:]

pyplot.plot(a[:, 0], a[:, 0], 'ro')

pyplot.savefig('tmp.png')
