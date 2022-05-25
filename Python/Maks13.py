a = ''
lst = []
c=0
summ = 0
a = input('Введите число (stop - для остановки ввода): ')
while(a != 'stop' and a != 'стоп'):
    number = int(a)
    if(number%6==0):
        summ+=number
        c+=1
    a = input('Введите число (stop - для остановки ввода): ')
else:
    if(c>0):
        print('Количество чисел кратных 6: ',c,'\nСумма равна: ',summ)
    else:
        print('Чисел кратных 6 нет')

