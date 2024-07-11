# 判断n是否为素数
def isprime(n):
    for i in range(2, int(n ** 0.5) + 1):
        if n % i == 0:
            return False
    return True


n = int(input())
if n % 2 == 1:
    print("Data error!")
else:
    for i in range(2, n):
        if isprime(i):  # p是素数
            if isprime(n - i):  # q也是素数
                print(f"N = {i} + {n - i}")
                break
