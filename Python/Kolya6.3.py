s = str(input("Введите текст: "))
s = s.replace(',', '').replace('.','')
a = -1
while(a<1 or a>2):
    a = int(input("Какие слова выводить?\n1 - Состоящие из чётного числа символов\n2 - Состоящие из нечётного числа символов\nВыбор: "))

count = 0
number = 0
print('Результат: ',end = ' ')
for i in range(0,len(s)):
    if(s[i]!=' '):
        count+=1
    else:
        if(a == 1):
            if(count%2 == 0):
                print(s.split()[number],end = ' ')
        else:
            if(count%2 != 0):
                print(s.split()[number],end = ' ')
        number+=1
        count = 0
