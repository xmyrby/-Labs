import math

z = float(input("Введите z: "))
summ = 0
for a in range(7,15):
    summ += a**3*math.cos(2*a)

summ*=z**3

print('Сумма = ', "{:.4f}".format(summ))
