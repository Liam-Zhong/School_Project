age = 0
list2 = ["0", "1", "2", "3", "4", "5", "6", "7", "8", "9"]  # 定义一个有0-9个数的列表
while age <= 100:  # 判断人的正常年龄范围
    num = str(age ** 3)  # 求立方
    ss = str(age ** 4)  # 求四次方
    if len(num) == 4 and len(ss) == 6:  # 判断这个数立方是四位数，四次方是六位数
        zzc = num + ss  # 将符合条件的四次方数和六次方数拼接
        list1 = list(zzc)  # 将拼接好的字符串变成列表
        list1.sort()  # 列表排序（升序）
        if list1 == list2:  # 判断如果有列表等于上面的列表，输出年龄
            print(age)
    else:
        pass
    age += 1
