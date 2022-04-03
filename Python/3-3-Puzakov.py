import math

x = float(input('x = '))

y = 0
if(x<=-2):
  y = 1 - 2*(1+x)**0.5
elif(x<=4):
  y=6 - math.e**x
else:
  y=math.sin(2*x)

print('y = ',"{:.3f}".format(y))
