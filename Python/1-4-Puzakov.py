import math
x = float(input('Введите x: '))
s = 2*x*math.e**(2*x)+math.fabs(x**2*math.cos(3*math.pi*x))/(2*math.sin(x**2)**2)
print('s = ',"{:.3f}".format(s))
