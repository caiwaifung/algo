import numpy as np
import wave

def read(file_path):
    f = wave.open(file_path, "rb")
    params = f.getparams()
    nchannels, sampwidth, framerate, nframes = params[:4]
    str_data = f.readframes(nframes)
    f.close()
    wave_data = np.fromstring(str_data, dtype = np.short)
    return wave_data

def read2(file_path): # read wave of double channels
    data = read(file_path)
    print "len = ", len(data)
    n = len(data) / 2
    print "n = ", n
    a = data[0:n]
    for i in range(n):
        a[i] = data[i*2]
    return a

def write(file_path, data, samplerate):
    f = wave.open(file_path, "wb")
    f.setnchannels(1)
    f.setsampwidth(2)
    #f.setframerate(44100)
    f.setframerate(samplerate)
    f.writeframes(data)
    f.writeframes(data)
    f.close()
