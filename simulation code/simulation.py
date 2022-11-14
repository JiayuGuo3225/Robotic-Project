import matplotlib.pyplot as plt
import math as m

# 1 robot collaborations 
def cord1(x1, y1, left, right, angleL, angleR):

    y = [0, 122]
    x = [0, 122]
    # left, right为机器人的左臂和右臂长度，angleL， angleR为机器人左臂和右臂扭转角度
    X1 = [x1 - left * m.cos(angleL), x1, x1 + right * m.cos(angleR)]# (x1, y1)为机器人中心坐标
    Y1 = [y1 + left * m.sin(angleL), y1, y1 + right * m.sin(angleR)]#纵坐标
    return x, y, X1, Y1

# start position
x, y, X1, Y1 = cord1(17, 0, 16, 16, 0, 0)
plt.figure( figsize=(10,10) )
plt.subplot(3, 3, 1)
plt.plot(X1,Y1,'o-',color = 'r',label="robot1")#s-:方形
plt.plot(x, y, color = 'w' )
plt.xlabel("start Position")#横坐标名字
plt.ylabel("vertical distance")#纵坐标名字
plt.legend(loc = "best")#图例


x, y, X1, Y1 = cord1(17, 20, 16, 16, 0, 0)
plt.subplot(3, 3, 2)
plt.plot(X1,Y1,'o-',color = 'r',label="robot1")#s-:方形
plt.plot(x, y, color = 'w' )
plt.xlabel("Incline Climbing ")#横坐标名字
plt.ylabel("vertical distance")#纵坐标名字
plt.legend(loc = "best")#图例


x, y, X1, Y1 = cord1(17, 30, 16, 16, 0, 0)
plt.subplot(3, 3, 3)
plt.plot(X1,Y1,'o-',color = 'r',label="robot1")#s-:方形
plt.plot(x, y, color = 'w' )
plt.xlabel("Incine Climbing stage")#横坐标名字
plt.ylabel("vertical distance")#纵坐标名字
plt.legend(loc = "best")#图例

x, y, X1, Y1 = cord1(17, 40, 16, 16, 0, 0)
plt.subplot(3, 3, 4)
plt.plot(X1,Y1,'o-',color = 'r',label="robot1")#s-:方形
plt.plot(x, y, color = 'w' )
plt.xlabel("Incine Climbing stage")#横坐标名字
plt.ylabel("vertical distance")#纵坐标名字
plt.legend(loc = "best")#图例


x, y, X1, Y1 = cord1(17, 60, 16, 16, 0, 0)
plt.subplot(3, 3, 5)
plt.plot(X1,Y1,'o-',color = 'r',label="robot1")#s-:方形
plt.plot(x, y, color = 'w' )
plt.xlabel("Incine Climbing stage")#横坐标名字
plt.ylabel("vertical distance")#纵坐标名字
plt.legend(loc = "best")#图例


x, y, X1, Y1 = cord1(17, 80, 16, 16, 0, 0)
plt.subplot(3, 3, 6)
plt.plot(X1,Y1,'o-',color = 'r',label="robot1")#s-:方形
plt.plot(x, y, color = 'w' )
plt.xlabel("Incine Climbing stage")#横坐标名字
plt.ylabel("vertical distance")#纵坐标名字
plt.legend(loc = "best")#图例


x, y, X1, Y1 = cord1(17, 90, 16, 16, 0, 0)
plt.subplot(3, 3, 7)
plt.plot(X1,Y1,'o-',color = 'r',label="robot1")#s-:方形
plt.plot(x, y, color = 'w' )
plt.xlabel("Incine Climbing stage")#横坐标名字
plt.ylabel("vertical distance")#纵坐标名字
plt.legend(loc = "best")#图例


x, y, X1, Y1 = cord1(17, 100, 16, 16, 0, 0)
plt.subplot(3, 3, 8)
plt.plot(X1,Y1,'o-',color = 'r',label="robot1")#s-:方形
plt.plot(x, y, color = 'w' )
plt.xlabel("Incine Climbing stage")#横坐标名字
plt.ylabel("vertical distance")#纵坐标名字
plt.legend(loc = "best")#图例


x, y, X1, Y1 = cord1(17, 122, 16, 16, 0, 0)
plt.subplot(3, 3, 9)
plt.plot(X1,Y1,'o-',color = 'r',label="robot1")#s-:方形
plt.plot(x, y, color = 'w' )
plt.xlabel("Reach the top")#横坐标名字
plt.ylabel("vertical distance")#纵坐标名字
plt.legend(loc = "best")#图例

