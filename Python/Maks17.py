import math

x = float(input('x = '))

y = 0
if(x<-4 or x>7):
  print('Выход из области определения')
  exit(1)
elif(x<0):
  y = x/-2
elif(x<2):
  y=abs(x**2-4)**0.5*-1+2
elif(x<4):
  y=abs((x-2)**2-4)**0.5
elif(x<5):
  y=4-x
elif(x<7):
  y=x-6

print('y = ',"{:.4f}".format(y))
