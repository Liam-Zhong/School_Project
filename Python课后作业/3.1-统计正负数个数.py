sum = 0
n = x = y = 0
z = 1
while z != 0:
    z = eval(input(""))
    sum += z
    n = n + 1
    if z < 0:
        x = x + 1
    else:
        y = y + 1
pj = sum / (n - 1)
print(pj)
print(y - 1)  # 最后一个是0
print(x)
