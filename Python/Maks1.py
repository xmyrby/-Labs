a, k, n = map(int, input("Введите первый член, знаменатель и n: ").split())
s = a
for i in range(n):
    s += a
    a*=k

print(s)
