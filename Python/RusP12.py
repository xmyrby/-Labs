#Ввод строки
s = str(input("Введите строку: "))+'.'

#Количество пробелов подряд
c = 0
#Максимальное количество
m = 0

#Цикл перебора символов
for i in range(len(s)):
    #Проверка является ли символ пробелом
    if(s[i] == ' '):
        #Увеличение счётчика
        c+=1
    #Если символ не пробел - завершить подсчёт
    else:
        #Обновление максимума
        m=max(c,m)
        #Обнуление счётчика
        c=0
#Ввод максимального количества пробелом идущих подряд
print('Максимальное кол-во подряд идущих пробелов =',m)
    
