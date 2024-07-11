def hanoi(n, A, B, C):
    global step
    if n == 1:
        print(f"[STEP  {step:>2}] {A}->{C}")
        step += 1
    else:
        hanoi(n - 1, A, C, B)
        print(f"[STEP  {step:>2}] {A}->{C}")
        step += 1
        hanoi(n - 1, B, A, C)


n = int(input(""))
step = 1
hanoi(n, 'A', 'B', 'C')
