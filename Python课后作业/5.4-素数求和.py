def find(n):
    for i in range(2, int(n ** 0.5) + 1):
        if n % i == 0:
            return False
    return True


def f(n):
    ls = []
    for i in range(2, n + 1):
        if find(i):
            ls.append(i)
    return sum(ls[-10:])


p = int(input())
print(f(p))
