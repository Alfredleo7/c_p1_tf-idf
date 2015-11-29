/**
* @file quebrado.h
* @brief Este archivo contiene la definicion del 
* TDA Quebrado que representa a un numero fraccionario con numerador y denomiador. Una variable
* Generic puede ser asignada a cualquier tipo de puntero, se le
* puede recuperar su valor y modificar su valor con las funciones
* aqui especificadas.
*
* @author Marcelo Loor
* @author Marisol Villacres
* @author Veronica Macias
*
* @date 10/26/2011
*/


#ifndef QUEBRADO_H
#define	QUEBRADO_H

#ifdef	__cplusplus
extern "C" {
#endif

/** @defgroup hs TDA Quebrado
 * Estas definiciones y funciones componenen el TDA Quebrado
 * @{
 */

 /**
 * @brief Definicion del tipo de dato Quebrado, el cual permite 
 * representar numeros fraccionarios compuestos de numerador
 * y denominador.
 */
    typedef struct Quebrado{
        int n, d;
    }Quebrado;

/**
* quebradoNew permite crear un nuevo Quebrado, asignarle numerador 
* y denominador y retornarlo listo para almacenarlo en una variable 
* de tipo Generic.
* @author Marisol Villacres
* @param nuevonum el valor a ser asignado para el numerador
* @param nuevoden el valor a ser asignado para el denominador
* @return retorna un nuevo quebrado 
* @date 10/26/2011
*/    
    Quebrado *quebradoNew(int nuevonum, int nuevoden);

/**
* quebradoSetNum permite asignarle un nuevo valor para el numerador 
* de un quebrado dado
* @author Marisol Villacres
* @param q el quebrado cuyo numerador se busca modificar
* @param nuevonum el valor a ser asignado para el numerador
* @date 10/26/2011
*/     
    void quebradoSetNum(Quebrado *q, int nuevonum);

/**
* quebradoSetNum permite asignarle un nuevo valor para el denominador 
* de un quebrado dado
* @author Marisol Villacres
* @param q el quebrado cuyo denominador se busca modificar
* @param nuevoden el valor a ser asignado para el denominador
* @date 10/26/2011
*/     
    void quebradoSetDen(Quebrado *q, int nuevoden);

/**
* quebradoGetNum obtiene el numerador de un quebrado existente
* @author Marisol Villacres
* @param q el quebrado del cual se quiere obtener el numerador
* @return el numerador del quebrado q
* @date 10/26/2011
*/     
    int quebradoGetNum(Quebrado *q);

/**
* quebradoGetDen obtiene el denominador de un quebrado existente
* @author Marisol Villacres
* @param q el quebrado del cual se quiere obtener el denominador
* @return el denominador del quebrado q
* @date 10/26/2011
*/     
    int quebradoGetDen(Quebrado *q);

/**
* quebradoSumar suma dos quebrados y retorna un nuevo quebrado
* @author Marisol Villacres
* @param a quebrado a ser sumado con el quebrado b
* @param b quebrado a ser sumado con el quebrado a
* @return un nuevo quebrado resultado de la suma de dos quebrados
* @date 10/26/2011
*/     
    Quebrado *quebradoSumar(Quebrado *a, Quebrado *b);


    int quebradoCmpxNum(Quebrado *a, int *valor);

    int quebradoCmpDenominadores(Quebrado *a, Quebrado *quebrado);

    void quebradoPrint(Quebrado *a);
    
#ifdef	__cplusplus
}
#endif

#endif	

