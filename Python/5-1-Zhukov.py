n = int(input("Введите n: "))
x = float(input("Введите x: "))
sum = 1

for i in range(1,n):
    sum += x**i/(2*i)
print(sum)
