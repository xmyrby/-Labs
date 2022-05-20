tp = 0

while(tp < 1 or tp > 2):
    tp = int(input("Выберите тип ввода\n1 - 85 цифр 9\n2 - Ручной ввод\nВыбор: "))
s=''
if(tp==1):
    s = '9'*85
else:
    while(s.count('666') == 0 and s.count('999') == 0):
        s = str(input("Введите строку: "))

while(s.count('666')>0 or s.count('999') > 0):
    s = s.replace('666','9')
    s = s.replace('999','6')
print(s)
