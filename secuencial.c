/*
 Autor: M. Curiel
 Pontificia Universidad Javeriana
 **/

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>

int **matriz;

int GenMatriz(int filas, int col, int pdifcero) {

	int j,i;
	
	matriz = (int **)malloc(filas*sizeof(int *));
	for (i = 0; i < filas; i++)
		matriz[i] = (int *)malloc(col * sizeof(int));
		
	for (i = 0; i < filas; i++)
       	for (j=0; j < col; j++)
       	// Solo tendra 1nos en la diagonal
       	   if (i == j) matriz[i][j] = 1;
       	   else matriz[i][j] = 0;
	
	/*for (i = 0; i < filas; i++) {
        	for (j = 0; j < col; j++) 
    	         printf("%d ", matriz[i][j]);
    	        
    	        printf("\n");
        }*/
    


}  


int main(int argc, char **argv){

    int filas, col, i, j, mayorcero=0;
    struct timeval ti, tf;
    double tiempo;   
    
    if (argc < 3) {
       printf("Numero de Argumentos insuficientes. Uso: filas columnas\n");
       exit(0);
    }
    
    filas = atoi(argv[1]);
    col = atoi(argv[2]);
    
    GenMatriz(filas, col, 10);
    gettimeofday(&ti, NULL); 
    // Contar total de 1 en la matriz
    /*for (i = 0; i < filas; i++) {
    	for (j = 0; j < col; j++) 
    	    printf("%d ", matriz[i][j]);
    	printf("\n");
    } */
    
    for (i = 0; i < filas; i++)
    	for (j=0; j < col; j++)
    		if (matriz[i][j] != 0)
			mayorcero++;
			
     printf("El numero de elementos de la matriz diferentes de 0 es %d\n", mayorcero);
     gettimeofday(&tf, NULL);   // Instante final
     tiempo= (tf.tv_sec - ti.tv_sec)*1000 + (tf.tv_usec - ti.tv_usec)/1000.0;
     printf("Has tardado: %g milisegundos\n", tiempo);
     		



}  
