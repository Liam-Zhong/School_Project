try:
    TempStr = input()

    if TempStr[-1] in ['F', 'f']:
        C = (eval(TempStr[:-1]) - 32) / 1.8
        C = int(C)
        print("What is the temperature?The converted temperature is {:.0f}C".format(C))
    elif TempStr[-1] in ['C', 'c']:
        F = 1.8 * (eval(TempStr[:-1])) + 32
        F = int(F)
        print("What is the temperature?The converted temperature is {:.0f}F".format(F))
    else:
        print("What is the temperature?End with 'C','c','F','f'")
except NameError:
    print('What is the temperature?Input error')
except SyntaxError:
    print('What is the temperature?Input error')
