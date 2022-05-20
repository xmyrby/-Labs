s = str(input("Введите строку: ")) + ' '
n = int(input("Введите n: "))

c = 0
d = 0

for i in range(len(s)):
    c+=1
    if(s[i]==' '):
        if(c - 1 == n):
            print(s.split(' ')[d])
        c = 0
        d+=1
    
