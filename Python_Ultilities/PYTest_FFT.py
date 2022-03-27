from scipy.fft import fft, ifft
import numpy as np
import matplotlib.pyplot as plt

x = np.array([1.0, 2.0, 1.0, -1.0, 1.5])

y = fft(x)

for i in range(len(y)):
    print(y[i])

print("-----------------------------------------")

iy = ifft(y)

for i in range(len(iy)):
    print(iy[i])

plt.plot(x)
