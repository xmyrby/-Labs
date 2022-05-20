s = str(input("Введите строку: "))
count = 0
for i in range(10):
    count+=s.count(str(i))
    s = s.replace(str(i),'')

print('Полученная строка: ',s,'\nКоличество удалённых цифр: ',count)
