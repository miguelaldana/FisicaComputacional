/** 
    Tarea 6

    Realizado por: Miguel Aldana y Jesús Rincón  
    Fecha: 29 de octubre de 2013

    Este modulo consiste en generar las condiciones iniciales para determinar las posiciones y velocidades de las particulas.

    Input:
    - x0: la posicion inicial en x del centro de la galaxia (double)
    - y0: la posicion inicial en y del centro de la galaxia (double)
    - vz: Velocidad inicial en x del centro de la galaxia (double)
    - vy: velocidad inicial en y del centro de la galaxia (double)

    Output:
    - Archivo de texto con condiciones iniciales (posicion y velocidades) de cada particula

**/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PI 3.1416


int main (int argc, char **argv){

  FILE *in;
  char filename[100] = "Condiciones_iniciales.dat";

  /**
     Codigo que asegura que hay cuatro argumentos de entrada en el problema
  **/

if(argc!= 4)
  {
    printf ("El programa necesita mas argumentos de entrada");
    exit (1);
  }

/** 
    Definición e inicializacion de las variables de entrada
**/

 double x0 = atof(argv[0]);

 double y0 = atof(argv[1]);

 double vz = atof(argv[2]);

 double vy = atof(argv[3]);

 /**
    Definicion de los punteros de posicion y velocidad

    Unidades: metros
              metros/segundo
 **/

 double *x;   // (Posición en x)

 double *y;   // (Posición en y)

 double *vx;  // (Velocidad en x)

 double *vj;  // (velocidad en y)

 /**
    Nos aseguramos de guardar espacio en la memoria para nuestros punteros
 **/

 x = malloc(sizeof(double));
 y = malloc(sizeof(double));
 vx = malloc(sizeof(double));
 vj = malloc(sizeof(double));

 /**
    Constantes de posición radial. Estas representan las órbitas de los planetas en la galaxia.

    Unidades: metros
 **/

 double kpc = 3*pow(10,16);

 double r_0 = 50*kpc;

 double r_1 = r_0/5;

 double r_2 = (2*r_0)/5;

 double r_3 = (3*r_0)/5;

 double r_4 = (4*r_0)/5;

 /**
    Definicion de constantes de gravitacion (N*m²/kg²), masas solares (kg) y masa central (kg)
 **/

 double G = 6.6674;

 double M_o = 1.9891*pow(10,30);

 double M = M_o*pow(10,12);

 /**
    Aqui se realizan los loops necesarios para determinar los valores de posicion y velocidad para las particulas a partir de la masa central
 **/

 int i;

 in = fopen(filename,"w");

 for (i=0;i<12;i++)
   {

     x[-1]=x0;
     
     x[i]=x0+ r_1*cos((2*PI*i)/12);
    
     vx[-1]=vz;

     vx[i]= vz + sqrt((G*M)/r_1)*sin((2*PI*i)/12);

     y[-1]=y0;

     y[i]= y0 + r_1*sin((2*PI*i)/5);

     vj[-1]=vy;

     vj[i]=vy + sqrt((G*M)/r_1)*cos((2*PI*i)/12);

   }
 for (i=12;i<30;i++)
   {

     x[i]= x0 + r_2*cos((2*PI*(i-12)/18));

     y[i]= y0 + r_2*sin((2*PI*(i-12)/18));

     vx[i]= vz + sqrt((G*M)/r_2)*sin((2*PI*(i-12))/18);

     vj[i]= vy + sqrt((G*M)/r_2)*cos((2*PI*(i-12))/18);

   }

 for (i=30;i<54;i++)
   {
    
     x[i]= x0 + r_3*cos((2*PI*(i-30)/24));

     y[i]= y0 + r_3*cos((2*PI*(i-30)/24));

     vx[i]= vz + sqrt((G*M)/r_3)*sin((2*PI*(i-30))/24);

     vj[i]= vy + sqrt((G*M)/r_3)*cos((2*PI*(i-30))/24);

   }
 
 for (i=54;i<84;i++)
   {

     x[i]= x0 + r_4*cos((2*PI*(i-54)/30));

     y[i]= y0 + r_4*cos((2*PI*(i-54)/30));

     vx[i]= vz + sqrt((G*M)/r_4)*sin((2*PI*(i-54))/30);

     vj[i]= vy + sqrt((G*M)/r_4)*cos((2*PI*(i-54))/30);

   }

 for (i=84;i<120;i++)
   {
    
     x[i]= x0 + r_0*cos((2*PI*(i-84)/36));

     y[i]= y0 + r_0*cos((2*PI*(i-84)/36));

     vx[i]= vz + sqrt((G*M)/r_0)*sin((2*PI*(i-84))/36);

     vj[i]= vy + sqrt((G*M)/r_0)*cos((2*PI*(i-84))/36);

   }

 fclose(in);

 return 0;

}


