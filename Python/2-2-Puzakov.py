N = int(input('N = '))
M = N//10%10*1000+N//1000*10+N//100%10*100 + N%10
print(M)
