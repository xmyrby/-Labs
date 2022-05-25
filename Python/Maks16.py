import math

x = float(input('x = '))

y = 0
if(x<-1):
  y = 1 - math.abs(math.sin(3*x))
elif(x<=3):
  y=3-math.e**(2*x)
else:
  y=x/(1+x**2)**0.5

print('y = ',"{:.3f}".format(y))
