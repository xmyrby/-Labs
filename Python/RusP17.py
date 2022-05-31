import random

def getSize():
    size = 0
    while(size<=0 or size>1000):
        size = int(input('Введите мощность множества: '))
    return size

s = getSize()
x1 = {random.randrange(1,1001) for i in range(s)}
print(x1)
s = getSize()
x2 = {random.randrange(1,1001) for i in range(s)}
print(x2)

y1 = {i*3 for i in range(1,334)}
y1=y1.intersection(x1)

y2 = {i*5 for i in range(1,201)}
y2 = y2.intersection(x2)

y3 = y2.intersection(y1)

if(y3 == set()):
    print('Пустое множество')
else:
    print('Полученное множество:\n',y3,'\nМощность',len(y3))
