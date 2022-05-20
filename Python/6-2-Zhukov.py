tp = 0

while(tp < 1 or tp > 2):
    tp = int(input("Выберите тип ввода\n1 - 1000 цифр 8\n2 - Ручной ввод\nВыбор: "))
s=''
if(tp==1):
    s = '8'*1000
else:
    while(s.count('999') == 0 and s.count('888') == 0):
        s = str(input("Введите строку: "))

while(s.count('999')>0 or s.count('888') > 0):
    s = s.replace('888','9')
    s = s.replace('999','8')
print(s)
