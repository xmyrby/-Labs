A = int(input("Введите A (A > 3): "))
s = 0
for B in range(A//2):
    s+=B
    if(s+B+1 >= A):
        break

print("B =",B)
    
