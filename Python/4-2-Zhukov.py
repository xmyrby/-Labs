a = 1
lst = []
while(a!=0):
    if(a%3==0):
        lst.append(a)
    a = int(input('Введите число: '))

print('Числа кратные 3:')
for i in range(len(lst)):
    print(lst[i],end = ' ')
