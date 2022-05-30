f = open('8-2-7.txt', 'r')
s = f.read()
sub = 'BOSS'
pos = s.find(sub)

k = 0
while pos != -1:
    if s[pos-1] != 'J' and s[pos+4] != 'J':
        k += 1
    pos = s.find(sub, pos + 1)
print(k)
