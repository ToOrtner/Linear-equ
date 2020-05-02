import numpy as np
import csv

file = 'segunda_fecha_cualitativo_WPL.csv'
out = 'penal-2da-wpl.csv'

with open(file,'r') as csvfile,open(out,'w') as outfile:
    score_reader = csv.reader(csvfile,delimiter=',',skipinitialspace=True)

    for partido in score_reader:
        resta = float(partido[4]) - float(partido[3])
        dif = abs(resta)
        if (partido[5] == 'Si'):
            outfile.write(str(dif) + '\n')
        else: outfile.write(str(-1 *dif) + '\n')
        
print ('done')    



