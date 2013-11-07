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
    - Archivo de texto con condiciones iniciales (posicion y velocidades) de cada particula y el centro de la galaxia: columna_1 = x, columna_2 = y, columna_3 = v_x, columna_4 = v_y

**/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PI 3.1416


int main (int argc, char **argv){

  FILE *in;
  char filename[100] = "Condiciones_iniciales.dat";
  char filename_2[100] = "Condiciones_iniciales_2.dat";

  /**
     Codigo que asegura que hay cuatro argumentos de entrada en el problema
  **/

if(argc < 2)
  {
    printf ("El programa necesita mas argumentos de entrada");
    exit (1);
  }

/** 
    Definición e inicializacion de las variables de entrada
**/

 double x0 = atof(argv[1]);

 double y0 = atof(argv[2]);

 double vz = atof(argv[3]);

 double vy = atof(argv[4]);

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

 x = malloc(121*sizeof(double));
 y = malloc(121*sizeof(double));
 vx = malloc(121*sizeof(double));
 vj = malloc(121*sizeof(double));

 /**
    Constantes de posición radial. Estas representan las órbitas de los planetas en la galaxia.

    Unidades: metros
 **/

 double kpc = 3*pow(10,16);

 double r_0 = 50;

 double r_1 = r_0/5;

 double r_2 = (2*r_0)/5;

 double r_3 = (3*r_0)/5;

 double r_4 = (4*r_0)/5;

 double r_5 = (5*r_0)/5;

 /**
    Definicion de constantes de gravitacion (N*m²/kg²), masas solares (kg) y masa central (kg)
 **/

 double G_0 = 6.6674*pow(10,-11);

 double G = G_0*(pow(60,4)*pow(24,2)*pow(7,2)*pow(4,2)*pow(12,2)*pow(pow(10,9),2)*1.9891*pow(10,30))/(pow(3*pow(10,16),3)); //Esta es la constante de gravitación en (kpc³/M_o*MMA) donde MMA es miles de millones de años, M_o es masas solares y kpc es kiloparsecs

 double M = pow(10,12); //Masa central en masas solares

 /**
    Aqui se realizan los loops necesarios para determinar los valores de posicion y velocidad para las particulas a partir de la masa central
 **/

 int i;

 x[0]=x0;

 y[0]=y0;
 
 vx[0]=vz;
 
 vj[0]=vy;

 in = fopen(filename,"w");
 fprintf(in, "%d %f %f %f %f\n", -1, x[0], y[0], vx[0], vj[0]);

 for (i=1;i<121;i++)
   {

     if (i > 0 && i < 13)
       {
     
	 x[i] = x0 + r_1*cos((2*PI*i)/12);

	 vx[i] = vz + sqrt((G*M)/r_1)*sin((2*PI*i)/12);

	 y[i] = y0 + r_1*sin((2*PI*i)/12);

	 vj[i] = vy + sqrt((G*M)/r_1)*cos((2*PI*i)/12);

       }

     if (i > 12 && i < 31)
       {
	 x[i]= x0 + r_2*cos((2*PI*(i-12)/18));

	 y[i]= y0 + r_2*sin((2*PI*(i-12)/18));

	 vx[i]= vz + sqrt((G*M)/r_2)*sin((2*PI*(i-12))/18);

	 vj[i]= vy + sqrt((G*M)/r_2)*cos((2*PI*(i-12))/18);

       }

     if (i > 30 && i < 55)
       {
	 x[i]= x0 + r_3*cos((2*PI*(i-30)/24));

	 y[i]= y0 + r_3*sin((2*PI*(i-30)/24));

	 vx[i]= vz + sqrt((G*M)/r_3)*sin((2*PI*(i-30))/24);

	 vj[i]= vy + sqrt((G*M)/r_3)*cos((2*PI*(i-30))/24);
       }

     if (i > 54 && i < 85)
       {
	 x[i]= x0 + r_4*cos((2*PI*(i-54)/30));

	 y[i]= y0 + r_4*sin((2*PI*(i-54)/30));

	 vx[i]= vz + sqrt((G*M)/r_4)*sin((2*PI*(i-54))/18);

	 vj[i]= vy + sqrt((G*M)/r_4)*cos((2*PI*(i-54))/18);
       }

     if (i > 84 && i < 121)
       {
	 x[i]= x0 + r_5*cos((2*PI*(i-84)/36));

	 y[i]= y0 + r_5*sin((2*PI*(i-84)/36));

	 vx[i]= vz + sqrt((G*M)/r_5)*sin((2*PI*(i-84))/36);

	 vj[i]= vy + sqrt((G*M)/r_5)*cos((2*PI*(i-84))/36);
       }

     fprintf(in,"%d %f %f %f %f\n", i-1, x[i], y[i], vx[i], vj[i]);

   }

 fclose(in);

 float *x_2;   // (Posición en x)

 float *y_2;   // (Posición en y)

 float *vx_2;  // (Velocidad en x)

 float *vj_2;  // (velocidad en y)

 /**
    Nos aseguramos de guardar espacio en la memoria para nuestros punteros
 **/

 x_2 = malloc(121*sizeof(float));
 y_2 = malloc(121*sizeof(float));
 vx_2 = malloc(121*sizeof(float));
 vj_2 = malloc(121*sizeof(float));

 x_2[0] = x0 + 150;
 
 y_2[0] = y0 + 200;
 
 vx_2[0] = 0.0;
 
 vj_2[0] = (-100)*(1000/(3*pow(10,16)))*(pow(60,4)*pow(24,2)*pow(7,2)*pow(4,2)*pow(12,2)*pow(pow(10,9),2));

 in = fopen(filename_2,"w");
 fprintf(in, "%d %f %f %f %f\n", -1, x_2[0], y_2[0], vx_2[0], vj_2[0]);

 for (i = 1; i < 121; i++)
   {

     if (i > 0 && i < 13)
       {
     
	 x_2[i] = x_2[0] + r_1*cos((2*PI*i)/12);

	 vx_2[i] = vx_2[0] + sqrt((G*M)/r_1)*sin((2*PI*i)/12);

	 y_2[i] = y_2[0] + r_1*sin((2*PI*i)/12);

	 vj_2[i] = vj_2[0] + sqrt((G*M)/r_1)*cos((2*PI*i)/12);

       }

     if (i > 12 && i < 31)
       {
	 x_2[i]= x_2[0] + r_2*cos((2*PI*(i-12)/18));

	 y_2[i]= y_2[0] + r_2*sin((2*PI*(i-12)/18));

	 vx_2[i]= vx_2[0] + sqrt((G*M)/r_2)*sin((2*PI*(i-12))/18);

	 vj_2[i]= vj_2[0] + sqrt((G*M)/r_2)*cos((2*PI*(i-12))/18);

       }

     if (i > 30 && i < 55)
       {
	 x_2[i]= x_2[0] + r_3*cos((2*PI*(i-30)/24));

	 y_2[i]= y_2[0] + r_3*sin((2*PI*(i-30)/24));

	 vx_2[i]= vx_2[0] + sqrt((G*M)/r_3)*sin((2*PI*(i-30))/24);

	 vj_2[i]= vj_2[0] + sqrt((G*M)/r_3)*cos((2*PI*(i-30))/24);
       }

     if (i > 54 && i < 85)
       {
	 x_2[i]= x_2[0] + r_4*cos((2*PI*(i-54)/30));

	 y_2[i]= y_2[0] + r_4*sin((2*PI*(i-54)/30));

	 vx_2[i]= vx_2[0] + sqrt((G*M)/r_4)*sin((2*PI*(i-54))/18);

	 vj_2[i]= vj_2[0] + sqrt((G*M)/r_4)*cos((2*PI*(i-54))/18);
       }

     if (i > 84 && i < 121)
       {
	 x_2[i]= x_2[0] + r_5*cos((2*PI*(i-84)/36));

	 y_2[i]= y_2[0] + r_5*sin((2*PI*(i-84)/36));

	 vx_2[i]= vx_2[0] + sqrt((G*M)/r_5)*sin((2*PI*(i-84))/36);

	 vj_2[i]= vj_2[0] + sqrt((G*M)/r_5)*cos((2*PI*(i-84))/36);
       }

     fprintf(in,"%d %f %f %f %f\n", i-1, x_2[i], y_2[i], vx_2[i], vj_2[i]);

   }

 fclose(in);


 return 0;

}


