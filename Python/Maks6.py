a1, k = map(float, input('Введите первый член и знаменатель (через пробел): ').split())
n = int(input('Введите n: '))
s = a1

for i in range(1, n):
    a1*=k
    s+=a1
print(f"{s:.3}")
 
