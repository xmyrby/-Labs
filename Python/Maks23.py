import random

a = []
size = 0
while(size<3 or size >20):
    size = int(input('Введите размер (3-20): '))

print('Массив:')
s=0
for i in range(size):
    a.append(random.randrange(-10,11))
    if(a[i]>=0):
        s+=a[i]
    print(a[i],end = ' ')

print('\nСумма положительных:',s)
