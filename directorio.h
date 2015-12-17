/* 
 * File:   directorio.h
 * Author: stalyn
 *
 * Created on 28 de noviembre de 2015, 02:43 PM
 */

#ifndef DIRECTORIO_H
#define	DIRECTORIO_H

#ifdef	__cplusplus
extern "C" {
#endif


char *txt;
char *csv;
char *dir;
char *newDir;
    
void llamarArchivo(void);
void abrirDirectorio(char *nombre);

#ifdef	__cplusplus
}
#endif

#endif	/* DIRECTORIO_H */

