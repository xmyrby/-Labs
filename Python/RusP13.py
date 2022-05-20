s = str(input("Введите строку: "))+'.'

c = 0
m = 0

for i in range(len(s)):
    if(s[i] == ' '):
        c+=1
    else:
        m=max(c,m)
        c=0
print('Максимальное кол-во подряд идущих пробелов =',m)
    
