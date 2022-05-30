f = open('8-2-8.txt', 'r')
s = f.read()
count = 0
maxc = 0

for i in range(1,len(s)):
    if(int(s[i])+int(s[i-1]) >= 10):
        count+=1
    else:
        maxc = max(maxc,count+1)
        count = 0
print('Максимальная длина = ',maxc)
