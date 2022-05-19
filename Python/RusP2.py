s = 0
ans = ""
while True:
    a = int(input("Введите число (0-конец последовательости): "))
    if(a==0):
        break
    if(a%2):
        s+=a
    else:
        ans+=str(a)+' '

print('Сумма нечетных:',s,'\nПоследовательность оставшихся:',ans)
