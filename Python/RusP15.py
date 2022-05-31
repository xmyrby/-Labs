import random

a = []
size = 0
while(size<3 or size >20):
    size = int(input('Введите размер (3-20): '))

count = 0
print('Массив:')
for i in range(size):
    a.append(random.randrange(-10,11))
    print(a[i])
    if(a[i]%2!=0):
        count+=1

print('Количество нечётных чисел =',count)
