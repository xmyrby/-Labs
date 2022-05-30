import csv
data =[['1','2','3','4','5'],['6','7','8','9','10']]
with open('x.csv','w',encoding='UTF8') as f:
    writer = csv.writer(f)

    writer.writerow(data)
