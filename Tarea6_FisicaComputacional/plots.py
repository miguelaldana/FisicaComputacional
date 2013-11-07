#!/usr/bin/python

import matplotlib.pyplot as plt
import numpy as np
from matplotlib import pyplot

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

data_0 = np.loadtxt("Condiciones_iniciales.dat")

pyplot.plot(data_0[:,1],data_0[:,2], 'ko')

pyplot.show()

data_0_2 = np.loadtxt("Condiciones_iniciales_2.dat")

pyplot.plot(data_0_2[:,1],data_0_2[:,2], 'ko')

pyplot.show()

data_0_3 = np.loadtxt("Condiciones_iniciales_3.dat")

pyplot.plot(data_0_3[:,1],data_0_3[:,2], 'ko')

pyplot.show()

data_1 = np.loadtxt("Datos_evolucion_1.dat")

pyplot.plot(data_1[:,0],data_1[:,1], 'ko')

pyplot.show()

data_2 = np.loadtxt("Datos_evolucion_2.dat")

pyplot.plot(data_2[:,0],data_2[:,1], 'ko')

pyplot.show()

data_3 = np.loadtxt("Datos_evolucion_3.dat")

pyplot.plot(data_3[:,0],data_3[:,1], 'ko')

pyplot.show()

data_4 = np.loadtxt("Datos_evolucion_4.dat")

pyplot.plot(data_4[:,0],data_4[:,1], 'ko')

pyplot.show()

data_5 = np.loadtxt("Datos_evolucion_5.dat")

pyplot.plot(data_5[:,0],data_5[:,1], 'ko')

pyplot.show()
