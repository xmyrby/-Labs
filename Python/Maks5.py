a = int(input("Введите число: "))
maxn = 0
while(a<=0):
    a = int(input("Введите число: "))
while(a>0):
    maxn = max(maxn,a%10)
    a //= 10

print("Максимальная цифра: ",maxn)
