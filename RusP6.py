A, B = map(int, input("Введите A и B (через пробел): ").split())
fact = 1
for i in range(1,B+1):
    fact*=i
if(fact == A):
    print("Является")
else:
    print("Не является")
