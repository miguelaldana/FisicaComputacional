import matplotlib as plt

"""
   Modulo que realiza las graficas de posiciones para las particulas para observar la evolucion de estas en el tiempo.

   Input:
   - Archivo_1: archivo con condiciones iniciales de posicion y velocidad de las particulas
   - Archivo_2 = posiciones y velocidades de las particulas en los proximos 5 mil millones de anos.
   - Archivo_3 = posiciones y velocidades de las particulas en los proximos 10 mil millones de anos.
   - Archivo_4 = posiciones y velocidades de las particulas en los proximos 15 mil millones de anos.
   - Archivo_5 = posiciones y velocidades de las particulas en los proximos 20 mil millones de anos.
   - Archivo_6 = posiciones y velocidades de las particulas en los proximos 25 mil millones de anos.

   Output:
   - Graficas correspondientes a cada archivo
"""

def plotting(x,y):
    plt.plot(x,y)
