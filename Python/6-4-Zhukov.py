#Ввод строки

#Проверка ввода
while 1:
    s = str(input("Введите строку: "))
    if s:
        break
#Инициализация счётчика
count = 0
#Перебор всех цифр
for i in range(10):
    #Увеличение счётчика на количество найденных цифр
    count+=s.count(str(i))
    #Удаление цифр из строки
    s = s.replace(str(i),'')

#Вывод результата
if(count):
    print('Полученная строка: ',s,'\nКоличество удалённых цифр: ',count)
else:
    print('В тексте нет цифр')
