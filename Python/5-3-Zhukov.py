import math

c,z = map(float,input("Введите c и z (через пробел): ").split())
summ = 0
for s in range(1,8):
    summ += s**2*math.sin(s*c)

summ*=math.log(z)

print('Сумма = ', "{:.4f}".format(summ))
