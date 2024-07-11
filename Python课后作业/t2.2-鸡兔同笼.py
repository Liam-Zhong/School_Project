a, b = map(int, input().split(' '))  # 读入两个整数到a，b中，输入的数用空格分隔
i = 0
while (i <= a):
    if (2 * i + 4 * (a - i) != b):
        i += 1
    else:
        break
if (i != 0 and i <= a):
    print(i, a - i, end=" ")
else:
    print("Data Error!")
