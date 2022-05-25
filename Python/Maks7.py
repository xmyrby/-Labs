a = int(input("Введите A (A>3): "))
while(a<=3):
    a = int(input("Введите A (A>3): "))
b=1
s=0
while(s+b<a):
    s+=b
    b+=1
print(b-1)
