from math import e
a, b, c = map(float,input('Введите 3 числа (a,b,c) через пробел ').split())
y = (e**(-a**2))**0.2+b/(9*c**3)
print('y = ',"{:.3f}".format(y))