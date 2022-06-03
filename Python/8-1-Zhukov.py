import csv

def sumk(c,n,m):
    k = -1
    while(k<0 or k>=m):
        k = int(input(f'Введите номер столбца 0-{m-1}: '))

    s=0
    for i in range(n):
        s+=c[i][k]

    print('Сумма эл-ов k-го столбца =',s)

def c1():
    n, m = map(int, input("Введите n, m для матрицы: ").split())
    a = [[0] * m for i in range(n)]
    c = [[0] * m for i in range(n)]

    for i in range(n):
        for j in range(m):
            a[i][j]= int(input(f'a[{i}][{j}]='))
            if i < j:
                c[i][j] = a[i][j]
            else:
                c[i][j] = -a[i][j]

    for row in c:
        for elem in row:
            print(str(elem).rjust(3), end = ' ')
        print()

    with open('8-1.csv', 'w', newline = '') as f:
        fW = csv.writer(f)
        fW.writerows(a)

    sumk(c,n,m)

def c2():
    c = []
    i=0
    j=0
    with open('8-1.csv', 'r') as f:
        fR = csv.reader(f, quoting = csv.QUOTE_NONNUMERIC)
        for row in fR:
            c.append(row)

        for row in c:
            for j in range(len(row)):
                if i < j:
                    c[i][j] = int(c[i][j])
                else:
                    c[i][j] = int(-c[i][j])
            i+=1
                    
    for row in c:
        for elem in row:
            print(str(elem).rjust(3), end = ' ')
        print()

    sumk(c,i,j+1)

while(True):
    c = int(input("1. Создать и записать матрицу в файл\n2. Прочитать матрицу из файла\nВыбор: "))
    if 1 <= c <= 2:
        break

if c == 1:
    c1()
else:
    c2()
