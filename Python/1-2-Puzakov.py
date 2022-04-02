N,K = map(float,input('Введите 2 числа (N,K) через пробел ').split())
D = N**3/7*K + (K*(N-K))**2/5**0.5
print('D = ', "{:.3f}".format(D))
