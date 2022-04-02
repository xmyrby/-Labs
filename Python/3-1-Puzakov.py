x, y, z = map(float,input('Введите 3 числа (x, y, z) через пробел ').split())
s = 0
if(x>=y):
    s = y
else:
    s = x

if(z>=s):
    s = z

s /= 7
print('s = ', "{:.3f}".format(s))
