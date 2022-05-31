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
y = (x2.union(x3)).difference(x1.difference(x2).intersection(x1.union(x3)))
print('x1 =',x1)
print('x2 =',x2)
print('x3 =',x3)
print('y =',y)

for i in range(10,31,10):
    if(i in y):
        print('число',i,'принадлежит Y')
    else:
        print('число',i,'не принадлежит Y')
        
print('Мощность y =',len(y))
