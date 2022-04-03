import math

x = float(input('x = '))

y = 0

if(x<-6 or x>10):
    print('Выход из области определения')
    exit(1)
elif(x<-4):
    y = -1
elif(x<-2):
    y = x+3
elif(x<4):
    y = -0.5*x
elif(x<6):
    y = -2
elif(x<=10):
    y = abs((x-8)**2-4)**0.5-2

print('y = ',"{:.4f}".format(y))
