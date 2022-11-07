import matplotlib.animation as animation
import matplotlib.pyplot as plt
import numpy as np

# 测试正余弦函数动图
# X = np.arange(0, 10, 0.01)  # X shape： (N,)
# Ys = [np.sin(X + k/10.0) for k in range(100)]  # Ys shape： (k, N)

# fig, axes = plt.subplots(nrows=1, ncols=2, figsize=(8, 4))

# def animate(i):
#     axes[0].cla()
#     axes[0].plot(X, Ys[i])
#     axes[0].set_title(f'y = sin(x + {i}/10)')

#     axes[1].cla()
#     axes[1].hist(Ys[i], bins=50, orientation='horizontal')

# ani = animation.FuncAnimation(fig, animate, frames=50, interval=50)
# ani.save('matplotlib-animation-hist.gif')
# plt.show()

# leg length = 16
time = 0
# 一号机器人起始位置 position (16, 0)
x1 = 16

# 二号机器人起始位置， start position (49, 0)
x2 = 49

# 三号机器人起始位置，start position (82, 0) 
x3 = 82

# 机械臂摆动随时间变化的轨迹
# 一号机器人机械臂摆动随时间变化的轨迹

if 0 < time < 2: # right arm swing
    y1 = 
    time += 1
elif 2 < time < 4: # left arm swing
    y1 = 
    time += 1

# 二号机器人机械臂摆动随时间变化的轨迹
elif 4 < time < 6: # right arm swing
    y2 = 
    time += 1
elif 8 < time < 10: # left arm swing
    y2 = 
    time += 1

elif 10 < time < 12: # docking
    y1 = 
    y2 = 
elif 12 < time < 15: # lifting
    y1 = 
    y2 = 

# 三号机器人机械臂摆动随时间变化的轨迹
y3 = 

fig, axes = plt.subplots(nrows=1, ncols=2, figsize=(8, 4))

def animate(i):
    axes[0].cla()
    axes[0].plot(x1, y1[i])
    axes[0].set_title(f'y = ')

    axes[1].cla()
    axes[1].hist(y1[i], bins=50, orientation='horizontal')
    
    axes[0].cla()
    axes[0].plot(x2, y2[i])
    axes[0].set_title(f'y = ')

    axes[1].cla()
    axes[1].hist(y2[i], bins=50, orientation='horizontal')
    
    axes[0].cla()
    axes[0].plot(x3, y3[i])
    axes[0].set_title(f'y = ')

    axes[1].cla()
    axes[1].hist(y3[i], bins=50, orientation='horizontal')

ani = animation.FuncAnimation(fig, animate, frames=50, interval=50)
ani.save('matplotlib-animation-hist.gif')
plt.show()