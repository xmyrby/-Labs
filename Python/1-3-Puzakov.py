import math
a, b, c = map(float,input('Введите 3 числа (a,b,c) через пробел ').split())
y = ((2*math.e**(a*b))**0.1-4*math.log(5*c,10))/7*math.log(a*b**2,10)
print('y = ',"{:.3f}".format(y))
