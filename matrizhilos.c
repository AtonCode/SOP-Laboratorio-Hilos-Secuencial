/*
 Autor: M. Curiel
 Pontificia Universidad Javeriana
 **/

// Versión con Hilos
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>

#define MAXHILOS 20

int **matriz;

void *contar(int *posiciones) {
         
         
       int filainicial, filafinal, i, j, columnas;
       int *cuantos;
       
       cuantos = (int *)malloc(sizeof(int)); 
       *cuantos = 0;
       
       filainicial = posiciones[0];
       filafinal = posiciones[1];
       columnas = posiciones[2];
       
       //printf("Valores de filainicial %d, filafinal %d, col %d\n", filainicial, filafinal, columnas);
       
       for (i = filainicial; i < filafinal; i++)
           for(j = 0; j < columnas; j++)
               if (matriz[i][j] > 0) (*cuantos)++; 
        
       //printf("Valor de cuantos en el hilo %d\n", *cuantos);       
       pthread_exit(cuantos);       
       

}

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
	
	/*
	for (i = 0; i < filas; i++) {
        	for (j = 0; j < col; j++) 
    	         printf("%d ", matriz[i][j]);
    	        
    	        printf("\n");
        } */
    


}  


int main(int argc, char **argv){

    int filas, col, i, j, mayorcero=0, nhilos, inicio, filash;
    int *nunos, total=0;
    pthread_t thread[MAXHILOS];
    pthread_attr_t attr;
    int coord[MAXHILOS][3];
   
    struct timeval ti, tf;
    double tiempo;
   
     
    if (argc < 4) {
       printf("Numero de Argumentos insuficientes. Uso: filas columnas hilos\n");
       exit(0);
    }
    
    filas = atoi(argv[1]);
    col = atoi(argv[2]);
    nhilos = atoi(argv[3]);
    
   
      
        //printf("Antes de GenMatriz\n");
        GenMatriz(filas, col, 10);
       gettimeofday(&ti, NULL);   // Instante inicial
    // Crear Hilos 
        pthread_attr_init(&attr);
        pthread_attr_setscope(&attr, PTHREAD_SCOPE_SYSTEM);             
        filash = filas/nhilos;
        inicio = 0;
        for (i = 0; i < nhilos; i++) {          
           coord[i][0]= inicio;
           coord[i][1] = (inicio + filash);
           coord[i][2] = col;
           inicio +=filash;
           pthread_create(&thread[i], (const pthread_attr_t *)&attr, (void*) contar, (void*)&coord[i]);
        
        }
        
         for (i = 0; i < nhilos; i++) {                  
           pthread_join(thread[i], (void **)&nunos);
           //printf("El valor devuelto por el hilo es %d\n", *nunos);
           total = total + *nunos;
        
        }
    
  			
        printf("El numero de elementos de la matriz diferentes de 0 es %d\n", total);
        gettimeofday(&tf, NULL);   // Instante final
        tiempo= (tf.tv_sec - ti.tv_sec)*1000 + (tf.tv_usec - ti.tv_usec)/1000.0;
        printf("Has tardado: %g milisegundos\n", tiempo);
     		



}  
