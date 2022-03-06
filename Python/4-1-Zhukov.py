a = int(input('Введите A: '))
c = a
b = 0
while(c>0):
    b += c%10
    c //= 100
print('Разница: ',a-b)