plt.tight_layout()
plt.show()


# 2 robots collaborations 
def cord2(x1, y1, x2, y2, left, right, angleL, angleR):
    y = [0, 122]
    x = [0, 122]
    # left, right为机器人的左臂和右臂长度，angleL， angleR为机器人左臂和右臂扭转角度
    # robot1
    X1 = [x1 - left * m.cos(angleL), x1, x1 + right * m.cos(angleR)]# (x1, y1)为机器人中心坐标
    Y1 = [y1 + left * m.sin(angleL), y1, y1 + right * m.sin(angleR)]#纵坐标
    # robot2
    X2 = [x2 - left * m.cos(angleL), x2, x2 + right * m.cos(angleR)]# (x2, y2)为机器人中心坐标
    Y2 = [y2 + left * m.sin(angleL), y2, y2 + right * m.sin(angleR)]#纵坐标
    return x, y, X1, Y1, X2, Y2

# start position
x, y, X1, Y1, X2, Y2 = cord2(17, 0, 49, 0, 16, 16, 0, 0)
plt.figure( figsize=(10,10) )
plt.subplot(3, 3, 1)
plt.plot(X1,Y1,'s-',color = 'r',label="robot1")#s-:方形
plt.plot(X2,Y2,'s-',color = 'g',label="robot2")#o-:圆形
plt.plot(x, y, color = 'w' )
plt.xlabel("start line")#横坐标名字
plt.ylabel("vertical distance")#纵坐标名字
plt.legend(loc = "best")#图例


x, y, X1, Y1, X2, Y2 = cord2(17, 0, 49, 0, 16, 16, 0, 0)
plt.subplot(3, 3, 2)
plt.plot(X1,Y1,'s-',color = 'r',label="robot1")#s-:方形
plt.plot(X2,Y2,'s-',color = 'g',label="robot2")#o-:圆形
plt.plot(x, y, color = 'w' )
plt.xlabel("start line")#横坐标名字
plt.ylabel("vertical distance")#纵坐标名字
plt.legend(loc = "best")#图例

x, y, X1, Y1, X2, Y2 = cord2(17, 0, 49, 0, 16, 16, 0, 0)
plt.subplot(3, 3, 3)
plt.plot(X1,Y1,'s-',color = 'r',label="robot1")#s-:方形
plt.plot(X2,Y2,'s-',color = 'g',label="robot2")#o-:圆形
plt.plot(x, y, color = 'w' )
plt.xlabel("start line")#横坐标名字
plt.ylabel("vertical distance")#纵坐标名字
plt.legend(loc = "best")#图例

x, y, X1, Y1, X2, Y2 = cord2(17, 0, 49, 0, 16, 16, 0, 0)
plt.subplot(3, 3, 4)
plt.plot(X1,Y1,'s-',color = 'r',label="robot1")#s-:方形
plt.plot(X2,Y2,'s-',color = 'g',label="robot2")#o-:圆形
plt.plot(x, y, color = 'w' )
plt.xlabel("start line")#横坐标名字
plt.ylabel("vertical distance")#纵坐标名字
plt.legend(loc = "best")#图例

x, y, X1, Y1, X2, Y2 = cord2(17, 0, 49, 0, 16, 16, 0, 0)
plt.subplot(3, 3, 5)
plt.plot(X1,Y1,'s-',color = 'r',label="robot1")#s-:方形
plt.plot(X2,Y2,'s-',color = 'g',label="robot2")#o-:圆形
plt.plot(x, y, color = 'w' )
plt.xlabel("start line")#横坐标名字
plt.ylabel("vertical distance")#纵坐标名字
plt.legend(loc = "best")#图例

x, y, X1, Y1, X2, Y2 = cord2(17, 0, 49, 0, 16, 16, 0, 0)
plt.subplot(3, 3, 6)
plt.plot(X1,Y1,'s-',color = 'r',label="robot1")#s-:方形
plt.plot(X2,Y2,'s-',color = 'g',label="robot2")#o-:圆形
plt.plot(x, y, color = 'w' )
plt.xlabel("start line")#横坐标名字
plt.ylabel("vertical distance")#纵坐标名字
plt.legend(loc = "best")#图例

