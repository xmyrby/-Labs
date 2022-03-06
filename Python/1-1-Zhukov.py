#Импортирование числа pi
from math import pi
#Ввод l в метрах
l = int(input('Print l metres = '))
#Получение радиуса
R = l/(2*pi)
#Получение площади
S = l*R/2
#Вывод S
print('S = ', S ,' metres^2')