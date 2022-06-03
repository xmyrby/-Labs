import csv

def fmin(a,n):
    minn = 10000
    for i in range(n):
        for j in range(n):
            if(i<j):
                minn=min(minn,a[i][j])

    print('Минимальное число в треугольней матрице =',int(minn))

def c1():
    n = int(input("Введите n для матрицы: "))
    a = [[0] * n for i in range(n)]

    for i in range(n):
        for j in range(n):
            if i > j:
                a[i][j] =0
            elif i == j:
                a[i][j] = 1
            else:
                a[i][j] = i + j

    for row in a:
        for elem in row:
            print(str(elem).rjust(3), end = ' ')
        print()

    with open('8-1-Maks.csv', 'w', newline = '') as f:
        fW = csv.writer(f)
        fW.writerows(a)

    fmin(a,n)

def c2():
    a = []
    i=0
    j=0
    with open('8-1-Maks.csv', 'r') as f:
        fR = csv.reader(f, quoting = csv.QUOTE_NONNUMERIC)
        for row in fR:
            a.append(row)

        for row in a:
            for j in range(len(row)):
                print(str(int(a[i][j])).rjust(3), end = ' ')
            print()
            i+=1

    fmin(a,j+1)

while(True):
    c = int(input("1. Создать и записать матрицу в файл\n2. Прочитать матрицу из файла\nВыбор: "))
    if 1 <= c <= 2:
        break

if c == 1:
    c1()
else:
    c2()
