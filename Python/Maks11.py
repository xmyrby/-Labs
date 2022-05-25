N = int(input('Введите N: '))
a = 1
ps = ''
while(a != 0):
    a = int(input('Введите число (0 - остановка): '))
    if(a < N and a!=0):
        ps += str(a) + ' '

print('Последовательность:',ps)
