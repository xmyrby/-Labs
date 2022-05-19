import math

s = 0
for p in range(10,15):
    s += math.cos(2*p)*math.sin(3*p)

print('Сумма = ', "{:.4f}".format(s))
