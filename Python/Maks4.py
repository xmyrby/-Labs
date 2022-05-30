import math
print("_________________________________\n")
for x in (z / 100 for z in range(10,86,3)):
    if(math.cos(30*math.pi/180)**2 - math.e**(math.sin(x)**0.5) > -1.2):
        print(f"| X = {x:.2f} | Y = {math.cos(30*math.pi/180) + math.sin(x)**0.5:.3f} | > -1.2 |")
    else:
        print(f"| X = {x:.2f} | Y = {math.cos(30*math.pi/180)**0.5/math.log(math.sin(x)**0.5):.3f} | <= -1.2 |")
    
print("_________________________________\n")
