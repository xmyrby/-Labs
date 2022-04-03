import math

x = float(input('x = '))

y = 0
if(x<=-4):
  y = abs(x-3)
elif(x<1.2):
  y=(1+x**2)**0.5-2
else:
  y=math.log(x)

print('y = ',"{:.3f}".format(y))
