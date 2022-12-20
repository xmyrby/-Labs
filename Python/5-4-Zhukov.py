import math
print("_________________________________\n")
x=0
for x in [i * 0.04 for i in range(0, 26)]:
    if(math.e**(2*x**2)-3*math.e < -5.5):
        print(f"| X = {x:.3f} | Y = {(2*x**2-(3*math.e)**0.5)/(4*x**2+3*x+1):.3f} | < -5.5 |")
    else:
        print(f"| X = {x:.3f} | Y = {math.log(3*math.e-4*x**4):.3f} | >= -5.5 |")
    
print("_________________________________\n")
