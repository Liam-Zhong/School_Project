sum = 0
a = 1
n = eval(input())
if not type(n) == int or n <= 0:
    print("输入有误，请输入正整数")
else:
    for i in range(1, n + 1):
        a *= i
        sum += a
    print(sum)
