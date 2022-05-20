N = int(input("Введите число: "))

while(N<=0):
    N = int(input("Введите число: "))
K=0

i = 1
while(N>0):
    if(N%10%2):
        K+=N%10*i
        i*=10
    N//=10
if(i == 1):
    print("Цифр кратных 2 нет")
else:
    print(K)
