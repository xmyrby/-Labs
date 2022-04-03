import math

x, y, r = map(float, input('Введите x, y и радиус круга (через пробел): ').split())

if(y>=0):
    hyp = math.sqrt(x**2+y**2)
    if(hyp <= r or y >= 2/r*x**2):
        print('Входит')
    else:
        print('Не входит')
else:
        print('Не входит')
