with open('mayun.txt', 'r') as f:
    s = f.read()

n_upper = n_lower = n_digit = n_space = n_other = 0
for i in s:
    if i.isupper():
        n_upper += 1
    elif i.islower():
        n_lower += 1
    elif i.isdigit():
        n_digit += 1
    elif i.isspace():
        n_space += 1
    else:
        n_other += 1
print(n_upper, n_lower, n_digit, n_space, n_other)

s_ls = s.replace(',', ' ').split()
print(f"{len(s_ls)} words in all")

week = input()
offset = sum([ord(i) for i in week]) % 26
print(offset)

s_cipher = ""
for i in s:
    if "a" <= i <= "z":
        s_cipher += chr((ord(i) - ord("a") + offset) % 26 + ord("a"))
    elif "A" <= i <= "Z":
        s_cipher += chr((ord(i) - ord("A") + offset) % 26 + ord("A"))
    else:
        s_cipher += i
print(s_cipher)
