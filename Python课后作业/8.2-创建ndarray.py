import numpy as np


def main():
    n, m = input().split(" ")
    a = np.zeros(eval(n))
    # b = np.array()
    a[eval(m) - 1] = 1
    a = np.array([a])
    print(a)


if __name__ == "__main__":
    main()
