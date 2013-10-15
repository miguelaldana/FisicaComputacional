import module_encefalograma as mf
import numpy as np

def main():
	"""
	Lee datos de 24 electrodos equiespaciados en el tiempo por un minuto, y suaviza los datos seleccionando las 10 frecuencias con mayor potencia  y calcula el error chi cuadrado entre los datos reales y la reconstrucción
 	"""
	#Carga los datos del encefalograma
	data = np.loadtxt("sampled+ma0844az_1-1+_data.txt")

	#Obtiene la transformada de Fourier para cada vector columna en el arreglo data
	fft_freq,fft_ampl = mf.fourierTransform(data)

	#Encuentra y selecciona las 10 potencias mayores y devuelve un arreglo con todas las amplitudes iguales aq cero excepto las de las 10 frecuencias con mayor amplitud.
	fft_ampl,fft_freq  = mf.espectro_potencias(fft_ampl,fft_freq)	

	#Reconstruye la señal con los 10 armonicos de mayor amplitud
	dataReconstruida = mf.inv_fft(fft_freq, fft_ampl)

	#Encuentra el chi cuadrado entre para cada vecor columna y lo deveuleve en un arreglo
	mf.chiCuadrado(data,dataReconstruida)
	

	

