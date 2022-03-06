import math

x = float(input('x = '))

y = 0
if(x<-5 or x>9):
  print('Выход из области определения')
  exit(1)
elif(x<-1):
  y = abs((x+3)**2-4)**0.5
elif(x<0):
  y=-2*x-2
elif(x<2):
  y=x-2
elif(x<6):
  y=(x-2)**0.5
elif(x<9):
  y=8-x
else:
  print('Выход из области определения')
  exit(1)

print('y = ',"{:.4f}".format(y))
