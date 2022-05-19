import math
x=3.4
while(x + 0.06 <= 4.8):
    y=0
    flag = math.e**(2*x**0.5-1.2*math.e)
    if(flag>2.5):
        y = 100*(2*x**0.5-1.2*math.e)/(4*x+x**2)
    else:
        y = math.log(1.2*math.e-(2*x**0.5)**0.5)
    print("{:.4f}".format(x),":","{:.4f}".format(y))
    x += 0.06
