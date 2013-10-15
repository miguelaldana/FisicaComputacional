import numpy as np
from scipy.fftpack import fft, fftfreq,ifft
import matplotlib.pyplot as plt

"""
Modulo con las funciones para procesar los datos de los 24 electrodos
Authors: Miguel Aldana, Juan Diego Bermeo
Creation date: Miercoles Oct  9 2013
"""

def fourierTransform(data):
	"""
	Carga un array de numpy [400,24] y le calcula la transformada de fourier a cada uno de los vectores columna devuelve dos arreglos de [400,24], uno para las amplitudes y otro para las frecuencias, donde el i-esimo vector columna de amplitudes le corresponde el i-esimo vector columna de frecuencias 
	Input: arreglo de numpy [400,24]
	Output: dos arreglos de numpy de [400,24], donde el primero corresponde a frecuencias, y el segundo a amplitudes. 
	"""

	n = 400

	fft_amplitudes = fft(data)/n
	
	fft_freq = fftfreq(n,1)

	half_n = np.ceil(n/2.0)

	fft_amplitudes_half = (2.0) * fft_amplitudes[:half_n]

	freq_half = freq[:half_n]

	plt.plot(freq_half, np.abs(fft_amplitudes_half))

	return fft_amplitudes_half, freq_half

def espectro_potencias(fft_amplitudes,fft_freq):

     """
     
     Esta funcion calcula el espectro de potencias de cada senal y devuelve los 10 valores mas grandes de amplitud con su respectiva frecuencia. Las otras frecuencias las hace iguales a cero

     Input:
     - fft_freq: arreglo numpy de tamano [400,24]. Frecuencias de cada senal.
     - fft_x: arreglo numpy de numeros complejos de tamano [400,24]. Amplitudes de cada senal.

     Output:
     - max_espectro_x: arreglo numpy con los 10 valores de fft_x normalizados mas grandes de tamano [400,24].
     - max_espectro_freq: arreglo numpy con los 10 valores correspondientes a valor de max_espectro_x de tamano[400,24].

     24 corresponde a las senales.
     400 corresponde a las frecuencias.

     """

     max_espectro_x = espectro_potencias_half
     for j in range(24):
	     for i in range(200): 
		     if i < 10:
			     temp = max(espectro_potencias_half[:,j])
			     if espectro_potencias_half[i,j] == temp:
				     max_espectro_x[i,j] = espectro_potencias_half[i,j]
				     espectro_potencias_half[i,j] = 0.0
		     else:
			     max_espectro_x[i,j] = 0.0 
			     max_espectro_freq[i] = 0.00

     return max_espectro_x, max_espectro_freq

def inv_fft(fft_freq, fft_amplitudes):
	"""
	Carga dos arreglos de numpy de [400,24], donde el primero corresponde a frecuencias, y el segundo a amplitudes y devuelve un arreglo de [400,24] que corresponde a la transformada inversa de fourier de la señal en frecuencia que entre por input. Es decir pasa la señal del dominio de la frecuencia al domino del tiempo
	Input: dos arreglos de numpy de [400,24], donde el primero corresponde a frecuencias, y el segundo a amplitudes. 
	Output: un arreglo de numpy de [400,24]
	"""
	invfft = fft_freq
	
	return invfft

def chiCuadrado(data,dataReconstruida)
	"""
	Carga dos arrays de numpy [400,24], uno con los datos originales del encefalograma, y otro con el encefalograma construida con las 10 frecuencias con mayor potencia, y calcula el chi cuadrado para el i-esimo vector columna de los dos arreglos, y los imprime en pantalla.
	Input: Dos arreglos de numpy de [400,24]
	Output: Nada 
	"""
	
	chi2 = empty(24)
		
	return

