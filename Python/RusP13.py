n, m = map(int,input('Введите размеры n и m: ').split())
a = [[0] * m for i in range(n)]
b = [[0] * m for i in range(n)]
mina = 100000
maxb = 0
maxbi = 0
for i in range(n):
    for j in range(m):
        a[i][j] = int(input(f'a[{i}][{j}] = '))
        mina = min(mina,a[i][j])

for i in range(n):
    for j in range(m):
        if(i>j):
            b[i][j] = mina / (i-j)
        elif(i<j):
            b[i][j] = i+j
        else:
            if(i == 0):
                b[i][j]=0
            else:
                b[i][j] = mina / i**2
        
print('Матрица b:')
for i in range(n):
    for j in range(m):
        print(str(b[i][j]).rjust(3),end = ' ')
    print()
k = -1
while(k<0 or k>=m):
    k = int(input(f'Введите номер столбца 0-{m-1}: '))

s=0
for i in range(n):
    s+=c[i][k]

print('Сумма = ',s)
