def isprime(num):
    isprime = 1
    for i in range(2, num):
        if num % i == 0:
            isprime = 0
    return isprime


li = [i for i in range(2, 1000) if isprime(i) == 1]
n = int(input())
num = n
m = []
while n != 1:
    for j in range(len(li)):
        if n % li[j] == 0:
            m.append((li[j]))
            n = n / li[j]
    if n == 1:
        break
m.sort()
print(m)
