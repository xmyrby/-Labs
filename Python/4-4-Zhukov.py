a = ''
lst = []
c=0
mini = 1000
maxi = -1000
a = input('Введите число (stop - для остановки ввода): ')
while(a != 'stop' and a != 'стоп'):
    number = int(a)
    if(number%2!=0):
        mini=min(mini,number)
        maxi=max(maxi,number)
        c+=1
    a = input('Введите число (stop - для остановки ввода): ')
else:
    if(c>0):
        print('Количество нечётных чисел: ',c,'\nМинимальное число: ',mini,'\nМаксимальное число: ',maxi)
    else:
        print('Нечётных чисел нет')

