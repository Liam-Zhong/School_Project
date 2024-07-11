def cmul(*num):
    mul = 1
    for i in num:
        mul *= i
    return mul


print(eval("cmul({})".format(input())))
