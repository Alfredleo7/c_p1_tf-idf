
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
//Declaramos los prototipos de funciones

char dir[50];
char *newDir;
//Declaramos los prototipos de funciones
void llamarArchivo();
void abrirDirectorio(char *nombre);

void llamarArchivo(){
    //Limpiamos la pantalla
     system("clear");

     //lista_directorio(argv[1]);
     //Llamamos a la función
     strcpy(&dir, "/");
     abrirDirectorio(&dir);

     while(1){
        printf("Ingrese la ubicacion: ");
        scanf("%s", &newDir);
        strcat(&dir, &newDir);
        abrirDirectorio(&dir);
        strcat(&dir, "/");
     }
}
//Función que permite listar un directorio de manera recursiva
void abrirDirectorio(char *nombre){
 
    //Declaramos variables, estructuras
     struct stat estru;
     struct dirent *dt;
     DIR *dire;

     dire = opendir(nombre);

     printf("Abriendo el directorio %s\n",nombre);
     //Recorrer directorio
     while((dt=readdir(dire))!=NULL){
         //strcmp permite comparar, si la comparación es verdadera devuelve un 0
         //Aquí se pregunta si el arhivo o directorio es distinto de . y ..
         //Para así asegurar que se muestre de forma recursiva los directorios y ficheros del directorio actual
             if((strcmp(dt->d_name,".")!=0)&&(strcmp(dt->d_name,"..")!=0)){
             stat(dt->d_name,&estru);
             //Si es un directorio, llamar a la misma función para mostrar archivos
             if(S_ISDIR(estru.st_mode)){
                 abrirDirectorio(dt->d_name);
                 //Si no es directorio, mostrar archivos
             }else{
                 
                 printf("|\t%-20s %d \t|\n",dt->d_name,estru.st_size);
             }
         }

     }
     closedir(dire);
}
