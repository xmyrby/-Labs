x, y = map(int, input('Введите x и y (через пробел): ').split())
g = max(min(x,4),max(y,-5))/(4*min(x,y))
print(g)
