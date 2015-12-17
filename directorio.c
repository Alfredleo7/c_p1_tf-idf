#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <dirent.h>
#include "directorio.h"
//Declaramos los prototipos de funciones
    
//Declaramos los prototipos de funciones


void llamarArchivo(){
    
     //lista_directorio(argv[1]);
     //Llamamos a la función
     
     //strcat(&dir,"/");
    
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
     struct dirent *dt;
     DIR *dire;
     char *ref;
     char txt[4];
     char csv[4];
     strcpy(&txt,".txt");
     strcpy(&csv,".csv");

     dire = opendir(nombre);

     
     printf("Abriendo el directorio %s\n",nombre);
     while((dt=readdir(dire))!=NULL){
         switch(dt->d_type){
             case DT_REG: { ref = strchr(&dt->d_name, '.');
                            if(!strcmp(&ref ,txt))
                                printf("%s\t %s es txt\n", ref ,dt->d_name);
                            break;}
             case DT_DIR: {printf("|\t%-20s|\n",dt->d_name);break;}
         }
     }
     closedir(dire);
}
