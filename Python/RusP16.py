days = {1:'Понедельник',2:'Вторник',3:'Среда',4:'Четверг',5:'Пятница',6:'Суббота',7:'Воскресенье'}

day = int(input('Введите количество дней с начала года: '))

print(days[day%7+1])
