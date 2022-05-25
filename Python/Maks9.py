import math
print("_________________________________\n")
x=0.1
grad = math.cos(30*180/math.pi)
while(x + 0.03 <= 0.85):
    if(grad**2 - math.e**math.sqrt(math.sin(x)) > -1.2):
        print(f"| X = {x:.3f} | Y = {grad+(math.sin(x))**0.5:.3f} | > -1.2 |")
    else:
        print(f"| X = {x:.3f} | Y = {grad**0.5/math.log(math.sin(x)**0.5):.3f} | <= -1.2 |")
    x += 0.03
    
print("_________________________________\n")
