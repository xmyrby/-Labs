a = 0

while(a<=0):
    a = int(input("Введите a: "))

count = 0
s = 0
ans = 0

while(a>0):
    s+=(a%10)**2
    a//=10
    count+=1

print(s**0.5/count)
