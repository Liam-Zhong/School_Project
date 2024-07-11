f1 = open("in162.txt", "r")
ret = count = 0
for line in f1:
    content = list(line.split())
    for i in content:
        ret += eval(i) * 0.454
        count += 1
        if (count == 10): break
    if count == 10: break
f2 = open("out162.txt", "w")
f2.write("%.2f" % ret)
f1.close()
f2.close()
