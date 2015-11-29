/* 
 * File:   documento.h
 * Author: stalyn
 *
 * Created on 28 de noviembre de 2015, 07:07 PM
 */

#ifndef DOCUMENTO_H
#define	DOCUMENTO_H

#include "list.h"

typedef struct Documento{
    char nombre[20];
    List *terminos = listNew();
}Documento;

#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* DOCUMENTO_H */

