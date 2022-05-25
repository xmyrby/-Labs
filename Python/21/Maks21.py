tables = []
dishes = []

class Table:
    name = ''
    dishesId = []

    def printDishes(self):
        for i in range(len(self.dishesId)):
            print(i,':',dishes[self.dishesId[i]])
        print(' ___________________________')
    def printDish(self, ind):
        print(dishes[self.dishesId[ind]])

def save():
    f = open('tables.txt','w', encoding="utf-8")
    f.write(str(len(tables)) + '\n')
    for i in range(len(tables)):
        f.write(tables[i].name + str(len(tables[i].dishesId)) + '\n')
        for j in range(len(tables[i].dishesId)):
            f.write(str(tables[i].dishesId[j]) + '\n')
    f.close()

f = open('dishes.txt','r', encoding="utf-8")

for i in range(int(f.readline())):
    dishes.append(f.readline())
    
f.close()
f = open('tables.txt','r', encoding="utf-8")

for i in range(int(f.readline())):
    table = Table()
    table.name = f.readline()
    table.dishesId = []
    for j in range(int(f.readline())):
        table.dishesId.append(int(f.readline()))
    tables.append(table)
f.close()

cmd = ''
while cmd != 'Выйти':
    print('Список команд:\nВывести - вывод всех блюд на всех столах\nВывести <id> - вывод блюда стола <id>\nБлюдо <id1> <id2> - вывести блюдо <id2> стоящее на столе <id1>\nБлюда - список всех блюд\nДобавить <id1> <id2> - добавить блюдов <id1> на стол <id2>\nВыйти - выход')
    cmd = str(input('Ввод: '))
    if(cmd == 'Вывести'):
        for i in range(len(tables)):
            print(i,':',tables[i].name,'___________________________\nБлюда:')
            tables[i].printDishes()
    elif(cmd.split()[0] == 'Вывести'):
        ind = int(cmd.split()[1])
        print(tables[ind].name,'Блюда:')
        tables[ind].printDishes()
    elif(cmd.split()[0] == 'Блюдо'):
        ind = int(cmd.split()[1])
        tables[ind].printDish(int(cmd.split()[2]))
    elif(cmd == 'Блюда'):
        for i in range(len(dishes)):
            print(i,':',dishes[i],end='')
        print()
    elif(cmd.split()[0] == 'Добавить'):
        dishInd = int(cmd.split()[1])
        ind = int(cmd.split()[2])
        tables[ind].dishesId.append(dishInd)
        print('Блюдо',dishes[dishInd],'добавлено на',tables[ind].name)
    elif(cmd == 'Выйти'):
        print('Сохранение')
    else:
        print('Неправильная команда')
else:
    save()
