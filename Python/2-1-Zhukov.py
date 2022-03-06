N = int(input('N = '))
bite, bit = divmod(N,8)
kbite, bite = divmod(bite,1024)
print(kbite,':',bite,':',bit)