x, y, X1, Y1, X2, Y2 = cord2(17, 0, 49, 0, 16, 16, 0, 0)
plt.subplot(3, 3, 7)
plt.plot(X1,Y1,'s-',color = 'r',label="robot1")#s-:方形
plt.plot(X2,Y2,'s-',color = 'g',label="robot2")#o-:圆形
plt.plot(x, y, color = 'w' )
plt.xlabel("start line")#横坐标名字
plt.ylabel("vertical distance")#纵坐标名字
plt.legend(loc = "best")#图例

x, y, X1, Y1, X2, Y2 = cord2(17, 0, 49, 0, 16, 16, 0, 0)
plt.subplot(3, 3, 8)
plt.plot(X1,Y1,'s-',color = 'r',label="robot1")#s-:方形
plt.plot(X2,Y2,'s-',color = 'g',label="robot2")#o-:圆形
plt.plot(x, y, color = 'w' )
plt.xlabel("start line")#横坐标名字
plt.ylabel("vertical distance")#纵坐标名字
plt.legend(loc = "best")#图例

x, y, X1, Y1, X2, Y2 = cord2(17, 0, 49, 0, 16, 16, 0, 0)
plt.subplot(3, 3, 9)
plt.plot(X1,Y1,'s-',color = 'r',label="robot1")#s-:方形
plt.plot(X2,Y2,'s-',color = 'g',label="robot2")#o-:圆形
plt.plot(x, y, color = 'w' )
plt.xlabel("start line")#横坐标名字
plt.ylabel("vertical distance")#纵坐标名字
plt.legend(loc = "best")#图例

plt.tight_layout()
plt.show()

# 3 robots collaborations 
def cord3(x1, y1, x2, y2, x3, y3, left, right, angleL, angleR):
    y = [0, 122]
    x = [0, 122]
    # left, right为机器人的左臂和右臂长度，angleL， angleR为机器人左臂和右臂扭转角度
    # robot1
    X1 = [x1 - left * m.cos(angleL), x1, x1 + right * m.cos(angleR)]# (x1, y1)为机器人中心坐标
    Y1 = [y1 + left * m.sin(angleL), y1, y1 + right * m.sin(angleR)]#纵坐标
    # robot2
    X2 = [x2 - left * m.cos(angleL), x2, x2 + right * m.cos(angleR)]# (x2, y2)为机器人中心坐标
    Y2 = [y2 + left * m.sin(angleL), y2, y2 + right * m.sin(angleR)]#纵坐标
    # robot3
    X3 = [x3 - left * m.cos(angleL), x3, x3 + right * m.cos(angleR)]# (x3, y3)为机器人中心坐标
    Y3 = [y3 + left * m.sin(angleL), y3, y3 + right * m.sin(angleR)]#纵坐标
    return x, y, X1, Y1, X2, Y2, X3, Y3

# start position
x, y, X1, Y1, X2, Y2, X3, Y3 = cord3(17, 0, 49, 0, 81, 0, 16, 16, 0, 0)
plt.figure( figsize=(10,10) )
plt.subplot(3, 3, 1)
plt.plot(X1,Y1,'s-',color = 'r',label="robot1")#s-:方形
plt.plot(X2,Y2,'s-',color = 'g',label="robot2")#o-:圆形
plt.plot(X3,Y3,'s-',color = 'b',label="robot3")
plt.plot(x, y, color = 'w' )
plt.xlabel("start line")#横坐标名字
plt.ylabel("vertical distance")#纵坐标名字
plt.legend(loc = "best")#图例


x, y, X1, Y1, X2, Y2, X3, Y3 = cord3(17, 0, 49, 0, 81, 0, 16, 16, 0, 0)
plt.subplot(3, 3, 2)
plt.plot(X1,Y1,'s-',color = 'r',label="robot1")#s-:方形
plt.plot(X2,Y2,'s-',color = 'g',label="robot2")#o-:圆形
plt.plot(X3,Y3,'s-',color = 'b',label="robot3")
plt.plot(x, y, color = 'w' )
plt.xlabel("start line")#横坐标名字
plt.ylabel("vertical distance")#纵坐标名字
plt.legend(loc = "best")#图例

