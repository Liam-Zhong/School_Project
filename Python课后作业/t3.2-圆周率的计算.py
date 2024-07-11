from math import pow
from random import random
from random import seed

seed(123)
P = eval(input())
hits = 0.0
for i in range(1, P + 1):
    x, y = random(), random()
    d = pow(x ** 2 + y ** 2, 0.5)
    if d <= 1.0:
        hits = hits + 1
pi = 4 * (hits / P)
print("{:.6f}".format(pi))
