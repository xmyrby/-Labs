#Открытие файла
f = open('8-2-7.txt', 'r')
#Чтение файла
s = f.read()
#Задание искомого слова
sub = 'BOSS'
#Получение позиции
pos = s.find(sub)

k = 0
while pos != -1:
    #Проверка
    if s[pos-1] != 'J' and s[pos+4] != 'J':
        k += 1
    #Получение следующей позиции
    pos = s.find(sub, pos + 1)
#Вывод
print(k)
