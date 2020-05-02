import numpy as np
import csv

file = 'segunda_fecha_cualitativo_WPL.csv'
out = 'penal-2da-wpl.csv'

with open(file,'r') as csvfile,open(out,'w') as outfile:
    score_reader = csv.reader(csvfile,delimiter=',',skipinitialspace=True)

    for partido in score_reader:
        dif = abs(patido[4] - partido[5])
        if (partido[6] == 'Si'):
        out.write(dif)
        elif :
            out.write(-1 *dif)
        endif
        
    