x, y, X1, Y1, X2, Y2, X3, Y3 = cord3(17, 0, 49, 0, 81, 0, 16, 16, 0, 0)
plt.subplot(3, 3, 3)
plt.plot(X1,Y1,'s-',color = 'r',label="robot1")#s-:方形
plt.plot(X2,Y2,'s-',color = 'g',label="robot2")#o-:圆形
plt.plot(X3,Y3,'s-',color = 'b',label="robot3")
plt.plot(x, y, color = 'w' )
plt.xlabel("start line")#横坐标名字
plt.ylabel("vertical distance")#纵坐标名字
plt.legend(loc = "best")#图例

x, y, X1, Y1, X2, Y2, X3, Y3 = cord3(17, 0, 49, 0, 81, 0, 16, 16, 0, 0)
plt.subplot(3, 3, 4)
plt.plot(X1,Y1,'s-',color = 'r',label="robot1")#s-:方形
plt.plot(X2,Y2,'s-',color = 'g',label="robot2")#o-:圆形
plt.plot(X3,Y3,'s-',color = 'b',label="robot3")
plt.plot(x, y, color = 'w' )
plt.xlabel("start line")#横坐标名字
plt.ylabel("vertical distance")#纵坐标名字
plt.legend(loc = "best")#图例


x, y, X1, Y1, X2, Y2, X3, Y3 = cord3(17, 0, 49, 0, 81, 0, 16, 16, 0, 0)
plt.subplot(3, 3, 5)
plt.plot(X1,Y1,'s-',color = 'r',label="robot1")#s-:方形
plt.plot(X2,Y2,'s-',color = 'g',label="robot2")#o-:圆形
plt.plot(X3,Y3,'s-',color = 'b',label="robot3")
plt.plot(x, y, color = 'w' )
plt.xlabel("start line")#横坐标名字
plt.ylabel("vertical distance")#纵坐标名字
plt.legend(loc = "best")#图例

x, y, X1, Y1, X2, Y2, X3, Y3 = cord3(17, 0, 49, 0, 81, 0, 16, 16, 0, 0)
plt.subplot(3, 3, 6)
plt.plot(X1,Y1,'s-',color = 'r',label="robot1")#s-:方形
plt.plot(X2,Y2,'s-',color = 'g',label="robot2")#o-:圆形
plt.plot(X3,Y3,'s-',color = 'b',label="robot3")
plt.plot(x, y, color = 'w' )
plt.xlabel("start line")#横坐标名字
plt.ylabel("vertical distance")#纵坐标名字
plt.legend(loc = "best")#图例

x, y, X1, Y1, X2, Y2, X3, Y3 = cord3(17, 0, 49, 0, 81, 0, 16, 16, 0, 0)
plt.subplot(3, 3, 7)
plt.plot(X1,Y1,'s-',color = 'r',label="robot1")#s-:方形
plt.plot(X2,Y2,'s-',color = 'g',label="robot2")#o-:圆形
plt.plot(X3,Y3,'s-',color = 'b',label="robot3")
plt.plot(x, y, color = 'w' )
plt.xlabel("start line")#横坐标名字
plt.ylabel("vertical distance")#纵坐标名字
plt.legend(loc = "best")#图例

x, y, X1, Y1, X2, Y2, X3, Y3 = cord3(17, 0, 49, 0, 81, 0, 16, 16, 0, 0)
plt.subplot(3, 3, 8)
plt.plot(X1,Y1,'s-',color = 'r',label="robot1")#s-:方形
plt.plot(X2,Y2,'s-',color = 'g',label="robot2")#o-:圆形
plt.plot(X3,Y3,'s-',color = 'b',label="robot3")
plt.plot(x, y, color = 'w' )
plt.xlabel("start line")#横坐标名字
plt.ylabel("vertical distance")#纵坐标名字
plt.legend(loc = "best")#图例

x, y, X1, Y1, X2, Y2, X3, Y3 = cord3(17, 0, 49, 0, 81, 0, 16, 16, 0, 0)
plt.subplot(3, 3, 9)
plt.plot(X1,Y1,'s-',color = 'r',label="robot1")#s-:方形
plt.plot(X2,Y2,'s-',color = 'g',label="robot2")#o-:圆形
plt.plot(X3,Y3,'s-',color = 'b',label="robot3")
plt.plot(x, y, color = 'w' )
plt.xlabel("start line")#横坐标名字
plt.ylabel("vertical distance")#纵坐标名字
plt.legend(loc = "best")#图例

plt.tight_layout()
plt.show()