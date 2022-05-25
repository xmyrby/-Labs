f = open('Файл2.txt','r', encoding="utf-8")
line = f.readline()
print('Количество комбинаций:',line.count("КОТ"))
f.close()
