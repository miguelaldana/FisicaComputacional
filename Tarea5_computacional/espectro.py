def espectro_potencias(fft_x,fft_freq):

     """
     
     Esta función calcula el espectro de potencias de cada señal y devuelve los 10 valores màs grandes de amplitud con su respectiva frecuencia.

     Input:
     - fft_freq: arreglo numpy de tamaño [400,24]. Frecuencias de cada señal.
     - fft_x: arreglo numpy de números complejos de tamaño [400,24]. Amplitudes de cada señal.

     Output:
     - max_espectro_x: arreglo numpy con los 10 valores de fft_x normalizados más grandes de tamaño [400,24].
     - max_espectro_freq: arreglo numpy con los 10 valores correspondientes a valor de max_espectro_x de tamaño[400,24].

     24 corresponde a las señales.
     400 corresponde a las frecuencias.

     """

     max_espectro_x = fft_x;
     max_espectro_freq = fft_freq;

     return max_espectro_x, max_espectro_freq
