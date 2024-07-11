credits = score = 0
gpa = [4.0, 3.7, 3.3, 3.0, 2.7, 2.3, 2.0, 1.5, 1.3, 1.0, 0];
level = ['A', 'A-', 'B+', 'B', 'B-', 'C+', 'C', 'C-', 'D', 'D-', 'F']
while True:
    str = input()
    if (str == '-1'):
        break
    else:
        temp = float(input())
        score += temp * gpa[level.index(str)]
        credits += temp
print("%.2f" % (score / credits))
