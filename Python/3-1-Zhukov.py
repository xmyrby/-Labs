a, b, c = map(float,input('Введите 3 числа (a,b,c) через пробел ').split())

l1 = l2 = 0

if(a<b):
  l1 = a
else:
  l1 = b
if(l1>b*a-4):
  l1 = b*a-4

if(a-b>c-a):
  l2 = a-b
else:
  l2 = c-a

l=l1/l2

print(l)