def cacluate(num):
    avg = sum(num) / len(num)
    up_avg = []
    for i in range(len(num)):
        if num[i] > avg:
            up_avg.append(num[i])
    return avg, up_avg


num1 = input("Please input numbers,and press the Enter to end.(gap with ,)\n").split(",")
num2 = list(map(int, num1))
a = cacluate(num2)
print(a)
