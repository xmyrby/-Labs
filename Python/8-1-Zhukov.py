n, m = map(int,input('Введите размеры n и m: ').split())
a = [[0] * m for i in range(n)]
c = [[0] * m for i in range(n)]
for i in range(n):
    for j in range(m):
        a[i][j] = int(input(f'a[{i}][{j}] = '))
        if(j<i):
            c[i][j]=a[i][j]
        else:
            c[i][j]=-a[i][j]
print('Матрица c:')
for i in range(n):
    for j in range(m):
        print(str(c[i][j]).rjust(3),end = ' ')
    print()
k = -1
while(k<0 or k>=m):
    k = int(input(f'Введите номер столбца 0-{m-1}: '))

s=0
for i in range(n):
    s+=c[i][k]

print('Сумма = ',s)
