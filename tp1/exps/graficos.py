import pandas as pd
import seaborn as sns
sns.set()
import sympy
import numpy as num
import matplotlib as plt
from matplotlib import pyplot as plt



df = pd.read_csv("Comparaciones.csv")

ax = df.plot('n', ['CMM', 'WP', 'Laplace'],
             marker='o', title='Comparación de tiempos')
ax.set_xlabel('Cantidad de equipos')        #tmb se puede hacer con cant partidos
ax.set_ylabel('Tiempo (microsegundos)')



plt.legend()
plt.show()
