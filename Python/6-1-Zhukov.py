N = int(input("Введите число: "))

while(N<=0):
    N = int(input("Введите число: "))
s=str(N)
for i in range(2,10,2):
    s = s.replace(str(i),'')
print('Число :',s)
