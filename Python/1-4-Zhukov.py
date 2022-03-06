import math
a, b, x, y = map(float,input('Введите 3 числа (a,b,c) через пробел ').split())
s = 2**math.sin(x)+abs(a*x+b*y)/(1/math.tan(x**2+y**2))
print('s = ',"{:.3f}".format(s))