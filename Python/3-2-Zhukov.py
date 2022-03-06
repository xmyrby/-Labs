n = int(input('Введите число: '))
if(abs(n)//100 == 0 and n%100>=10):
  print('Является')
else:
  print('Не является')