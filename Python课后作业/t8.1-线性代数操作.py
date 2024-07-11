import numpy as np

# 创建数组a和y
a = np.array([[1., 2.], [3., 4.]])
y = np.array([[5.], [7.]])

# 输出a数组

print(a)

# 输出a数组的转置

print(a.T)

# 输出形状为(2,2)的对角矩阵b
b = np.array([[1., .0], [.0, 1.]])
print(b)

# 输出对角矩阵的迹

print("{:.1f}".format(np.trace(b)))

# 求解数组a和数组y的解
x = np.linalg.solve(a, y)

print(x)

'''import numpy as np
import matplotlib.pyplot as plt
fig,ax = plt.subplots()
ax.plot(10*np.random.randn(100),10*np.random.randn(100),'o')
ax.set_title('Simple Scatter')
plt.show()'''  # 散点图

'''import numpy as np
import matplotlib.pyplot as plt
x = [1,2,3,4]
y = [10,50,30,70]
plt.plot(x,y,'r-*',linewidth = 2,ms=20,label='a')
plt.xticks(rotation=45)
plt.xlabel("date")
plt.ylabel("number")
plt.title("polyline chart")
plt.legend(loc="upper left")
plt.show()'''  # 折线图

'''import numpy as np
import matplotlib.pyplot as plt
np.random.seed(0)
mu,sigma=100,20
a=np.random.normal(mu,sigma,size=100)
plt.hist(a,20,histtype='stepfilled',
         facecolor='g',alpha=0.7)
plt.title("Histogram")

plt.show()'''  # 直方图

'''import matplotlib.pyplot as plt
labels='a','b','d','e'
size=[12,14,14,60]
explode=(0,0.1,0,0,)
plt.pie(size,explode=explode,labels=labels,
        autopct='%1.1f%%',shadow=False,startangle=90)


plt.show()'''  # 饼状图
