funt = float(input("Введите массу в фунтах: "))

kg = funt/2.205

print(funt," фунтов = ","{:.0f}".format(kg//1)," кг ","{:.0f}".format(kg%1*1000)," грамм")
