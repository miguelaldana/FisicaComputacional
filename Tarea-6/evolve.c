// Tarea 6: Punto 2 solución de la ecuación diferencial
// Realizado por Miguel Aldana y Jesús Rincón
// 26 de octubre de 2013


#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int main (int argc,char **argv){

// estipulación de condiciones iniciales. Estas son el documento creado en condiciones iniciales

  if( argc != 2)
{
    printf("Se necesita un segundo documento para ejecutar este programa\n");
    exit(1);
  }

	FILE *in;
if(!(in=fopen(argv[1], "r"))){
    printf("Problema abriendo el archivo %s\n", argv[1]);
    exit(1);
 }
// definición de los vectores condiciones iniciales. Con esto se hace un scan que obtiene las variables del problema anterior y las convierte en xi (float) y yi(float), y las velocidades iniciales vix(float) y viy(float).

float *xi;
float *yi;
float *vix;
float *viy;
float *aix;
float *aiy;

float G ;// constante gravitacional 
float M ; // Masa del planeta 


xi= malloc(100 * sizeof(float));
yi= malloc(100 * sizeof(float));
vix= malloc(100 * sizeof(float));
viy= malloc(100 * sizeof(float));

G=1000.0;// no son valores reales;
M=200.0;// No son valores reales;

 int k;

 for(k = 0; k < 100;k++){
    fscanf(in," %f %f %f %f",&xi[k],&yi[k],&vix[k],&viy[k]);
  }  

// Inicialización de la solución usando el método de Runge-Kutta de cuarto orden.Siendo x (float) y y (float) (distancias) y vx (float) y vy (float) sus velocidades, osea, primeras derivadas.

float *x;
float *y;
float *vx;
float *vy; 
float *t;

float h;//diferencial a usar
float n_points;// puntos a analizar

h=0.5;
n_points=((6.0 + h)/h);

// Inicialización de funciones (x y y) y sus derivadas (vx y vy)

x= malloc(n_points * sizeof(float));
y= malloc(n_points * sizeof(float));
vx= malloc(n_points * sizeof(float));
vy= malloc(n_points * sizeof(float));
t=malloc(n_points * sizeof (float));// tiempo.

// definición del método de Runge-Kutta


// paso 1: Definición de derivadas

float func_prime_1x(float t,float x, float vx,  float y,float vy){
	return vx;
}

float func_prime_2x(float t, float x, float vx, float y, float vy)
{
	float r=(x*x + y*y);
	float d=pow(r,3);
	return -(G*M/d);
}
float func_prime_1y(float t,float x, float vx,  float y,float vy)//primera derivada en y
{
	return vy;
}

float func_prime_2y(float t,float x, float vx,  float y,float vy)//segunda derivada en y
{
	float ra=(x*x + y*y);
	float di=pow(ra,3);
	return -(G*M/di);
}

// Realización del método de Runge-Kutta
// condiciones iniciales

 int j;

for (j=0; j<n_points; j++){
x[0]=xi[j];
y[0]=yi[j];
vx[0]=vix[j];
vy[0]=viy[j];

}
// realización del método
t[0]=0;

 int i;

for (i=1; i<n_points; i++){
float kx1_1=func_prime_1x(t[i-1],x[i-1],vx[i-1],y[i-1],vy[i-1]);// pendiente velocidad en x;
float kx2_1=func_prime_2x(t[i-1],x[i-1],vx[i-1],y[i-1],vy[i-1]); //pendiente aceleración en x

float ky1_1=func_prime_1y(t[i-1],x[i-1],vx[i-1],y[i-1],vy[i-1]);// pendiente velocidad en y;
float ky2_1=func_prime_2y(t[i-1],x[i-1],vx[i-1],y[i-1],vy[i-1]); //pendiente aceleración en y

// primera línea 

float t1= t[i-1] + (h/2.0);
float x1=x[i-1] + (h/2.0)*kx1_1;
float vx1=vx[i-1] + (h/2.0)*kx2_1;
float y1=y[i-1] + (h/2.0)*ky1_1;
float vy1=vy[i-1] + (h/2.0)*ky2_1;

float kx1_2 = func_prime_1x(t1,x1,vx1,y1,vy1);
float kx2_2 = func_prime_2x(t1,x1,vx1,y1,vy1);

float ky1_2 = func_prime_1y(t1,x1,vx1,y1,vy1);
float ky2_2 = func_prime_2y(t1,x1,vx1,y1,vy1);

// segunda línea 

float t2= t[i-1] + (h/2.0);
float x2=x[i-1] + (h/2.0)*kx1_2;
float vx2=vx[i-1] + (h/2.0)*kx2_2;
float y2=y[i-1] + (h/2.0)*ky1_2;
float vy2=vy[i-1] + (h/2.0)*ky2_2;

float kx1_3 = func_prime_1x(t2,x2,vx2,y2,vy2);
float kx2_3 = func_prime_2x(t2,x2,vx2,y2,vy2);

float ky1_3 = func_prime_1y(t2,x2,vx2,y2,vy2);
float ky2_3 = func_prime_2y(t2,x2,vx2,y2,vy2);

// tercera línea 

float t3= t[i-1] + (h/2.0);
float x3=x[i-1] + (h/2.0)*kx1_3;
float vx3=vx[i-1] + (h/2.0)*kx2_3;
float y3=y[i-1] + (h/2.0)*ky1_3;
float vy3=vy[i-1] + (h/2.0)*ky2_3;

float kx1_4 = func_prime_1x(t3,x3,vx3,y3,vy3);
float kx2_4 = func_prime_2x(t3,x3,vx3,y3,vy3);

float ky1_4 = func_prime_1y(t3,x3,vx3,y3,vy3);
float ky2_4 = func_prime_2y(t3,x3,vx3,y3,vy3);

// cuarta línea promedios de pendientes

float kx1= (1.0/6.0)*(kx1_1 + 2.0*kx1_2 + 2.0*kx1_3 + kx1_4);
float kx2= (1.0/6.0)*(kx2_1 + 2.0*kx2_2 + 2.0*kx2_3 + kx2_4);

float ky1= (1.0/6.0)*(ky1_1 + 2.0*ky1_2 + 2.0*ky1_3 + ky1_4);
float ky2= (1.0/6.0)*(ky2_1 + 2.0*ky2_2 + 2.0*ky2_3 + ky2_4);

t[i] = t[i-1] + h;
    
x[i] = x[i-1] + h *kx1;
    
vx[i] = vx[i-1] + h *kx2;
    
y[i] = y[i-1] + h *ky1;
    
vy[i] = vy[i-1] + h *ky2;

}
return 0; 
}



