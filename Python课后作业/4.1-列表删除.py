import random

n = eval(input("输入一个1-100之间的正整数:"))
random.seed(n)
m = random.randrange(n)
list1 = []
list2 = []
for i in range(1, n + 1):
    list1.append(i)
print(list1)

'''for i in list1:
    if i % m == 0:
        list1.remove(i)
print(list1)
'''
for i in list1:
    if i % m != 0:
        list2.append(i)
print(list2)
