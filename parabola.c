#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <gsl/gsl_math.h> 
#include <gsl/gsl_eigen.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_linalg.h>
#include <gsl/gsl_cblas.h>
#include <gsl/gsl_blas.h>

int count_lines(char *filename);
int main(int argc, char **argv){
  FILE *in;
  FILE *dos;
  int i;

  /*Leo los datos que hay en argv[1] y los ubico en una matriz*/
  in = fopen(argv[1], "r");

  int n_lines = count_lines(argv[1]);

  gsl_matrix * datos = gsl_matrix_calloc (n_lines, 2);

  gsl_matrix_fscanf(in, datos);

  fclose(in);
  
  /*Inicializamos las matrices y vectores que usaremos para realizar el ajuste*/

  /*La matriz g es donde guardamos los elementos que componen el modelo físico a utilizar [1+t+(1/2)t^2]*/
  gsl_matrix * g = gsl_matrix_calloc (n_lines, 3);
  /*La matriz gt es donde en un futuro guardaremos la traspuesta de g*/
  gsl_matrix * gt = gsl_matrix_calloc (3, n_lines);
  /*La matriz w es donde en un futuro guardaremos la multiplicación matricial de gt*g (G^t*G)*/
  gsl_matrix * w = gsl_matrix_calloc (3,3);
  /*La matriz d es donde en un futuro guardaremos la multiplicación matricial de gt*posición (G^t*d)*/
  gsl_matrix * d = gsl_matrix_calloc (3,1);
  gsl_matrix * pos = gsl_matrix_calloc (n_lines,1);

  /*Determinamos la matriz g cuya iésima fila es: 1.0, ti, 0.5*ti*ti*/

  gsl_vector * uno = gsl_vector_calloc( n_lines );
  gsl_vector * tiempo = gsl_vector_calloc( n_lines );  
  gsl_vector * tiempo_cuadrado = gsl_vector_calloc( n_lines );

  gsl_vector_set_all (uno, 1.0);

  gsl_matrix_get_col (tiempo, datos,0);

  gsl_vector_add (tiempo_cuadrado, tiempo);
  gsl_vector_mul (tiempo_cuadrado, tiempo);
  gsl_vector_scale (tiempo_cuadrado, 0.5);

  gsl_matrix_set_col (g, 0, uno);
  gsl_matrix_set_col (g, 1, tiempo);
  gsl_matrix_set_col (g, 2, tiempo_cuadrado);

  /*Ahora hallamos la traspuesta de g y la guardamos en gt*/

  gsl_matrix_transpose_memcpy (gt, g);

  /*Realizamos la multiplicación gt*g para seguir con nuestro modelo de ajuste por mínimos cuadrados (m = (Gt*G)^-1 * Gt*d)*/

  gsl_blas_dgemm( CblasNoTrans, CblasNoTrans,1,gt,g,0,w);

  /*Las siguientes líneas corresponden a la determinación de la inversa de gt*g es decir (gt*g)^-1, que se llamará inverse*/

  int s;

  gsl_matrix * inverse = gsl_matrix_alloc (3, 3);
  gsl_permutation * perm = gsl_permutation_alloc (3);

  gsl_linalg_LU_decomp (w, perm, &s);

  gsl_linalg_LU_invert (w, perm, inverse);

  /*Ahora sacamos los valores de la posición del archivo argv[1] y los guardamos en una amtriz llamado posición de nx1*/

  gsl_vector * posicion = gsl_vector_calloc (n_lines);
  gsl_matrix_get_col (posicion, datos,1);
  gsl_matrix_set_col (pos, 0, posicion);

  /*Calculamos la multiplicación de gt*d siguiendo nuestro modelo, y la guardamos en una amtriz d*/

  gsl_blas_dgemm(CblasNoTrans,CblasNoTrans,1,gt,pos,0,d);

  /*Finalmente hallamos el vector m (matriz de nx1) que minimiza el tamaño del vector residual*/

  gsl_matrix * m = gsl_matrix_calloc (3, 1);
  gsl_blas_dgemm(CblasNoTrans,CblasNoTrans,1,inverse,d,0,m);

  /*Con este nuevo m, y con el modelo d=G*m, podemos hallar el nuevo vector posición h que minimiza nuestra función*/

  gsl_matrix * h = gsl_matrix_calloc (n_lines, 1);
  gsl_blas_dgemm(CblasNoTrans,CblasNoTrans,1,g,m,0,h);

  /*Las siguientes líneas son para imprimir las nuevas posiciones con el tiempo en un archivo nuevo*/

  dos = fopen("minimizado.dat", "w");
  for(i=0;i<n_lines;i++){ 
    fprintf (dos,"%f %f\n", gsl_vector_get (tiempo, i), gsl_matrix_get (h, i, 0));
  }
  fclose(dos);

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
