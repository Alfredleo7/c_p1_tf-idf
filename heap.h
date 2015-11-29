
#ifndef HEAP_H
#define HEAP_H

#include "generic.h"
#include "list.h"

/*
 * ARCHIVO:
 *      heap.h
 * 		�ltima modificaci�n: 2007/04/25  (V. Mac�as)
 * --------------------------------------------------------------------------------------
 * DESCRIPCION:
 * 		Este archivo contiene la interfaz del TDA Heap(Cola de Prioridad) 
 *		manejado internamente como un arreglo unidimensional
 * DEPENDENCIAS:
 *		generic.h Definici�n de Tipo de Dato Gen�rico
 *		list.h	Para que la lista sirva de repositorio de los datos ordenados luego del HeapSort
 * MODIFICACIONES:
 *		2004/07/28 (Marisol Villacres):	creacion de la libreria
 *		2007/04/25 (V. Mac�as): Cambio soporte de version en Ingles
*/



/*-----------------------------------------------------------------------------------------
							TDA HEAP
  -----------------------------------------------------------------------------------------*/

/****************
	NIVEL L�GICO
 ****************

	Definici�n
	_____________________________________________________________________________________
	<heap>		::=	<arbol_PO>
	Operaciones
	_____________________________________________________________________________________
	Creacion
		Heap* heapNew(tamaniomaximo, tipo_de_orden, funcion_de_comparacion);
	Encolar/Desencolar
		heapEnQueue(nombreheap, nuevovalor)
		Generic heapDeQueue(nombreheap)
	Operaciones Varias
		Dado un heap, llena un arreglo con los elementos en el correctamente ordenados
		List *heapSort(nombreheap)
*/

/*****************************
	NIVEL DE IMPLEMENTACION
 *****************************/


/*
 * Tipo: TSort
 * ---------------
 * Define un tipo de ordenamiento para el heap: ascendente o descendente
 * Si es ascendente, en el tope del monticulo estara siempre el menor valor
 * si es descendente, en el tope estara el mayor valor
 */
typedef enum {ASC, DESC} TSort;

/*
 * Tipo: Heap
 * ---------------
 * El heap o monticulo es una arbol cuya raiz siempre contendra el mayor o menor
 * (esto depende del tipo de ordenamiento)
 * El Heap se utiliza para implementar colas de prioridad(debe salir el menor o el mayor)
 * y para implementar ordenamiento(HeapSort)
 * valor que sus hijos izquierdo y derecho,  
 */
typedef struct Heap{
	Generic *Data;
	int max;
	int nData;
	TSort type;
        cmpfn cmp;
}Heap;


/*
 * Funcion: heapNew
 * --------------------------
 * Modo de uso:
 * Heap *H;
 * H = heapNew(max, ASC, comoComparar);
 * Descripcion:
 * Esta operacion crea un heap para que almacene maximo una
 * cantidad dada de elementos, en forma ASC o DESC, dependiendo del tipo
 */
Heap * heapNew(int max, TSort type, cmpfn cmp);


/*
 * Funcion: heapIsEmpty
 * --------------------------
 * Modo de uso:
 * if(heapIsEmpty(H))
 * Descripcion:
 * Esta operacion indica si el heap esta vacio 
 */
int heapIsEmpty(Heap *H);

/*
 * Funcion: heapSort
 * --------------------------
 * Modo de uso:(Para un heap y una lista de enteros)
 * List *L;
 * Heap *H;
 * L = heapSort(H);
 * Descripcion:
 * Esta operacion genera una lista ordenada con los elementos dentro del Heap
 * Luego de la operaci�n el Heap queda vac�o
 */
List *heapSort(Heap *H);

/*
 * Funcion: heapDeQueue
 * --------------------------
 * Modo de uso:
 * Heap *H;
 * Generic Gmax;
 * Gmax = heapDeQueue(H);
 * Descripcion:
 * Esta operacion saca el elemento maximo o minimo(depende del tipo de orden
 * del heap) del heap y lo retorna
 */
Generic heapDeQueue(Heap *H);

/*
 * Funcion: heapEnQueue
 * --------------------------
 * Modo de uso:
 * Heap *H;
 * Generic gvalor;
 * heapEnQueue(H, gvalor);
 * Descripcion:
 * Esta operacion inserta un nuevo elemento en el Heap,
 * controlando que el heap conserve su propiedad de orden
 */
void heapEnQueue(Heap *H, Generic G);

Generic heapGetDatum(Heap *H, int idx);

int heapGetSize(Heap *H);

void heapPrint(Heap *H, printfn print);

void heapMake(Heap *H);

#endif
