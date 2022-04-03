import math

x, y = map(float, input('Введите x и y (через пробел): ').split())

if(y>=0):
    hyp = math.sqrt(x**2+y**2)
    if(hyp <= 4 and hyp > 2):
        print('Входит')
    else:
        print('Не входит')
else:
    if((x > -2 and x < 2 and y > -2) or x < -4 or x > 4 or y < -4):
        print('Не входит')
    else:
        print('Входит')
