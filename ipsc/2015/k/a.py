import numpy as np
import math
import wave
from matplotlib import pyplot

def read(file_path):
    f = wave.open(file_path, "rb")
    params = f.getparams()
    nchannels, sampwidth, framerate, nframes = params[:4]
    str_data = f.readframes(nframes)
    f.close()
    wave_data = np.fromstring(str_data, dtype = np.short)
    return wave_data

def write(file_path, data, samplerate):
    f = wave.open(file_path, "wb")
    f.setnchannels(1)
    f.setsampwidth(2)
    #f.setframerate(44100)
    f.setframerate(samplerate)
    f.writeframes(data)
    f.writeframes(data)
    f.close()

a = read('../_downloads/k2.wav')
l = np.array(a[::2])
r = np.array(a[1::2])
assert(len(l) == len(r))

ks = '254341551554451532121245113555112132343531511135144151235553125151551122215535415551134'
keys = [ord(c) - ord('1') for c in ks]

def ampl(a):
    a = np.array(a, dtype=float)
    a1 = a[:-1]
    a2 = a[1:]
    return np.linalg.norm(a1 - a2) / 30000. / 10

def g(k, d):
    return math.tan(d * 3.14159 / 2) ** 2
'''
    if k==4: return d
    if k==3: return d
    if k==2: return d
    if k==1: return d
    if k==0: return d
'''

pyplot.figure(9, figsize=(15,2))
for cur in range(87):
    cl = np.array(l[cur*66140:(cur+1)*66140])
    cr = np.array(r[cur*66140:(cur+1)*66140])
    ampl_l = ampl(cl)
    ampl_r = ampl(cr)
    if ampl_l + ampl_r < 0.1:
        print 'bad', cur
        continue
    key = keys[cur]
    #key = 4 - cur // 56
    delta = -(ampl_l - ampl_r) / max(ampl_l, ampl_r)
    #print abs(cl).argmax(), abs(cr).argmax()
    #delta = (abs(cl).argmax() - abs(cr).argmax()) 
    if delta > 0:
        delta = g(key, delta)
    else:
        delta = -g(key, -delta)
    '''
    if ampl_l > ampl_r:
        delta = -1 + ampl_l
    else:
        delta = 1 - ampl_r
    '''

    pyplot.plot([delta], [key], 'ro')
    print cur, key, delta

pyplot.plot([0], [-1], '+')
pyplot.plot([0], [5], '+')

pyplot.savefig('tmp.png')
