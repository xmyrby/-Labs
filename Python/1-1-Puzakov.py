import math
a, b, A = map(float, input('Введите a, b и A: ').split())
s = a * b * math.sin(A * (180/math.pi))
print('s = ', "{:.3f}".format(s))
