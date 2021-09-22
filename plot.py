import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation

total_frames = 100

data = [None]*total_frames
fig, ax = plt.subplots()

for i in range(total_frames):
    data[i]= np.loadtxt("Data/birds"+str(i))

xdata, ydata = [],[]

ln, = plt.plot([], [], marker="o",ls="")

def animate(i):
    xdata = data[i][:, 0]
    ydata = data[i][:, 1]
    ln.set_data(xdata, ydata)
    return ln,

ani = animation.FuncAnimation(
    fig, animate, interval=2, blit=True, save_count=100, frames=total_frames)

plt.xlim((0,5))
plt.ylim((0,5))

plt.show()




