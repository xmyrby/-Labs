a = int(input("Введите число: "))
b=a
suma = 0

while(b>0):
    suma += b%10
    b//=100

print(a-suma)
