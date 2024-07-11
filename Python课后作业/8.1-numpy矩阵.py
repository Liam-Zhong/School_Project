import numpy as np

n = 4
a = np.zeros((n, n))
for i in range(n):
    a[i][i] = i + 1
print(a)
