N = int(input("Введите число: "))

while(N<=0):
    N = int(input("Введите число: "))

s=str(N)

minimum, maximum = 9, 0
 
while N:
    N, n = divmod(N, 10)
    minimum = min(minimum, n)
    maximum = max(maximum, n)

s = s.replace(str(minimum),'m')
s = s.replace(str(maximum),str(minimum))
s = s.replace('m',str(maximum))

print(s)
