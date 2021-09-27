import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation

total_frames = 1000

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

plt.xlim((0,10))
plt.ylim((0,10))

ani = animation.FuncAnimation(
    fig, animate, interval=2, blit=True, save_count=100, frames=total_frames)

Writer = animation.writers['ffmpeg']
writer = Writer(fps=60, metadata=dict(artist='Me'), bitrate=3000)
ani.save('video.mp4', writer=writer)
plt.show()




