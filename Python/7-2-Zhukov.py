marks = {1:'Плохо',2:'Неудовлетворительно',3:'Неудовлетворительно',4:'Удовлетворительно',5:'Удовлетворительно',6:'Удовлетворительно',7:'Хорошо',8:'Хорошо',9:'Отлично', 10:'Отлично'}

mark = int(input())

if(mark>=1 and mark<=10):
    print(marks[mark])
else:
    print('Неправильный ввод данных')
