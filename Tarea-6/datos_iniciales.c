// Tarea 6
// Realizado por Miguel Aldana y Jes�s Rinc�n  
// Fecha 22 de octubre de 2013

// Definir el main en la funci�n. Este main posee 4 atributos de entrada.
// X0: el punto inicial en x de la part�cula (double)
// y0: el punto inicial en y de la part�cula (double)
// vz: Velocidad inicial en x (double)
// vy: velocidad inicial en y (double)

#include <math.h>

#include <stdio.h>

#include <stdlib.h>

#define pi 3.1416


int main void (int argc, char **argv){

// C�digo que asegura que hay cuatro argumentos de entrada en el problema

if(argv!= 4)
{

	printf "El programa necesita m�s argumentos de entrada";
	exit (1);
	}
// definici�n de las variables de entrada

double x0;

double y0;

double vz;

double vy;

// inicializaci�n de las constantes

x0=atof(argv[1]);

y0=atof(argv[2]);

vz=atof(argv[3]);

vy=atof(argv[4]);;

// definici�n de los vectores posici�n y velocidad

double *x;// (Posici�n en x)

double *y; // (Posici�n en y)

double *vx; // (Velocidad en x)

double *vj; // (velocidad en y)

// Inicializaci�n de vectores posici�n y velocidad

x= malloc(sizeof(double));
y= malloc(sizeof(double));
vx= malloc(sizeof(double));
vj= malloc(sizeof(double));

// Constantes de posici�n radial. Estas representan las �rbitas del problema

double r0;

double r1;

double r2;

double r3;

double r4;


// inicializaci�n de las posiciones radiales

r0= 50;

r1=r0/5;

r2=((2*r0)/5);

r3=((3*r0)/5);

r4=((4*r0)/5);

// Definici�n de constantes del problema (Nota, los valores reales se instalaran en la aplicaci�n final del c�digo)
double G;

double M;
G=1234;

M=10;

// M�todo para llenar vectores, se usa un for para llenar las coordenas de cada vector

for (i=0;i<12;i++){

X[-1]=x0

x[i]= x0+ r1cos((2pi*i)/12);

vx[-1]=vz;

vx[i]= vz + sqrt((G*r1)/M)*sin((2pi*i)/12);

y[-1]=y0

y[i]= y0 + r1sin((2pi*i)/5);

vj[-1]=vy;

vj[i]=vy + sqrt((G*r1)/M)*cos((2pi*i)/12);

}
for (i=12;i<30;i++)
{

x[i]= x0 + r2cos((2pi*(i-12)/18);

y[i]= y0 + r2sin((2pi*(i-12)/18);

vx[i]= vz + sqrt((G*r2)/M)*sin((2pi*(i-12))/18);

vj[i]= vy + sqrt((G*r2)/M)*cos((2pi*(i-12))/18);

}

for (i=30;i<54;i++){

x[i]= x0 + r3cos((2pi*(i-30)/24);

y[i]= y0 + r3cos((2pi*(i-30)/24);

vx[i]= vz + sqrt((G*r3)/M)*sin((2pi*(i-30))/24);

vj[i]= vy + sqrt((G*r3)/M)*cos((2pi*(i-30))/24);

}

for (i=54;i<84;i++){

x[i]= x0 + r4cos((2pi*(i-54)/30);

y[i]= y0 + r4cos((2pi*(i-54)/30);

vx[i]= vz + sqrt((G*r4)/M)*sin((2pi*(i-54))/30);

vj[i]= vy + sqrt((G*r4)/M)*cos((2pi*(i-54))/30);

}

for (i=84;i<120;i++){

x[i]= x0 + r0cos((2pi*(i-84)/36);

y[i]= y0 + r0cos((2pi*(i-84)/36);

vx[i]= vz + sqrt((G*r0)/M)*sin((2pi*(i-84))/36);

vj[i]= vy + sqrt((G*r0)/M)*cos((2pi*(i-84))/36);

}
return 0;
}


