minn = 1000
a = int(input("Введите число: "))
while(a>0):
    c = a%10
    if(c%2==0 and c<minn):
        minn=c
    a//=10
else:
    if(min!=1000):
        print(minn)
    else:
        print("Нет чётных цифр")
