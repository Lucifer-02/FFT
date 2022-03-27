import numpy as np
import matplotlib.pyplot as plt 
import subprocess

# Run FFT program
filename = 'G:/IMPORTANTS!!!/CODE/FFT256/FFT_Recursive.exe'
subprocess.Popen(['start', filename], shell=True)

# Shutdown console to take data
s = subprocess.check_output('tasklist', shell=False)
if b"FFT_Recursive.exe" in s:
    subprocess.call(['taskkill', '/F', '/IM', 'FFT_Recursive.exe'])

# Process data
data_name = 'FFT_Recursive'
file = open("G:/IMPORTANTS!!!/CODE/FFT256/Data/" + data_name + '.txt', 'r')
data = file.read()
data = data.split('\n')
data[0] = data[0].split(',')
data[1] = data[1].split(',')
X = []
x = []
for i in range(len(data[0])-1):
	x.append(float(data[0][i]))

for i in range(len(data[1])-1):
	X.append(float(data[1][i]))



# Display data
fig, axs = plt.subplots(nrows=2, ncols=1, figsize=(7, 7))

	# plot time signal:
axs[0].set_title(data_name)
axs[0].plot(x, color='green')
axs[0].set_xlabel("Time")
axs[0].set_ylabel("Amplitude")

	# plot freq signal:

axs[1].plot(X, color='red')
axs[1].set_xlabel("Frequency")
axs[1].set_ylabel("Amplitude")


plt.show()