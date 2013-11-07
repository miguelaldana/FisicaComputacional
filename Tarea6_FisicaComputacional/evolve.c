/** 
    Tarea 6

    Realizado por: Miguel Aldana y Jesús Rincón  
    Fecha: 29 de octubre de 2013

    Este modulo consiste en utilizar el metodo de Runge-Kutta de cuarto orden para poder determinar la evolucion de las posiciones y velocidades de las particulas en la galaxia.

    Input:
    - Archivo con condiciones iniciales de posicion y velocidad de las particulas y en centro de la galaxia: columna_1 = x, columna_2 = y, columna_3 = v_x, columna_4 = vy

    Output:
    - Archivo_1 = posiciones y velocidades de las particulas en los proximos 1 mil millones de anos.
    - Archivo_2 = posiciones y velocidades de las particulas en los proximos 2 mil millones de anos.
    - Archivo_3 = posiciones y velocidades de las particulas en los proximos 3 mil millones de anos.
    - Archivo_4 = posiciones y velocidades de las particulas en los proximos 4 mil millones de anos.
    - Archivo_5 = posiciones y velocidades de las particulas en los proximos 5 mil millones de anos.
**/

#include <stdio.h>
#include <math.h>
#include <stdlib.h> 

int main (int argc,char **argv){

  char evolucion_1[100] = "Datos_evolucion_1.dat";
  char evolucion_2[100] = "Datos_evolucion_2.dat";
  char evolucion_3[100] = "Datos_evolucion_3.dat";
  char evolucion_4[100] = "Datos_evolucion_4.dat";
  char evolucion_5[100] = "Datos_evolucion_5.dat";

// estipulación de condiciones iniciales. Estas son el documento creado en condiciones iniciales

  if( argc < 2)
    {
      printf("Se necesita un segundo documento para ejecutar este programa\n");
      exit(1);
    }

  float h = 0.001;

  int n_points = (6.0+h)/h;

  int n_lines = count_lines(argv[1]);

  int i,m,j;

  FILE *in;
  FILE *in_1;
  FILE *in_2;
  FILE *in_3;
  FILE *in_4;
  FILE *in_5;

// definición de los vectores condiciones iniciales. Con esto se hace un scan que obtiene las variables del problema anterior y las convierte en xi (float) y yi(float), y las velocidades iniciales vix(float) y viy(float).

  float *t;
  int *ID;
  float *x;
  float *y;
  float *vx;
  float *vy;
  float **ev_x;
  float **ev_y;
  float **ev_vx;
  float **ev_vy;
  
  t = malloc(n_points * sizeof(float));
  ID = malloc(n_lines * sizeof(int));
  x = malloc(n_lines * sizeof(float));
  y = malloc(n_lines * sizeof(float));
  vx = malloc(n_lines * sizeof(float));
  vy = malloc(n_lines * sizeof(float));

  /**
     Obtencion de los valores iniciales.
  **/

  int k;

  in = fopen(argv[1], "r");
  
  for(k = 0; k < n_lines; k++)
    {
      fscanf(in,"%d %f %f %f %f", &ID[k],&x[k],&y[k],&vx[k],&vy[k]);
    }  
  
  fclose(in);
  
  /**
     Creamos los punteros dobles donde guardaresmo las evoluciones de x, y, vx y vy. La columna cero de cada puntero doble, correspondera a los valores iniciales que entraron como parametro.
  **/
  
  //Para x
  
  ev_x = (float**) malloc(n_lines*sizeof(float*));  
  for (i = 0; i < n_lines; i++)  
    {
      ev_x[i] = (float*) malloc(n_points*sizeof(float));    
    }
  
  for(j = 0; j < n_points; j++)
    {
      for (i = 0; i < n_lines; i++)
	{
	  if(j == 0)
	    {
	      ev_x[i][0] = x[i];
	    }
	  else
	    {
	      ev_x[i][j] = 0.0;
	    }
	}
    }
  
  //Para y
  
  ev_y = (float**) malloc(n_lines*sizeof(float*));  
  for (i = 0; i < n_lines; i++)  
    {
      ev_y[i] = (float*) malloc(n_points*sizeof(float));    
    }
  
  for(j = 0; j < n_points; j++)
    {
      for (i = 0; i < n_lines; i++)
	{
	  if(j == 0)
	    {
	      ev_y[i][0] = y[i];
	    }
	  else
	    {
	      ev_y[i][j] =  0.0;
	    }
	}
    }

  //Para vx
  
  ev_vx = (float**) malloc(n_lines*sizeof(float*));  
  for (i = 0; i < n_lines; i++)  
    {
      ev_vx[i] = (float*) malloc(n_points*sizeof(float));    
    }
  
  for(j = 0; j < n_points; j++)
    {
      for (i = 0; i < n_lines; i++)
	{
	  if(j == 0)
	    {
	      ev_vx[i][0] = vx[i];
	    }
	  else
	    {
	      ev_vx[i][j] = 0.0;
	    }
	}
    }

  //Para vy
  
  ev_vy = (float**) malloc(n_lines*sizeof(float*));  
  for (i = 0; i < n_lines; i++)  
    {
      ev_vy[i] = (float*) malloc(n_points*sizeof(float));    
    }
  
  for (j = 0; j < n_points; j++)
    {
      for (i = 0; i < n_lines; i++)
	{
	  if (j == 0)
	    {
	      ev_vy[i][j] = vy[i];
	    }
	  else
	    {
	      ev_vy[i][j] = 0.0;
	    }
	} 
    }
  
  /**
     Definicion de constantes de gravitacion (N*m²/kg²), masas solares (kg) y masa central (kg)
  **/
  
  double G_0 = 6.6674*pow(10,-11);
  
  double G = G_0*(pow(60,4)*pow(24,2)*pow(7,2)*pow(4,2)*pow(12,2)*pow(pow(10,9),2)*1.9891*pow(10,30))/(pow(3*pow(10,16),3)); //Esta es la constante de gravitación en (kpc³/M_o*MMA) donde MMA es miles de millones de años, M_o es masas solares y kpc es kiloparsecs
  
  double M = pow(10,12); //Masa central en masas solares
  
  /**
     Obtencion de los valores iniciales de la masa central.
  **/

 float x_0;
 float y_0; 
 float vx_0;
 float vy_0;
 
 /**
    Metodo Runge-Kutta de cuarto orden para determinar la evolucion de la galaxia en los proximos miles de millones de anos.

    Lo primero es definir las funciones que contendran la primera y segunda derivada de r con respecto al tiempo 
 **/
 
 float func_prime_1x(float t, float x, float vx,float y, float vy, float x_0, float y_0)
 {
   return vx;
 }

 float func_prime_1y(float t, float x, float vx, float y, float vy, float x_0, float y_0)
 {
   return vy;
 }
 
 float func_prime_2x(float t, float x, float vx, float y, float vy, float x_0, float y_0)
 {
   return (-1)*(G*M)*(x-x_0)/(pow((x-x_0)*(x-x_0) + (y-y_0)*(y-y_0),(3.0/2.0))+0.00000000001);
 }
 
 //x'' = G*M*(x - xm)/ ( (x-xm)^2 + (y - ym)^2 )^(3.2)

 float func_prime_2y(float t, float x, float vx, float y, float vy, float x_0, float y_0)
 {
   return (-1)*(G*M)*(y-y_0)/(pow((x-x_0)*(x-x_0) + (y-y_0)*(y-y_0),(3.0/2.0))+0.00000000001);
 }
 
 /**
   Realización del método
   
   h y delta_t están en miles de millones de años
**/
 
 t[0] = 0;
 
 in_1 = fopen(evolucion_1, "w");
 in_2 = fopen(evolucion_2, "w");
 in_3 = fopen(evolucion_3, "w");
 in_4 = fopen(evolucion_4, "w");
 in_5 = fopen(evolucion_5, "w");
 
 for (j = 1; j < n_points; j++)
   {

     ev_x[0][j-1] = ev_vx[0][j-1]*h;

     ev_y[0][j-1] = ev_vy[0][j-1]*h;
     
     for (i = 0; i < n_lines; i++)
       {
	 float kx_1 = func_prime_1x(t[j-1],ev_x[i][j-1],ev_vx[i][j-1],ev_y[i][j-1],ev_vy[i][j-1], ev_x[0][j-1], ev_y[0][j-1]);
	 float ky_1 = func_prime_1y(t[j-1],ev_x[i][j-1],ev_vx[i][j-1],ev_y[i][j-1],ev_vy[i][j-1], ev_x[0][j-1], ev_y[0][j-1]);
	 float k2x_1 = func_prime_2x(t[j-1],ev_x[i][j-1],ev_vx[i][j-1],ev_y[i][j-1],ev_vy[i][j-1], ev_x[0][j-1], ev_y[0][j-1]); 
	 float k2y_1 = func_prime_2y(t[j-1],ev_x[i][j-1],ev_vx[i][j-1],ev_y[i][j-1],ev_vy[i][j-1], ev_x[0][j-1], ev_y[0][j-1]);
	 
	 // primera línea 
	 
	 int t1 = t[j-1] + (h/2.0);
	 float vx1 = ev_vx[i][j-1] + (h/2.0)*k2x_1;
	 float x1 = ev_x[i][j-1] + (h/2.0)*kx_1;
	 float vy1 = ev_vy[i][j-1] + (h/2.0)*k2y_1;
	 float y1 = ev_y[i][j-1] + (h/2.0)*ky_1;

	 float kx_2 = func_prime_1x(t1,x1,vx1,y1,vy1, ev_x[0][j-1], ev_y[0][j-1]);
	 float ky_2 = func_prime_1y(t1,x1,vx1,y1,vy1, ev_x[0][j-1], ev_y[0][j-1]);
	 float k2x_2 = func_prime_2x(t1,x1,vx1,y1,vy1, ev_x[0][j-1], ev_y[0][j-1]); 
	 float k2y_2 = func_prime_2y(t1,x1,vx1,y1,vy1, ev_x[0][j-1], ev_y[0][j-1]);
	 
	 // segunda línea 
	 
	 int t2 = t[j-1] + (h/2.0);	
	 float vx2 = ev_vx[i][j-1] + (h/2.0)*k2x_2;
	 float x2 = ev_x[i][j-1] + (h/2.0)*kx_2;
	 float vy2 = ev_vy[i][j-1] + (h/2.0)*k2y_2;
	 float y2 = ev_y[i][j-1] + (h/2.0)*ky_2;
      
	 float kx_3 = func_prime_1x(t2,x2,vx2,y2,vy2, ev_x[0][j-1], ev_y[0][j-1]);
	 float ky_3 = func_prime_1y(t2,x2,vx2,y2,vy2, ev_x[0][j-1], ev_y[0][j-1]);
	 float k2x_3 = func_prime_2x(t2,x2,vx2,y2,vy2, ev_x[0][j-1], ev_y[0][j-1]);
	 float k2y_3 = func_prime_2y(t2,x2,vx2,y2,vy2, ev_x[0][j-1], ev_y[0][j-1]);
	 
	 // tercera línea 
	 
	 int t3 = t[j-1] + (h/2.0);		
	 float vx3 = ev_vx[i][j-1] + (h/2.0)*k2x_3;
	 float x3 = ev_x[i][j-1] + (h/2.0)*kx_3;
	 float vy3 = ev_vy[i][j-1] + (h/2.0)*k2y_3;
	 float y3 = ev_y[i][j-1] + (h/2.0)*ky_3;
	
	 float kx_4 = func_prime_1x(t3,x3,vx3,y3,vy3, ev_x[0][j-1], ev_y[0][j-1]);
	 float ky_4 = func_prime_1y(t3,x3,vx3,y3,vy3, ev_x[0][j-1], ev_y[0][j-1]);
	 float k2x_4 = func_prime_2x(t3,x3,vx3,y3,vy3, ev_x[0][j-1], ev_y[0][j-1]);
	 float k2y_4 = func_prime_2y(t3,x3,vx3,y3,vy3, ev_x[0][j-1], ev_y[0][j-1]);
	 
	 // cuarta línea promedios de pendientes
	 
	 float average_x = (1.0/6.0)*(kx_1 + 2.0*kx_2 + 2.0*kx_3 + kx_4);
	 float average_y = (1.0/6.0)*(ky_1 + 2.0*ky_2 + 2.0*ky_3 + ky_4); 
	 float average_vx = (1.0/6.0)*(k2x_1 + 2.0*k2x_2 + 2.0*k2x_3 + k2x_4);
	 float average_vy = (1.0/6.0)*(k2y_1 + 2.0*k2y_2 + 2.0*k2y_3 + k2y_4);
	 
	 t[j] = t[j-1] + h;
	 
	 ev_vx[i][j] = ev_vx[i][j-1] + h*average_vx;
	 
	 ev_x[i][j] = ev_x[i][j-1] + h*average_x;
	 
	 ev_vy[i][j] = ev_vy[i][j-1] + h*average_vy;
	 
	 ev_y[i][j] = ev_y[i][j-1] + h*average_y;
       }
   }
 
 for (i = 0; i < n_lines; i++)
   {
     fprintf(in_1,"%f %f %f %f\n", ev_x[i][1000], ev_y[i][1000], ev_vx[i][1000], ev_vy[i][1000]);
   }
 
 for (i = 0; i < n_lines; i++)
   {
     fprintf(in_2,"%f %f %f %f\n", ev_x[i][2000], ev_y[i][2000], ev_vx[i][2000], ev_vy[i][2000]);
   }

 for (i = 0; i < n_lines; i++)
   {
     fprintf(in_3,"%f %f %f %f\n", ev_x[i][3000], ev_y[i][3000], ev_vx[i][3000], ev_vy[i][3000]);
   }
 
 for (i = 0; i < n_lines; i++)
   {
     fprintf(in_4,"%f %f %f %f\n", ev_x[i][4000], ev_y[i][4000], ev_vx[i][4000], ev_vy[i][4000]);
   }

 for (i = 0; i < n_lines; i++)
   {
     fprintf(in_5,"%f %f %f %f\n", ev_x[i][5000], ev_y[i][5000], ev_vx[i][5000], ev_vy[i][5000]);
   }


 fclose(in_1);
 fclose(in_2);
 fclose(in_3);
 fclose(in_4);
 fclose(in_5);
 
 return 0; 
}

int count_lines(char *filename){
  FILE *in;
  int n_lines;
  int c;
  if(!(in=fopen(filename, "r"))){
    printf("problem opening file %s\n", filename);
    exit(1);
  }

  n_lines = 0;
  do{
    c = fgetc(in);
    if(c=='\n'){
      n_lines++;
    }
  }while(c!=EOF);
  
  fclose(in);
  return n_lines;
}
