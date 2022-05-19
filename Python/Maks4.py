import math
print("_________________________________\n")
x=0.1
while(x + 0.03 <= 0.85):
    if(math.cos(30*math.pi/180)**2 - math.e**(math.sin(x)**0.5) > -1.2):
        print(f"| X = {x:.3f} | Y = {math.cos(30*math.pi/180) + math.sin(x)**0.5:.3f} | > -1.2 |")
    else:
        print(f"| X = {x:.3f} | Y = {math.cos(30*math.pi/180)**0.5/math.log(math.sin(x)**0.5):.3f} | <= -1.2 |")
    x += 0.03
    
print("_________________________________\n")
