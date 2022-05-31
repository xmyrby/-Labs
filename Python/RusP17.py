import random

def getSize():
    size = 0
    while(size<=0 or size>1000):
        size = int(input('Введите мощность множества: '))
    return size

s = getSize()
x1 = {random.randrange(1,1001) for i in range(s)}
s = getSize()
x2 = {random.randrange(1,1001) for i in range(s)}
s = getSize()
x3 = {random.randrange(1,1001) for i in range(s)}
y = (x2.union(x3)).difference(x1.union(x2).intersection(x1.union(x3)))
print('x1 =',x1)
print('x2 =',x2)
print('x3 =',x3)
print('y =',y)

y1 = {i for i in range(13,1001)}
y1 = y1.intersection(y)
print('y1 =',y1)
print('Мощность y1 =',len(y1э))
