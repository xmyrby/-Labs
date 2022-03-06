U,V,X = map(float,input('Введите 3 числа (U,V,X) через пробел ').split())
T = (U**2 - V)/((V+U**2)**2*X**2)+1/(U*V)**0.5
print('T = ', "{:.3f}".format(T))