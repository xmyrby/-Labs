x = float(input('Введите x: '))
e = float(input('Введите e: '))
n = 2
s = 0
polar = -1
fact = 24
numb = 1
lastx = (2*x+1)**2
while(abs(numb)>=e):
    for i in range(n*2+1,n*3 + 1):
        fact *= i

    numb = polar * lastx / (3*fact)
    s+=numb
    print('Число = ', "{:.4f}".format(numb))
    polar*=-1
    lastx *= 2*x+1
    n+=1

print('Сумма = ', "{:.4f}".format(s))
