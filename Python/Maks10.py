a = str(int(input('Введите число: ')))
maxx = 0
for i in range (1, 10):
    if(a.count(str(i)) > 0):
        maxx = i
print(maxx)
